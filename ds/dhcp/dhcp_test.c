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
#include <byteswap.h>

#include "dhcp.h"
#include "../include/utils.h"

void TestAllocate();
void Test();
void Test_pton();

int main(void)
{
  
   
    TestAllocate();
    /*
     Test_pton();
    printf("\n\ttest1\n");
    Test();*/

    return 0;
}

void Test_pton()
{
    char *req1_address = "216.202.192.66";
    char *req2_address = "216.202.192.0";
    uint32_t convert_ip = 0;
     char result1[50] = {0};
    char result2[50] = {0};

    inet_pton(AF_INET, req1_address, &convert_ip);
    printf("coinverted to uint: %u\n", convert_ip);
    inet_ntop(AF_INET, &convert_ip, result1, 16);
    printf("ip to free is %s\n", result1);

    convert_ip = ntohl(convert_ip);
    printf("flipped? uint: %u\n", convert_ip);
    inet_ntop(AF_INET, &convert_ip, result2, 16);
    printf("ip to free is %s\n", result2);

}

void Test()
{
    dhcp_t *new = NULL;
    
    char *req1_address = "216.202.192.66";
    char *req2_address = "216.202.192.66";
    char result1[50] = {0};
    char result2[50] = {0};
    char result3[50] = {0};
    char result4[50] = {0};

    new = DHCPCreate("216.202.192.66", 24);
    printf("Created! 216.202.192.66/24 \n");

    printf("free count: %ld\n", DHCPCountFree(new));

    DHCPAllocateIP(new, req1_address, result1);
    printf("\n1 Resulted IP = %s\n", result1);
    printf("allocated, free count: %ld\n", DHCPCountFree(new));

    DHCPAllocateIP(new, req2_address, result2);
    printf("\n2 Resulted IP = %s\n", result2);
    printf("allocated, free count: %ld\n", DHCPCountFree(new));
   
    DHCPAllocateIP(new, NULL, result3);
    printf("\n3 Resulted IP = %s\n", result3);
    printf("free count: %ld\n", DHCPCountFree(new));

    DHCPFreeIP(new, "216.202.192.2");
    printf("freed? count: %ld\n", DHCPCountFree(new));
   

    DHCPAllocateIP(new, NULL, result4);
    printf("\n3.4 Resulted IP = %s\n", result4);
    printf("free count: %ld\n", DHCPCountFree(new));

    DHCPAllocateIP(new, "240.202.192.0", result4);
    printf("\n4 Resulted IP = %s\n", result4);
    printf("free count: %ld\n", DHCPCountFree(new));
    /* 
    DHCPAllocateIP(new, req2_address, result2);
    DHCPAllocateIP(new, NULL, result3);
    printf("\nResult1 = %s\n", result1);
    
    printf("\nResult3 = %s\n", result3);
     printf("free count: %ld\n", DHCPCountFree(new));
    /*DHCPFreeIP(new,"216.202.192.66");
     printf("free count: %ld\n", DHCPCountFree(new));
   /*printf("%d\n", IsIPValid(new, "216.202.192.0"));*/
   
    DHCPDestroy(new); 
}
void TestAllocate()
{
    dhcp_t *dhcp = NULL;
    char *network_address = "216.202.192.66";

    char *req1_address = "216.202.192.66";
    char *req2_address = "216.202.192.66";
    char *bad_adr = "192.200.95.9";
    char result1[50] = {0};
    char result2[50] = {0};
    char result3[50] = {0};
    char result4[50] = {0};
    char result5[50] = {0};

    dhcp = DHCPCreate(network_address,24);
    printf("created! free count: %ld\n", DHCPCountFree(dhcp));

    DHCPAllocateIP(dhcp, req1_address, result1);
    printf("\nResult1 = %s\n", result1);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));
    
    DHCPAllocateIP(dhcp, NULL, result4);
    printf("\nno_ip, Result4 = %s\n", result4);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));

    DHCPAllocateIP(dhcp, req2_address, result2);
    printf("\nResult2 = %s\n", result2);
     printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));
    
    DHCPAllocateIP(dhcp, NULL, result3);
    printf("\nno_ip Result3 = %s\n", result3);
     printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));
    
    
   
    printf("free count: %ld\n", DHCPCountFree(dhcp));

    
    DHCPAllocateIP(dhcp, NULL, result4);
    printf("\nResult4 = %s\n", result4);
     printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));

   
    DHCPAllocateIP(dhcp, NULL, result5);
    printf("\nResult5 = %s\n", result5);
     printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));

    DHCPFreeIP(dhcp, result2);
    DHCPFreeIP(dhcp, result2);
    printf("freed? count: %ld\n", DHCPCountFree(dhcp));

    DHCPAllocateIP(dhcp, req2_address, result2);
    printf("\nResult2 = %s\n", result2);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));


    DHCPDestroy(dhcp);
}
   




