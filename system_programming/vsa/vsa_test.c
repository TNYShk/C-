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
    size_t ss = 0;
    void *aloc_ptr = malloc(120 + sizeof(vsa_t*));
    vsa_t *test = NULL;
    
    ss = ALIGNUP(120);
    test = VSAInit(aloc_ptr, ss); 
   
    free(aloc_ptr);
    return 0;
}
