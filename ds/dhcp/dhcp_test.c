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

void TestZiv();
void Test();


int main(void)
{
   
    TestZiv();


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
    printf("Created! 216.202.192.66/29 \n");

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

    /*DHCPFreeIP(new,"216.202.192.66");
    printf("free count: %ld\n", DHCPCountFree(new));*/
    DHCPAllocateIP(new, NULL, result4);
    printf("\n3.4 Resulted IP = %s\n", result4);
    printf("free count: %ld\n", DHCPCountFree(new));

    DHCPAllocateIP(new, "216.202.192.0", result4);
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
void TestZiv()
{
    dhcp_t *dhcp = NULL;
    char *network_address = "216.202.192.66";
    char *req1_address = "216.202.192.66";
    char *req2_address = "216.202.192.66";
    /*char *req3_address = "192.200.95.9";*/
    char result1[16] = {0};
    char result2[16] = {0};
    char result3[16] = {0};


    dhcp = DHCPCreate(network_address,29);

    DHCPAllocateIP(dhcp, req1_address, result1);
    DHCPAllocateIP(dhcp, req2_address, result2);
    DHCPAllocateIP(dhcp, NULL, result3);

    printf("\nResult1 = %s\n", result1);
    printf("\nResult2 = %s\n", result2);
    printf("\nResult3 = %s\n", result3);

    DHCPDestroy(dhcp);
}
   




/*
    uint32_t ans = 4294967288;
    char *string = (char *)malloc(sizeof(char) * 100);
    ans = bswap_32(ans);
     inet_ntop(AF_INET, &ans,string, 100);
    printf("string %s\n", string);
   free(string);


    printf("AND is     %ld\n", (4294967032 & 3637166146));
    printf("AND is     %ld\n", (4294967032 & 3637166151));
    printf("AND not is %ld\n", (4294967032 & 3637166153));
    printf("AND not is %ld\n", (4294967032 & 3637166402));
     

   static int Mask[30] = { pow(2,32),pow(2,31),pow(2,30),
                          pow(2,29),pow(2,28),pow(2,27),
                          pow(2,26),pow(2,25),pow(2,24), 
                          pow(2,23),pow(2,22),pow(2,21),
                          pow(2,20),pow(2,19),pow(2,18),
                          pow(2,17),pow(2,16),pow(2,15),
                          pow(2,14),pow(2,13),pow(2,12),
                          pow(2,11),pow(2,10),pow(2,9),
                          pow(2,8),pow(2,7),pow(2,6),
                          pow(2,5),pow(2,4), pow(2,3)
   };


3637166153 = "216.202.192.73"
3637166152 = "216.202.192.72"
3637166151 = "216.202.192.71" 
3637166146 = "216.202.192.66" 

4294966272 = 255.255.252.0
4294967032 = 255.255.254.248
uint32_t ans = 4194303;
 char *string = (char *)malloc(sizeof(char) * 100);
    ans = bswap_32(ans);
     inet_ntop(AF_INET, &ans,string, 100);
    printf("string %s\n", string);

      free(string);

11011000 -11001010 - 11000000 - 01000010
11111111  11111111   11111100 - 00000000

11011000 216
11001010 202
11000000 192
01000010 66

11011000 216
11001010 202
11000000 192
01000000 64





1000010 66
11000000 192
11001010 202
11011000 216

11011000 216
11001010 202
11000000 192
01000010 66

11011000 216
11001010 202
11000000 192
00000000
*/
 /*
    char *string = (char *)malloc(sizeof(char) * 100);
    uint32_t ans = 4294966272;
    
    inet_pton(AF_INET, "255.255.255.255", &ans );
    printf("ans is %d\n", ans);
    inet_ntop(AF_INET, &ans,string, 100);
    printf("string %s\n", string);
    free(string);
    */