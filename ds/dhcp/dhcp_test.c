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
    
    Test();

    return 0;
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

    new = DHCPCreate("216.202.192.66", 29);
    TEST_NOT_NULL(new);
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

    DHCPDestroy(new); 
}
void TestAllocate()
{
    dhcp_t *dhcp = NULL;
    char *network_address = "216.202.192.66";

    char *req1_address = "216.202.192.66";
    char *req2_address = "216.202.192.66";
    char result1[16] = {0};
    char result2[16] = {0};
    char result3[16] = {0};
    char result4[16] = {0};
    char result5[16] = {0};

    dhcp = DHCPCreate(network_address,24);
    TEST_NOT_NULL(dhcp);
    printf("created! 216.202.192.66/24\nfree count: %ld\n", DHCPCountFree(dhcp));

    DHCPAllocateIP(dhcp, req1_address, result1);
    printf("\nResult1 = %s\n", result1);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));
    
    DHCPAllocateIP(dhcp, NULL, result4);
    printf("\nno_ip, Result4 = %s\n", result4);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));

    CONDITION_TEST(0, DHCPAllocateIP(dhcp, req2_address, result2));
    printf("\nResult2 = %s\n", result2);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));
    
    CONDITION_TEST(0, DHCPAllocateIP(dhcp, NULL, result3));
    printf("\nResult3 = %s\n", result3);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));
    printf("free count: %ld\n", DHCPCountFree(dhcp));

    CONDITION_TEST(0, DHCPAllocateIP(dhcp, NULL, result4));
    printf("\nResult4 = %s\n", result4);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));

   
  
    CONDITION_TEST(0, DHCPAllocateIP(dhcp, NULL, result5));
    printf("\nResult5 = %s\n", result5);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));

     CONDITION_TEST(0, DHCPFreeIP(dhcp, result2));

    CONDITION_TEST(1, DHCPFreeIP(dhcp, result2));
    CONDITION_TEST(248, DHCPCountFree(dhcp));
    printf("freed, count: %ld\n", DHCPCountFree(dhcp));

    DHCPAllocateIP(dhcp, req2_address, result2);
    printf("\nResult2 = %s\n", result2);
    printf("alllocated ! free count: %ld\n", DHCPCountFree(dhcp));

    DHCPFreeIP(dhcp, "216.202.192.1");
    printf("freed? count: %ld\n", DHCPCountFree(dhcp));
    CONDITION_TEST(248, DHCPCountFree(dhcp));
    
    DHCPDestroy(dhcp);
    printf("\nPASSED\n");

}
   




