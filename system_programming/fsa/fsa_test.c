#include <stdlib.h> /* size_t  */
#include <stdio.h> /* printf */
#include <assert.h> /* asserts */
#include <string.h>

#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))

static void UnitTestInit();
static void SuggestSizeTest();

int main(void)
{
    SuggestSizeTest();
    /*
    UnitTestInit();
*/

    return 0;
}






static void UnitTestInit(void)
{
    void *pool = malloc(120 + WORD_SIZE);
    size_t number_of_blocks = 5;
    size_t block_size = 20;
    size_t next_offset = 0;
    fsa_t *test = NULL;
    
    memset(pool, 0, 128);
    test = FSAInit(pool, number_of_blocks * (block_size + 4) + WORD_SIZE, block_size);
    
    printf("\nInitializing pool\n");
    
    next_offset = WORD_SIZE;
    printf("Test result for initializing start_offset member: %d\n", (size_t)next_offset == 
                                                *((size_t *)test));
    next_offset += 24 - WORD_SIZE;
    printf("Test result for next index in block 0: %d\n", next_offset ==
                                                *((size_t *)(*((char **)&test) + 8)));
    next_offset += 24 ;
    printf("Test result for next index in block 1: %d\n", next_offset ==
                                                *((size_t *)(*((char **)&test) + 32)));
    next_offset += 24;
    printf("Test result for next index in block 2: %d\n", next_offset ==
                                                *((size_t *)(*((char **)&test) + 56)));
    next_offset += 24;
    printf("Test result for next index in block 3: %d\n", next_offset ==
                                                *((size_t *)(*((char **)&test) + 80)));
    next_offset = 0;
    printf("Test result for next index in block 4: %d\n", next_offset ==
                                                *((size_t *)(*((char **)&test) + 104)));
    
    free(pool);
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

    printf("asserts are good test passed" );
}