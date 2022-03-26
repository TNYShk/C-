#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */

typedef struct dhcp dhcp_t;

typedef enum status
{
	SUCCESS = 0,
	DOUBLE_FREE = 1,
	FAILURE = 2
}status_t;


/* DESCRIPTION: 
 * Create and Initialize a DHCP module, once initialized will hand out available IP addresses.
 * network, server and broadcast addressed are allocated upon initialization.
 * thus, MAX subnet mask size must be up to 29 
 *  
 * Destroy DHCP() must be called upon end of use.
 * 
 * PARAMS: 
 * const char *network_address - the subnet address to be used by the DHCP
 * subnet_mask_size - number of bits containing the subnet address, must be less than 30.
 * 
 * RETURN:
 * ptr to the newly created DHCP mudule, NULL if memory allocation error.
 *
 * Complexity: O(1) time, O(1) space. */
/* 
dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size);


/* DESCRIPTION: 
 * Destroys the DHCP Module, and frees all the allocated memory
 * Undefined in case of NULL DHCP
 *  
 * Destroy DHCP() must be called upon end of use.
 * 
 * PARAMS: 
 * *dchp - ptr to the DHCP module to destroy
 * 
 * RETURN:
 * none.
 *
 * Complexity: O(n) time, O(1) space. */
/* 
void DHCPDestroy(dhcp_t *dhcp);

/* DESCRIPTION: 
 * Allocates the first available address, or the speficically requested IP address.
 * 
 * 
 * PARAMS: 
 * dhcp - ptr to the DHCP.
 *  requested_ip_address -  address to allocate. May be NULL to indicate no request.
 *   	Requesting an IP address not in the subnet causes UNDEFINED behavior.
 *   	If the requested IP address is unavailable, will provide the first free address instead
 *  result_ip_address - Buffer to store the resulting allocated IP address.
 *   	Must be at least large enough to be able to store 16 bytes of data.
 * 
 * RETURN:
 * status_t as described above
 *
 * Complexity: O(log n) time, O(log n) space. */
status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip_address, char *result_ip_address); 

/*  DESCRIPTION: 
 *  Deallocates an allocated IP address.
 *  Deallocating an IP address not in the subnet causes undefined behavior.
 *  Deallocating a reserved IP address causes undefined behavior.
 * 
 * 
 * PARAMS: 
 * dhcp - ptr to the DHCP.
 *  ip_address_to_free -  address to deallocate. 
 * 
 * RETURN:
 * status_t as described above
 *
 * Complexity: O(log n) time, O(log n) space. */
status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_address_to_free);

/*  DESCRIPTION: 
 *  Counts the available number of IP addresses that 
 *  can be allocated within a subnet.
 * 
 * 
 * PARAMS: 
 * dhcp - ptr to the DHCP.
 *  
 * 
 * RETURN:
 * size_t unallocated IP addresses.
 *
/*time complexity O(n), O(log n) worst case space.*/
size_t DHCPCountFree(const dhcp_t *dhcp); 

#endif /*__DHCP_H__ */
