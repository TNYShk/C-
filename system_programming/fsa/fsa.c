/********************************
* FSA - Source Code             *
* Developer: Tanya              *
* 2022-01-03                    *
*                               *
*      Reviewed by Erez  	 	*
*********************************/
#include <stdlib.h> /* size_t  */
#include <assert.h> /* asserts */

#include "fsa.h" /* header file */

#define WORD_SIZE (sizeof(size_t))

#define ALIGNDOWN(a) (a - ((a + WORD_SIZE) & (WORD_SIZE - 1)))
#define ALIGNUP(a) ((a + WORD_SIZE - 1) & -(WORD_SIZE))
#define ZERO (0l)


struct fsa
{
	long start;
};


size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return (sizeof(fsa_t) + (ALIGNUP(block_size) * num_of_blocks));
}


fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size)
{
	char *runner = NULL;
	
	assert(NULL != memory);

	block_size = WORD_SIZE + ALIGNDOWN(block_size);

	((fsa_t*)memory)->start = sizeof(fsa_t);

	runner = ((fsa_t*)memory)->start + (char *)memory;

	mem_size -= sizeof(fsa_t);
	
	while(mem_size > block_size)
	{
	 	*(long *)runner = block_size;
	 	runner += block_size;
	 	mem_size -=block_size;
	}
	
	*(long *)runner = (long)memory - (long)runner;
	
	return (fsa_t*)memory;
}


void *FSAAlloc(fsa_t *pool)
{
	char *ptr = NULL;

	assert(NULL != pool);

	if (pool->start > ZERO)
	{
		ptr = (char *)pool + pool->start;
		pool->start += *(long *)ptr;
	}
	
	return ptr;
}


size_t FSACountFree(const fsa_t *pool)
{
	
	const char *runner = (const char *)pool + pool->start;
    size_t counter = 0;

    assert(NULL != pool);

    while((long)pool != (long)runner)
    {
        ++counter;
        runner += *(long *)runner;
    }

    return counter;
}


void FSAFree(fsa_t *pool, void *block)
{
  
    assert(NULL != pool);
    assert(NULL != block);

    *(long *)block = (long)pool + pool->start - (long)block;
    pool->start = (long)block - (long)pool;
}







