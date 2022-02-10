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
#define TAKEN (2)

typedef struct trie_node trie_node_t;

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
	uint32_t network_address; /* after inet_pton ans bswap 1401034532*/
	uint32_t mask;
};

typedef struct trie
{
	struct trie_node *root;
	uint32_t height;
}trie_t;

struct trie_node
{
	char isTaken;
	trie_node_t *child[NUM_OF_CHILDREN];

};


static void Destroy(trie_node_t *trie);
static status_t InitLeft(trie_node_t *root, uint32_t height);
static status_t InitRight(trie_node_t *root, uint32_t height);
static size_t CountRec(trie_node_t *root, uint32_t height);

static status_t IsIPValid(dhcp_t *dhcp, const char *ip_address);

dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size)
{

	status_t test = SUCCESS;
	dhcp_t *death = NULL;
	unsigned int mask = -1;
	uint32_t inet = 0;

	assert(30 > subnet_mask_size);
	assert(NULL != network_address);

	death = (dhcp_t *)calloc(1, sizeof(dhcp_t));
	if (NULL == death)
		return NULL;

	death->tree = (trie_t *)calloc(1, sizeof(trie_t));
	if(NULL == death->tree)
	{
		free(death);
		death = NULL;
		return NULL;
	}
	death->tree->root = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if(NULL == death->tree->root)
	{
		free(death->tree);
		death->tree = NULL;

		free(death);
		death = NULL;
		return NULL;
	}

	death->subnet_mask_size = subnet_mask_size;
	death->tree->height = BITS - subnet_mask_size;

	test = inet_pton(AF_INET, network_address, &inet);
	assert(test);

	death->network_address = ntohl(inet);
	
	mask = (-1)<<(death->tree->height);
	death->mask = mask;
	printf("mask %u\n",death->mask );
	printf("network adrs %u\n",death->network_address );

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
	dhcp->tree->root = NULL;
	
	free(dhcp->tree);
	dhcp->tree = NULL;
	
	memset(dhcp, 0, sizeof(dhcp_t));

	free(dhcp);
	dhcp = NULL;
}


size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t max_available = pow(2, BITS - dhcp->subnet_mask_size);
	
	return max_available -= CountRec(dhcp->tree->root, dhcp->tree->height);
}


status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_address_to_free)
{
	/*check that ip belongs to pool */
	int gowhere = -1;
	uint32_t convert_ip = 0;
	size_t high = dhcp->tree->height;

	printf("isIpvalid?  %d\n", IsIPValid(dhcp, ip_address_to_free));

	if(RIGHT != inet_pton(AF_INET, ip_address_to_free, &convert_ip))
	{
		return FAILURE;
	}
	/*printf("IP is %u\n", convert_ip);*/
	convert_ip = ntohl(convert_ip);
	/*printf("Swaped IP is %u\n", convert_ip);*/
	convert_ip = convert_ip &  ~(dhcp->mask);

	/*printf("AND tilda IP is %u\n", convert_ip);*/
	 
	for(; high > 0; --high)
	{
		gowhere = (( convert_ip >> (high - 1) ) & 1 );
		printf("gowhere? %d\n", gowhere);
		dhcp->tree->root = dhcp->tree->root->child[gowhere];
		dhcp->tree->root->isTaken = 0;
		
	}
	return SUCCESS;
}

static status_t IsIPValid(dhcp_t *dhcp, const char *ip_address)
{
	unsigned int convert_ip = 0;						
	unsigned int net_adr = (dhcp->network_address) & (dhcp->mask);

	status_t test = inet_pton(AF_INET, ip_address, &convert_ip);
	assert(1 == test);
	printf("converted %u\n", convert_ip);
	printf("net_adr %u\n", net_adr);
	convert_ip &= dhcp->mask;

	printf("XOR %u\n", (convert_ip ^ net_adr));
	
	return ((convert_ip ^ net_adr) == 0);


}

static size_t CountRec(trie_node_t *root, uint32_t height)
{
	size_t counter = 0;
	
	if (root->isTaken == TAKEN)
	{
		return (1 << height);
	}

	

	if(NULL != root->child[LEFT])
	{
		counter += CountRec(root->child[LEFT], height -1);
	}

	if(NULL != root->child[RIGHT])
	{
		counter += CountRec(root->child[RIGHT], height -1);
	}

	
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


static status_t InitLeft( trie_node_t *root, uint32_t height)
{
	while(height > 0)
	{
		root->child[LEFT] = (trie_node_t*)calloc( 1,sizeof(trie_node_t));
		if(NULL == root->child[LEFT])
		{
			return FAILURE;
		}

		root = root->child[LEFT];
		--height;
	}
	root->isTaken = TAKEN;
	return SUCCESS;
	/*

	if(height == 0)
	{
		root->isTaken = TAKEN;
		return SUCCESS;
	}

	root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if (NULL == root->child[LEFT])
		return FAILURE;

	return InitLeft(root->child[LEFT], height -1);

	
	*/
}


static status_t InitRight(trie_node_t *root, uint32_t height)
{
	size_t index = 0;

	for(index = 0; index < height - 1; ++index)
    {
        root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
        if(NULL == root->child[RIGHT])
        {
            return FAILURE;
        }

        root = root->child[RIGHT];
    }
    root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
    if(NULL == root->child[LEFT])
    {
        return FAILURE;
    }

    root->child[LEFT]->isTaken = TAKEN;

    root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
    if(NULL == root->child[RIGHT])
    {
        return FAILURE;
    }

    root->child[RIGHT]->isTaken = TAKEN;
    root->isTaken = TAKEN;

    return SUCCESS;

	/*
	if(height == 1)
	{
		
		root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
		if(NULL != root->child[LEFT])
		{
			root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
			root->child[RIGHT]->isTaken = TAKEN;
			root->child[LEFT]->isTaken = TAKEN;
			root->isTaken = TAKEN;
		}
		
		return (NULL == root->child[RIGHT]);
	}

	root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if (NULL == root->child[RIGHT])
		return FAILURE;

	return InitRight(root->child[RIGHT], --height);
	*/

}



/*
unsigned int try = -1;
try <<= death->tree->height;


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






/*
subnet:
255.255.254.248 /29
255.255.255.240 /28
255.255.255.224 /27
255.255.255.192 /26
255.255.255.128 /25
255.255.255.0   /24 
255.255.254.0   /23
255.255.252.0   /22 
255.255.248.0   /21
255.255.240.0   /20
255.255.224.0   /19
255.255.192.0   /18
255.255.128.0   /17
255.255.0.0     /16
255.254.0.0     /15
255.252.0.0     /14
255.248.0.0     /13
255.240.0.0     /12
255.224.0.0     /11



128.0.0.0      /1

Create dhcp:
1. based on given param, extract trie height (32 - subnet_mask_size)
2. store network adrs 255.255.252? 216.202.
int gowhere = (1<<(height -1))&numtocheck;
*/

