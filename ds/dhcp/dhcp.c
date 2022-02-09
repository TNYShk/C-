/**********************************************
 * AVL - Source File                          *
 * Developer: Tanya			                  *
 *          Jan 31, 2022                      *
 *                                            *
 * Reviewer: Nurit  	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* memset */
#include <stdio.h>
#include <arpa/inet.h>
#include <byteswap.h>

#include "dhcp.h"

#define BITS (32)
#define TAKEN (1)



enum child
{
    ZERO,
    ONE,
    NUM_OF_CHILDREN
};

struct dhcp
{
	struct trie *root;
	unsigned int subnet_mask_size; /* /22 */
	uint32_t network_address;

};

typedef struct trie
{
	struct trie_node *node;
	unsigned int height;
	

}trie_t;

typedef struct trie_node
{
	char isTaken;
	struct trie_node *child[NUM_OF_CHILDREN];

}trie_node_t;


static void Destroy(trie_node_t *trie);
static void InitLeft(dhcp_t *dhcp, trie_node_t *root, unsigned int height);
static void InitRight(dhcp_t *dhcp, trie_node_t *root, unsigned int height);


dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size)
{
	status_t test = SUCCESS;
	
	dhcp_t *death = NULL;
	death = (dhcp_t *)calloc(1, sizeof(dhcp_t));
	if (NULL == death)
		return NULL;

	death->root = (trie_t *)calloc(1, sizeof(trie_t));
	if(death->root == NULL)
	{
		free(death);
		death = NULL;
		return NULL;
	}
	death->subnet_mask_size = subnet_mask_size;
	death->root->height = BITS - subnet_mask_size;

	test = inet_pton(AF_INET, network_address, &death->network_address);

	death->network_address = bswap_32(death->network_address);
	printf("test %d\n", test);

	printf("%d\n",death->network_address );
	InitLeft(death, death->root->node, death->root->height);
	InitRight(death,death->root->node, death->root->height);

	return death;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	Destroy(dhcp->root->node->child[ZERO]);
	Destroy(dhcp->root->node->child[ONE]);
	
	dhcp->root = NULL;
	memset(dhcp,0,sizeof(dhcp_t));

	free(dhcp);
	dhcp = NULL;
}



static void Destroy(trie_node_t *trie)
{
    if (NULL == trie)
    {
        return;
    }

    Destroy(trie->child[ZERO]);
    Destroy(trie->child[ONE]);
    
    free(trie);
    trie = NULL;
}


static void InitLeft(dhcp_t *dhcp, trie_node_t *root, unsigned int height)
{
	int cur_height = height;
	if(cur_height == 0)
	{
		root->isTaken = TAKEN;
		return;
	}

	root->child[ZERO] = (trie_node_t*)calloc(1, sizeof(trie_node_t));
	if(root->child[ZERO] == NULL)
	{
		free(root);
		return ;
	}

	InitLeft(dhcp, root->child[ZERO], --cur_height);
}


static void InitRight(dhcp_t *dhcp, trie_node_t *root, unsigned int height)
{
	int cur_height = height;

	if (cur_height == 1)
	{
		root->child[ZERO] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
		root->child[ZERO]->isTaken = TAKEN;

		root->child[ONE] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
		root->child[ONE]->isTaken = TAKEN;
		
		root->isTaken = TAKEN;
		return;
	}
	InitRight(dhcp, root->child[ONE], --cur_height);
}




/*
subnet:
255.255.254.252 /29
255.255.255.240 /28
255.255.255.224 /27
255.255.255.192 /26
255.255.255.128 /25

255.255.255.0   /24 
255.255.254.0   /23
255.255.252.0   /22 
255.255.248.0   /21
255.255.240.0  /20

255.255.0.0     /16
255.254.0.0     /15

128.0.0.0      /1

Create dhcp:
1. based on given param, extract trie height (32 - subnet_mask_size)
2. store network adrs 255.255.252? 216.202.
int gowhere = (1<<(height -1))&numtocheck;
*/

