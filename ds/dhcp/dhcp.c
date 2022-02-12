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
#define OCCUPIED (3)



enum child
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct trie_node
{
	char isTaken;
	 struct trie_node *child[NUM_OF_CHILDREN];

}trie_node_t;

typedef struct trie
{
	trie_node_t *root;
	uint32_t height;
}trie_t;



struct dhcp
{
	trie_t *tree;
	unsigned int subnet_mask_size; /* /22 */
	uint32_t network_address; /* after inet_pton ans bswap 1401034532*/
	uint32_t mask;
};

typedef status_t (*req_func_t)(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *);
static status_t IPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *);
static status_t NoIPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *);
static status_t RecIPProvide(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *);
static status_t InitLeft(trie_node_t *root, uint32_t height);
static status_t InitRight(trie_node_t *root, uint32_t height);
static void Destroy(trie_node_t *trie);
static size_t CountRec(trie_node_t *root, uint32_t height);
static status_t IsIPValid(dhcp_t *dhcp, const char *ip_address);
static status_t IsIpValid(dhcp_t *dhcp, uint32_t requested_ip_address);
static void UpdateAllocated(trie_node_t *root);
static status_t RecFreeIP(trie_node_t *node, uint32_t *ip_to_free, uint32_t height);




dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size)
{

	status_t test = SUCCESS;
	dhcp_t *death = NULL;
	
	uint32_t inet = 0;

	assert(30 > subnet_mask_size);
	assert(NULL != network_address);

	death = (dhcp_t *)calloc(1, sizeof(dhcp_t));
	if (NULL == death)
		return NULL;

	death->tree = (trie_t *)calloc(1, sizeof(trie_t));
	if (NULL == death->tree)
	{
		free(death);
		death = NULL;
		return NULL;
	}
	death->tree->root = (trie_node_t *)calloc(1,sizeof(trie_node_t));
	if (NULL == death->tree->root)
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
	
	death->mask = ((-1)<<(death->tree->height));

	
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
	size_t max_available = 1<<(BITS - dhcp->subnet_mask_size);
	
	return max_available -= CountRec(dhcp->tree->root, dhcp->tree->height);
}

status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip_address, char *result_ip_address)
{
	status_t alloc_stat = SUCCESS;
	int is_provided = 0;

	uint32_t net_adrs = (dhcp->network_address)&(dhcp->mask);
	uint32_t req_ip_adrs = 0;
	req_func_t IP_LUT[] = {&NoIPProvided, &IPProvided};

	assert(NULL != dhcp);
  	assert(NULL != result_ip_address);

  	if(dhcp->tree->root->isTaken)
  	{
  		printf("full!\n");
  		return FAILURE;
  	}

  	if ((is_provided = (NULL != requested_ip_address)))
  	{
  		if( !IsIPValid(dhcp,requested_ip_address))
  		{
  			sprintf(result_ip_address, "%s not of pool!",requested_ip_address);
  			return FAILURE;
  		}

  		assert(1 == inet_pton(AF_INET, requested_ip_address, &req_ip_adrs));
    	req_ip_adrs = bswap_32(req_ip_adrs);
    	assert(IsIpValid(dhcp, req_ip_adrs));
    }

    alloc_stat = IP_LUT[is_provided](dhcp->tree->root, &req_ip_adrs, (dhcp->tree->height) -1, &alloc_stat);
  	if (SUCCESS != alloc_stat)
  	{
  		return alloc_stat;
  	}
  	
  	req_ip_adrs |= net_adrs;
  	req_ip_adrs = bswap_32(req_ip_adrs);

  		

  	return (SUCCESS == inet_ntop(AF_INET, &req_ip_adrs, result_ip_address, BITS >>1));

}


status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_address_to_free)
{
	
	uint32_t convert_ip = 0;
	
	if (1 != IsIPValid(dhcp, ip_address_to_free))
  	{
  		printf("invalid! %s\n",ip_address_to_free);

  		return FAILURE;
  	}

	if(1 != inet_pton(AF_INET, ip_address_to_free, &convert_ip))
	{
		return FAILURE;
	}
	convert_ip &=  ~(dhcp->mask);
	convert_ip = bswap_32(convert_ip);
	
	return RecFreeIP(dhcp->tree->root, &convert_ip, dhcp->tree->height);
	

	/*
	for(; high >= 0; --high)
	{
		gowhere = ( convert_ip >> (high -1 ) ) & 1;
		printf("gowhere? %d\n", gowhere);
		if(NULL == dhcp->tree->root->child[gowhere])
		{
			return DOUBLE_FREE;
		}
		dhcp->tree->root = dhcp->tree->root->child[gowhere];
		dhcp->tree->root->isTaken = 0;
	}
	
	return SUCCESS;
	*/
}

