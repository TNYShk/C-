#include <stdlib.h> /* size_t  */
#include <stdio.h> /* printf */
#include <assert.h> /* asserts */

#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))

#define ALIGNDOWN(adrs) (adrs- ((adrs + WORD_SIZE)&(WORD_SIZE - 1)))

#define ALIGNUP(a) (a + WORD_SIZE - 1) & -(WORD_SIZE)

#define ZERO (0ul)


struct fsa
{
	size_t start;
	
};

/* eager initialization */
static void *MemSetZero(void *s, size_t n);

/*
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return(sizeof(fsa_t) + WORD_SIZE + (ALIGNDOWN(block_size) * num_of_blocks));
}*/

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return(sizeof(fsa_t) + (ALIGNUP(block_size) * num_of_blocks));
}


fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	size_t num_of_blocks = 0;
	char *runner = NULL;

	fsa = (fsa_t*)memory + sizeof(fsa);
	

	runner = fsa->start + (char *)memory;

	block_size = ALIGNUP(block_size);
	num_of_blocks = (mem_size- sizeof(fsa)) / block_size;

	while(num_of_blocks)
	{
	 runner += block_size;
	 --num_of_blocks;
	}
	
	return fsa;

}

void *FSAAlloc(fsa_t *pool)
{
	char *ptr = NULL;

	assert(NULL != pool);

	ptr = (char *)pool + pool->start;
	pool->start += *(size_t*)ptr;
	
	return ptr;
}


size_t FSACountFree(const fsa_t *pool)
{
	size_t counter = 0;
	assert(NULL != pool);
	char *runner = pool->start;

	while(runner != (pool->start * pool->block_size))
	{
		++counter;
		runner += pool->block_size;

	}
return counter;
}


void FSAFree(fsa_t *pool, void *ptr)
{
    assert(NULL != pool);
    assert(NULL != ptr);

    *(size_t *)ptr = pool->start + pool->block_size - (size_t)ptr;

    pool->top = (size_t)ptr - (size_t)pool;
}






static void *MemSetZero(void *s, size_t n)
{
	size_t word = ZERO;
	char *byte_ptr = NULL;

	size_t toalign = ((size_t)byte_ptr % WORD_SIZE);
	size_t wordalign = n / WORD_SIZE;
	
	assert(NULL != s);

	byte_ptr = s;
	word *= 0x0101010101010101;
	
	while (n)
	{

		if ((wordalign > 0) && (0 == toalign))
		{
			*(size_t *)byte_ptr = word;
			++(*(size_t **)&byte_ptr);
			--wordalign;
			n -= WORD_SIZE;
		}
		else 
		{
			*byte_ptr = (unsigned char)ZERO;
			++byte_ptr;
			--n;
		}
	}
	return s;
}