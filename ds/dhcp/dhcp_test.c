/**********************************
 * DHCP - Source Code          	  *
 * Developer: Tanya               *
 * Feb 10, 2022                   *
 *                                *
 *      reviewed by               *
***********************************/
#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memset                      */
#include <assert.h>    /* assert                      */ 


#include "dhcp.h"
#include "../include/utils.h"


int main(void)
{
    dhcp_t *new = NULL;
    new = DHCPCreate("216.202.192.66", 22);
    DHCPDestroy(new);

    return 0;
}