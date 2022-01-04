/**********************************************
 * Variable-Size Allocator - Test File      *
 * Developer:  Tanya                          *
 * Written:   04/01/2022                      *
 * Reviewer: __________                       *
 *                                            *
 **********************************************/
#include <stdlib.h> /* size_t  */
#include <assert.h> /* asserts */
#include <stdio.h> /* printf */

#include "vsa.h" /* header file */


#define WORD_SIZE (sizeof(size_t))
#define ALIGNUP(a) ((a + WORD_SIZE - 1) & -(WORD_SIZE))

int main(void)
{
    size_t ss = 124;
    void *aloc_ptr = malloc(124);
    vsa_t *test = NULL;
    printf("adrs of aloc_ptr id %p \n", aloc_ptr);
    ss = ALIGNUP(124);
    printf("aligned up is %ld\n", ss);
    test = VSAInit(aloc_ptr, ss); 

    printf("post init: adrs of aloc_ptr id %p \n", aloc_ptr);
    printf("post init: adrs of vsa test id %p \n", test);
    
    ss = VSALargestFreeChunck(test);
    printf("largest chunk is %ld\n", ss);
  

    free(aloc_ptr);
    return 0;
}
