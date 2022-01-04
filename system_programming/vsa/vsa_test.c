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

void VSAPrint(vsa_t *vsa);

int main(void)
{
    size_t ss = 124;
    void *aloc_ptr = malloc(124);
    vsa_t *test = NULL;

    void *alloc_test = NULL;
   /* printf("adrs of aloc_ptr id %p \n", aloc_ptr);*/
    ss = ALIGNUP(124);
    printf("aligned up is %ld\n", ss);
    test = VSAInit(aloc_ptr, ss); 

    VSAPrint(test);
    ss = VSALargestFreeChunck(test);
    printf("largest chunk is %ld\n", ss);
    
    alloc_test = VSAAlloc(test, 33);
   
    ss = VSALargestFreeChunck(test);
    printf("largest chunk is %ld\n", ss);
    
    VSAPrint(test);
 
    free(aloc_ptr);
    return 0;
}

void VSAPrint(vsa_t *vsa)
{
    void *runner = NULL;
    size_t counter = 0;
    runner = vsa;

    printf("------VSA is:-------\n");
    while (0 != *(long *)runner)
    {
        ++counter;
        printf("%lu. Size is %ld\n", counter, *(long *)runner);
        if (*(long *)runner < 0)
        {
            runner = (void *)((char *)runner + *(long *)runner * (-1) + sizeof(size_t));
        }
        else
        {
            runner = (void *)((char *)runner + *(long *)runner + sizeof(size_t));
        }
    }
}