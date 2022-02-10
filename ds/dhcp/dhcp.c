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
#include <math.h>
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
static size_t CountRec(trie_node_t *root, size_t height, int side);
static size_t CountRight(trie_node_t *root, size_t height);

dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size)
{
	status_t test = SUCCESS;
	dhcp_t *death = NULL;

	assert(30 > subnet_mask_size);

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
	assert(test);

	death->network_address = bswap_32(death->network_address);

	printf("%u\n",death->network_address );
	test = InitLeft(death->tree->root, death->tree->height);
	assert(test == SUCCESS);
	
	test = InitRight(death->tree->root, death->tree->height);
	assert(test == SUCCESS);
	
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


size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t max_available = pow(2,BITS - dhcp->subnet_mask_size);
	
	return max_available -= CountRec(dhcp->tree->root, dhcp->tree->height,RIGHT) + CountRec(dhcp->tree->root, dhcp->tree->height,LEFT);

}



static size_t CountRec(trie_node_t *root, size_t height, int side)
{
	size_t counter = 0;
	
	if (height == 1)
	{
		if(root->child[side] != NULL )
		{
			if(root->child[side]->isTaken == TAKEN)
			{
				++counter;	
			} 
		}
		if(root->child[!side] != NULL )
		{
			if(root->child[!side]->isTaken == TAKEN)
				++counter;
		}
		return counter;
	}

	counter += CountRec(root->child[side], --height, side) ;
	

	return counter;

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
	if(height == 0)
	{
		root->isTaken = TAKEN;
		return SUCCESS;
	}

	root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if (root->child[LEFT] == NULL)
		return FAILURE;

	return InitLeft(root->child[LEFT], --height);

	/*
	while(height > 0)
	{
		root->child[LEFT] = (trie_node_t*)calloc( 1,sizeof(trie_node_t));
		root = root->child[LEFT];
		--height;
	}
	root->isTaken = TAKEN;
	return SUCCESS;
	*/
}


static status_t InitRight(trie_node_t *root, size_t height)
{
	
	if(height == 1)
	{
		
		root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
		if(root->child[LEFT] != NULL)
		{
			root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
			root->child[RIGHT]->isTaken = TAKEN;
			root->child[LEFT]->isTaken = TAKEN;
			root->isTaken = TAKEN;
		}
		
		return (root->child[RIGHT] == NULL);
	}

	root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if (root->child[RIGHT] == NULL)
		return FAILURE;

	return InitRight(root->child[RIGHT], --height);



/*
/*
static size_t CountRight(trie_node_t *root, size_t height)
{
	size_t counter = 0;
	
	while(height > 0)
	{
		if(root->isTaken == TAKEN)
	{
		++counter;
	}
		root = root->child[RIGHT];

		--height;
	}
	return counter;


}
*/

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

