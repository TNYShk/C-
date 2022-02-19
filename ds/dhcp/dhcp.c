/**********************************************
 * DHCP - Source File                         *
 * Developer: Tanya			                  *
 *          Feb 15, 2022                      *
 *                                            *
 * Reviewer: Ephraim  	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* memset */
#include <arpa/inet.h> /*IP - str conversion */
#include <byteswap.h> /* endiannes*/

#include "dhcp.h" /* program's header */


#define BITS (sizeof(char) * sizeof(int) * sizeof(size_t))
#define TAKEN (1)
#define ALL_OCCUPIED_BELOW (3)
#define GREATSUCCESS (1)
#define SERVER_ADRS(mask_size) ((1u << (BITS - (mask_size))) - 1u)
#define BROADCAST_ADR(mask_size) ((1u << (BITS - (mask_size))) - 2u)



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
	uint32_t subnet_mask_size; 
	uint32_t network_address; 
};


/* Service Funcs */
typedef status_t (*req_func_t)(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat);
static status_t IPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat);
static status_t NoIPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat);
static status_t RecIPProvide(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat);

static status_t CreateLeftSubTrie(trie_node_t *root, uint32_t height);
static status_t CreateRightSubTrie(trie_node_t *root, uint32_t height);
static void Destroy(trie_node_t *trie);
static size_t CountRec(trie_node_t *root, uint32_t height);
static status_t IsIPValid(dhcp_t *dhcp, const char *ip_address);
static status_t IsIpValid(dhcp_t *dhcp, uint32_t requested_ip_address);
static void UpdateAllocated(trie_node_t *root);
static status_t RecFreeIP(trie_node_t *node, uint32_t *ip_to_free, uint32_t height);
static void InetPtonNtohl(const char *adrs, uint32_t *ip_result);
static void NotHollyTrinityIP(dhcp_t *dhcp,uint32_t convert_ip);



dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size)
{
	dhcp_t *dhcp = NULL;
	uint32_t inet = 0;

	assert(30 > subnet_mask_size);
	assert(NULL != network_address);

	dhcp = (dhcp_t *)calloc(1, sizeof(dhcp_t));
	if (NULL == dhcp)
	{
		return NULL;
	}

	dhcp->tree = (trie_t *)calloc(1, sizeof(trie_t));
	if (NULL == dhcp->tree)
	{
		free(dhcp);
		dhcp = NULL;
		return NULL;
	}
	dhcp->tree->root = (trie_node_t *)calloc(1,sizeof(trie_node_t));
	if (NULL == dhcp->tree->root)
	{
		free(dhcp->tree);
		dhcp->tree = NULL;
		
		free(dhcp);
		dhcp = NULL;

		return NULL;
	}

	InetPtonNtohl(network_address, &inet);
	
    dhcp->subnet_mask_size = subnet_mask_size; 
	dhcp->tree->height = BITS - dhcp->subnet_mask_size;
    dhcp->network_address = inet & (-1)<<dhcp->tree->height;

	if (SUCCESS != CreateLeftSubTrie(dhcp->tree->root, dhcp->tree->height))
	{
		DHCPDestroy(dhcp);
	}
	
	if (SUCCESS != CreateRightSubTrie(dhcp->tree->root, dhcp->tree->height))
	{
		DHCPDestroy(dhcp);
	}
	
	return dhcp;
}


void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	if (NULL != dhcp->tree->root)
	{
		Destroy(dhcp->tree->root->child[LEFT]);
		Destroy(dhcp->tree->root->child[RIGHT]);
	
		free(dhcp->tree->root);
		dhcp->tree->root = NULL;
	}
	
	free(dhcp->tree);
	dhcp->tree = NULL;
	
	memset(dhcp, 0, sizeof(dhcp_t));

	free(dhcp);
	dhcp = NULL;
}


status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip_address, char *result_ip_address)
{
	status_t alloc_stat = SUCCESS;
	unsigned int is_provided = 0;
	uint32_t req_ip_adrs = 0;

	static req_func_t IP_LUT[] = {&NoIPProvided, &IPProvided};

	assert(NULL != dhcp);
  	assert(NULL != result_ip_address);

  	if(dhcp->tree->root->isTaken)
  	{
  		return FAILURE;
  	}

  	if ((is_provided = (NULL != requested_ip_address)))
  	{
		InetPtonNtohl(requested_ip_address, &req_ip_adrs);
    	assert(IsIpValid(dhcp, req_ip_adrs));
    }
    
   	alloc_stat =  IP_LUT[is_provided](dhcp->tree->root, &req_ip_adrs, (dhcp->tree->height) - 1, &alloc_stat);
  	if (SUCCESS != alloc_stat)
  	{
  		return alloc_stat;
  	}
  
  	req_ip_adrs |= dhcp->network_address;
  	req_ip_adrs = bswap_32(req_ip_adrs);

  	return (SUCCESS == inet_ntop(AF_INET, &req_ip_adrs, result_ip_address, BITS >> 1));

}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t max_available = 0;
	assert(NULL != dhcp);

	max_available = 1<<(BITS - dhcp->subnet_mask_size);
	return max_available -= CountRec(dhcp->tree->root, dhcp->tree->height);
}


