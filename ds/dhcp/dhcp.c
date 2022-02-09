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

#define BITS (sizeof(char) * 32)
#define TAKEN (1)



enum child
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

struct dhcp
{
	struct trie *tree;
	unsigned int subnet_mask_size; /* /22 */
	uint32_t network_address;
};

typedef struct trie
{
	struct trie_node *root;
	size_t height;
}trie_t;

typedef struct trie_node
{
	int isTaken;
	struct trie_node *child[NUM_OF_CHILDREN];

}trie_node_t;


static void Destroy(trie_node_t *trie);
static status_t InitLeft(trie_node_t *root, size_t height);
static status_t InitRight(trie_node_t *root, size_t height);


dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size)
{
	status_t test = SUCCESS;
	
	dhcp_t *death = NULL;
	death = (dhcp_t *)calloc(1, sizeof(dhcp_t));
	if (NULL == death)
		return NULL;

	death->tree = (trie_t *)calloc(1, sizeof(trie_t));
	if(death->tree == NULL)
	{
		free(death);
		death = NULL;
		return NULL;
	}
	death->tree->root = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if(death->tree->root == NULL)
	{
		free(death->tree);
		death->tree = NULL;

		free(death);
		death = NULL;
		return NULL;
	}

	death->subnet_mask_size = subnet_mask_size;
	death->tree->height = BITS - subnet_mask_size;

	test = inet_pton(AF_INET, network_address, &death->network_address);

	death->network_address = bswap_32(death->network_address);
	printf("test %d\n", test);

	printf("%u\n",death->network_address );
	test = InitLeft(death->tree->root, death->tree->height);

	test = InitRight(death->tree->root, death->tree->height);

	return death;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	Destroy(dhcp->tree->root->child[LEFT]);
	Destroy(dhcp->tree->root->child[RIGHT]);
	
	free(dhcp->tree->root);
	free(dhcp->tree);
	dhcp->tree = NULL;
	memset(dhcp,0,sizeof(dhcp_t));

	free(dhcp);
	dhcp = NULL;
}



static void Destroy(trie_node_t *root)
{
    if (NULL == root)
    {
        return;
    }

    Destroy(root->child[LEFT]);
    Destroy(root->child[RIGHT]);
    
    free(root);
    root = NULL;
}


static status_t InitLeft(trie_node_t *root, size_t height)
{
	while(height > 0)
	{
		root->child[LEFT] = (trie_node_t*)calloc( 1,sizeof(trie_node_t));
		root = root->child[LEFT];
		--height;
	}
	root->isTaken = TAKEN;
	return SUCCESS;
	
}


static status_t InitRight(trie_node_t *root, size_t height)
{
	
	while(height > 1)
	{
		root->child[RIGHT] = (trie_node_t*)calloc( 1,sizeof(trie_node_t));
		root = root->child[RIGHT];
		--height;
	}
	root->child[LEFT] = (trie_node_t*)calloc(1,sizeof(trie_node_t));
	root->child[RIGHT] = (trie_node_t*)calloc(1,sizeof(trie_node_t));
	
	root->child[RIGHT]->isTaken = TAKEN;
	root->child[LEFT]->isTaken = TAKEN;
	root->isTaken = TAKEN;

	return SUCCESS;


	
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