static status_t RecFreeIP(trie_node_t *node, uint32_t *ip_to_free, uint32_t height)
{
	uint32_t gowhere = 0;
	status_t stat = SUCCESS ;

	if (NULL == node)
	{
		printf("IP wasnt allocated to begin with!\n");
		return FAILURE;
	}

	if (0 == height)
	{
		if (node->isTaken)
		{
			node->isTaken = !TAKEN;
			return SUCCESS;
		}
		return DOUBLE_FREE;
		
	}

	gowhere = (*ip_to_free >> (height - 1)) & 1;

	stat = RecFreeIP(node->child[gowhere], ip_to_free, height -1);

	UpdateAllocated(node);
	return stat;


}


static status_t IPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat)
{
    
   	*stat = RecIPProvide(node, requested_ip_address, height, stat);

    if (OCCUPIED == *stat)
    {
        *stat = NoIPProvided(node, requested_ip_address, height, stat);
    }

    return *stat;
}

static status_t RecIPProvide(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat)
{
    uint32_t where = (*requested_ip_address >> height) & 1;
    
    if (0 == height)
    {
        node->isTaken = TAKEN;
        return SUCCESS;
    }

    if (NULL == node->child[where])
    {
        node->child[where] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
        if (NULL == node->child[where])
        {
            return FAILURE;
        }
    }

    else if (node->child[where]->isTaken)
    {
        return OCCUPIED;
    }

   *stat = RecIPProvide(node->child[where],requested_ip_address, height -1, stat);
   if (SUCCESS == *stat)
   {
        UpdateAllocated(node);
   }

   return *stat;
}

static status_t NoIPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat)
{
                                                   
    if (0 == height)
    {
        node->isTaken = TAKEN;
   	 	UpdateAllocated(node);
        return SUCCESS;
    }

    if (NULL == node->child[LEFT])
    {
        node->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
        if (NULL == node->child[LEFT])
        {
            return FAILURE;
        }
    }
   
    if (node->child[LEFT]->isTaken != TAKEN)
    {
        *requested_ip_address &= ~(1 << (height));
       
        *stat = NoIPProvided(node->child[LEFT], requested_ip_address, height -1, stat);
        
        UpdateAllocated(node);
        return *stat;
    }

    if (NULL == node->child[RIGHT])
    {
        node->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
        if (NULL == node->child[RIGHT])
        {
            return FAILURE;
        }
        
    }

    *requested_ip_address |= (1 << (height));
    
    *stat = NoIPProvided(node->child[RIGHT], requested_ip_address, height -1, stat);
    
    UpdateAllocated(node);
    return *stat;
}

static void UpdateAllocated(trie_node_t *root)
{
    
    if((NULL != root->child[LEFT]) && (root->child[LEFT]->isTaken)) 
    {
    	if(NULL != (root->child[RIGHT]) && (root->child[RIGHT]->isTaken)) 
    	{
    		root->isTaken = TAKEN;
    	}
    } 
}


static status_t IsIPValid(dhcp_t *dhcp, const char *ip_address)
{
    uint32_t convert_ip = 0;                        
    uint32_t net_adr = (dhcp->network_address) & (dhcp->mask);

    if (1 != inet_pton(AF_INET, ip_address, &convert_ip))
    	return FAILURE;
    
    convert_ip = ntohl(convert_ip);

    convert_ip &= (dhcp->mask);
    
    return ((convert_ip ^ net_adr) == 0);

}

static status_t IsIpValid(dhcp_t *dhcp, uint32_t requested_ip_address)
{
    uint32_t masked_ip = requested_ip_address & dhcp->mask;
    return (0 == (masked_ip ^ (dhcp->network_address & dhcp->mask)));
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


static status_t InitLeft(trie_node_t *root, uint32_t height)
{
	while(height > 0)
	{
		root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
		if(NULL == root->child[LEFT])
		{
			return FAILURE;
		}

		root = root->child[LEFT];
		--height;
	}
	root->isTaken = TAKEN;
	return (root->isTaken == SUCCESS);

	

	
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

	 ;
	
	*/
}


static status_t InitRight(trie_node_t *root, uint32_t height)
{
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

	return InitRight(root->child[RIGHT], height - 1);

	

	/*
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

