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
#include <arpa/inet.h>

#include "dhcp.h"
#include "../include/utils.h"


int main(void)
{
    dhcp_t *new = NULL;

    /*
    char *string = (char *)malloc(sizeof(char) * 100);
    uint32_t ans = 0;

    inet_pton(AF_INET, "255.255.255.255", &ans );
    printf("ans is %d\n", ans);
    inet_ntop(AF_INET, &ans,string, 100);
    printf("string %s\n", string);
    free(string);
    */
    new = DHCPCreate("83.130.23.36", 29);

    printf("free count: %ld\n", DHCPCountFree(new));
    DHCPDestroy(new);
    
    return 0;
}