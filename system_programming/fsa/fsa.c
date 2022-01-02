#include <stdlib.h> /* size_t  */
#include <stdio.h> /* printf */
#include <assert.h> /* asserts */

#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))

#define ALIGNDOWN(adrs) (adrs- ((adrs + WORD_SIZE)&(WORD_SIZE - 1)))

#define ALIGNUP(a) ((a + WORD_SIZE - 1) & (-WORD_SIZE))

#define ZERO (0ul)


struct fsa
{
	long start;
	
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
	char *runner = NULL;
	char *rear = NULL;
	size_t index =1;
	assert(0 < mem_size);
	assert(NULL != memory);

	block_size = ALIGNUP(block_size);

	((fsa_t*)memory)->start = sizeof(fsa_t);
	
	runner = ((fsa_t*)memory)->start + (char *)memory;
	rear = (char *)memory + mem_size - block_size;
	
	while(runner < rear)
	{
	 *(long *)runner = index * block_size;
	 runner += block_size;
	 ++index;
	 
	}
	*(long *)runner = (long)memory - (long)runner;

	return (fsa_t*)memory;

}

void *FSAAlloc(fsa_t *pool)
{
	char *ptr = NULL;

	assert(NULL != pool);

	if (pool->start > 0)
	{
		ptr = (char *)pool + pool->start;
		pool->start += *(long *)ptr;
	}
	
	
	return ptr;
}


size_t FSACountFree(const fsa_t *pool)
{
	const char *runner = (const char *)pool;
	size_t counter = 0;

	assert(NULL != pool);
	

	while(runner != ((char *)pool + pool->start ))
	{
		++counter;
		runner += pool->start;
	}
return counter;
}



void FSAFree(fsa_t *pool, void *ptr)
{
  
    assert(NULL != pool);
    assert(NULL != ptr);

    *(long *)ptr = (char *)pool + pool->start - (char *)ptr;
    pool->start = (long)ptr - (long)pool;
}





/*
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
*/