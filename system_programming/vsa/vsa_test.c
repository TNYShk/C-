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
#include <limits.h> /* for LONG_MAX, LONG_MIN */
#include "vsa.h" /* header file */


#define WORD_SIZE (sizeof(size_t))
#define ALIGNUP(a) ((a + WORD_SIZE - 1) & -(WORD_SIZE))
#define MAGIC (0x666AAA666AAA6666l)
#define STOP (LONG_MIN)
#define NEG_CONVERT (-1)

void VSAPrint(vsa_t *vsa);


int main(void)
{
   
    size_t ss = 0;
    void *aloc_ptr = malloc(128);
    vsa_t *test = NULL;
    void *another = NULL;
    void *alloc_test = NULL;
  
   
    test = VSAInit(aloc_ptr, 128); 
    VSAPrint(test);
    alloc_test = VSAAlloc(test, 33);
    ss = VSALargestFreeChunck(test);
    printf("\tAllocated block, largest chunk available is %ld\n", ss);
    VSAPrint(test);

    another = VSAAlloc(test, 32);
    VSAPrint(test);
   
    
    ss = VSALargestFreeChunck(test);
    printf("\tAllocated another block, largest Chunk available is %ld\n", ss);
    
    printf("\tFreed block\n");
    VSAFree(another);
    VSAPrint(test);
   
    
    ss = VSALargestFreeChunck(test);
    printf("\tPost Free, largest chunk available is %ld\n", ss); 
    VSAFree(alloc_test); 

    ss = VSALargestFreeChunck(test);
    printf("\tPost another free, largest Chunky Monkey is %ld\n", ss); 
   
    VSAPrint(test);
    
    another = VSAAlloc(test, 100);
    ss = VSALargestFreeChunck(test);
    printf("\tAllocated again, now largest chunk is %ld\n", ss); 
    VSAPrint(test);
    /*
    test double free, uses assert WORKS :)
    VSAFree(alloc_test); 
    */
   
    free(aloc_ptr);
    
    return 0;
}











void VSAPrint(vsa_t *vsa)
{
    void *runner = NULL;
    size_t counter = 0;
    runner = vsa;

    printf("------VSA is:-------\n");
    while (STOP != *(long *)runner)
    {
        ++counter;
        printf("%lu. Address of BlockHeader is %p, it contains %ld\n", counter, (void *)runner, *(long *)runner);

        if (*(long *)runner == 0)
        {
            runner = (void *)((char *)runner + WORD_SIZE);
        }
        else if (*(long *)runner < 0)
        {
            runner = (void *)((char *)runner + *(long *)runner * NEG_CONVERT + sizeof(size_t));
        }
        else
        {
            runner = (void *)((char *)runner + *(long *)runner + sizeof(size_t));
        }
    }
    printf("\n");
}