status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_address_to_free)
{
	uint32_t convert_ip = 0;
	assert(NULL != dhcp);
	
	if (GREATSUCCESS != IsIPValid(dhcp, ip_address_to_free))
  	{
  		return FAILURE;
  	}
  	InetPtonNtohl(ip_address_to_free, &convert_ip);
	assert(IsIpValid(dhcp, convert_ip));

	NotHollyTrinityIP(dhcp, convert_ip);
	
	return RecFreeIP(dhcp->tree->root, &convert_ip, dhcp->tree->height);
}




static void NotHollyTrinityIP(dhcp_t *dhcp,uint32_t convert_ip)
{
	uint32_t mask = (1 << (BITS - dhcp->subnet_mask_size)) - 1;
	
	assert(0 != (mask & convert_ip));
    assert(SERVER_ADRS(dhcp->subnet_mask_size) != (mask & convert_ip));
    assert(BROADCAST_ADR(dhcp->subnet_mask_size) != (mask & convert_ip));
}

static status_t RecFreeIP(trie_node_t *node, uint32_t *ip_to_free, uint32_t height)
{
	uint32_t gowhere = (*ip_to_free >> height) & 1;
	status_t stat = SUCCESS;

	if (NULL == node)
	{
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
	 
	stat = RecFreeIP(node->child[gowhere], ip_to_free, height -1);
	UpdateAllocated(node);
	
	return stat;
}

static void InetPtonNtohl(const char *adrs, uint32_t *ip_result)
{
	assert(1 == inet_pton(AF_INET, adrs, ip_result));
	*ip_result = ntohl(*ip_result);
}

static status_t IPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat)
{
	
   	*stat = RecIPProvide(node, requested_ip_address, height, stat);

    if (ALL_OCCUPIED_BELOW == *stat)
    {
        *stat = NoIPProvided(node, requested_ip_address, height, stat);
    }

    return *stat;
}

static status_t RecIPProvide(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat)
{
    uint32_t where = (*requested_ip_address >> height) & 1;
   
    if (0 == height + 1)
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

   if (node->child[where]->isTaken)
    {
        return ALL_OCCUPIED_BELOW;
    }

 	*stat = RecIPProvide(node->child[where],requested_ip_address, height - 1, stat);
 	UpdateAllocated(node);
  
   	return *stat;
}


static status_t NoIPProvided(trie_node_t *node, uint32_t *requested_ip_address, uint32_t height, status_t *stat)
{
                                        
    if (0 == height + 1)
    {
       	node->isTaken = TAKEN;
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
   
    if (TAKEN != node->child[LEFT]->isTaken)
    {
        *requested_ip_address &= ~(1 << height);
        *stat = NoIPProvided(node->child[LEFT], requested_ip_address, height - 1, stat); 
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

    *requested_ip_address |= (1 << height);
    *stat = NoIPProvided(node->child[RIGHT], requested_ip_address, height - 1, stat);
    UpdateAllocated(node);

    return *stat;
}

static void UpdateAllocated(trie_node_t *root)
{
    root->isTaken =
        ((NULL != root->child[LEFT]) && root->child[LEFT]->isTaken) &&
        			((NULL != root->child[RIGHT]) && root->child[RIGHT]->isTaken);
}

static status_t IsIPValid(dhcp_t *dhcp, const char *ip_address)
{
    uint32_t convert_ip = 0;  
    uint32_t mask = (-1)<< (BITS - dhcp->subnet_mask_size);                      
    uint32_t net_adr = (dhcp->network_address) & mask;

    InetPtonNtohl(ip_address, &convert_ip);
    return (0 == ((convert_ip &= mask) ^ net_adr));
}

static status_t IsIpValid(dhcp_t *dhcp, uint32_t requested_ip_address)
{
    uint32_t mask = (-1)<< (BITS - dhcp->subnet_mask_size);
    uint32_t masked_ip = requested_ip_address & mask;
    return (0 == (masked_ip ^ (dhcp->network_address & mask)));
}

static size_t CountRec(trie_node_t *root, uint32_t height)
{
	size_t counter = 0;
	
	if (TAKEN == root->isTaken)
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
    
    memset(root, 0, sizeof(trie_node_t));
    free(root);
    root = NULL;
}


static status_t CreateLeftSubTrie(trie_node_t *root, uint32_t height)
{
	if(0 == height)
	{
		root->isTaken = TAKEN;
		return SUCCESS;
	}

	root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if (NULL == root->child[LEFT])
	{
		return FAILURE;
	}

	return CreateLeftSubTrie(root->child[LEFT], height -1);
	
}


static status_t CreateRightSubTrie(trie_node_t *root, uint32_t height)
{
	size_t idx = 0;

	for(; idx < height -1; ++idx)
	{
		root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
		if(NULL == root->child[RIGHT])
			return FAILURE;

		root = root->child[RIGHT];
	}

	root->child[LEFT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if(NULL == root->child[LEFT])
		return FAILURE;

	root->child[RIGHT] = (trie_node_t *)calloc(1, sizeof(trie_node_t));
	if(NULL == root->child[RIGHT])
		return FAILURE;
	
	root->child[LEFT]->isTaken = TAKEN;
	root->child[RIGHT]->isTaken = TAKEN;
	root->isTaken = ALL_OCCUPIED_BELOW;

	return (NULL == root);
}

