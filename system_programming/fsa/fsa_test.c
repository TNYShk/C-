/********************************
* FSA - Source Code             *
* Developer: Tanya              *
* 2022-01-03                    *
*                               *
*      Reviewed by Erez         *
*********************************/
#include <stdlib.h> /* size_t  */
#include <stdio.h> /* printf */
#include <assert.h> /* asserts */
#include <string.h> /* memset */

#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))


static void UnitTestInit();
static void SuggestSizeTest();


int main(void)
{
    
    SuggestSizeTest();
    UnitTestInit();

    return 0;
}


static void SuggestSizeTest()
{
    size_t num_of_blocks = 5;
    size_t block_size = 19;
    size_t mem_size = 0;

    mem_size = FSASuggestSize(num_of_blocks, block_size);
    printf("given user's wishes for block size %ld * %ld, \n",block_size, num_of_blocks);
    printf("total memory allocated should be %ld bytes\n", mem_size );
    assert(mem_size = 128);
    num_of_blocks = 10;
    block_size = 13;

    mem_size = FSASuggestSize(num_of_blocks, block_size);
    printf("given user's wishes for block size %ld * %ld, \n",block_size, num_of_blocks);
    printf("total memory allocated should be %ld bytes\n", mem_size );
    assert(mem_size = 168);

    printf("asserts are good test passed\n" );
}


static void UnitTestInit(void)
{
    void *pool = malloc(120 + WORD_SIZE);
    size_t number_of_blocks = 5;
    size_t block_size = 20;
    size_t next_offset = 0;
    
    fsa_t *test = NULL;
    void *test_ptr = NULL;
    void *test2 = NULL;
    memset(pool, 0, 128);
    test = FSAInit(pool, number_of_blocks * (block_size + 4) + WORD_SIZE, block_size);
    
    printf("\nInitializing pool\n");
    
    next_offset = WORD_SIZE;
    printf("Test result for initialized pool %d\n", (size_t)next_offset == 
                                                *((size_t *)test));
    printf("Available blocks: %ld\n\n", FSACountFree(test));
    test_ptr = FSAAlloc(test);
    printf("allocated one, size is %ld\n", FSACountFree(test));
    test_ptr = FSAAlloc(test);
    printf("allocated one, size is %ld\n", FSACountFree(test));
    test2 = FSAAlloc(test);
    printf("allocated one, size is %ld\n", FSACountFree(test));
    test_ptr = FSAAlloc(test);
    printf("allocated one, size is %ld\n", FSACountFree(test));
    test_ptr = FSAAlloc(test);
    printf("allocated one, size is %ld\n", FSACountFree(test));
    printf("Available blocks: %ld\n", FSACountFree(test));
    assert(0 == FSACountFree(test));
    FSAFree(test, test_ptr);
    printf("freed a block, size is  %ld\n", FSACountFree(test));
    FSAFree(test, test2);
    printf("freed a block, size is  %ld\n", FSACountFree(test));
    assert(0 != FSACountFree(test));
    printf("asserts are good test passed\n" );
    free(pool);
}


