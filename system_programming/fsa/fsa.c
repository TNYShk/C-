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





/* no in use*/
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

/* ver1
size_t FSACountFree(const fsa_t *pool)
{
	
	size_t runner =  *(long *)pool->start;
	size_t counter = 0;

	assert(NULL != pool);
	

	while(runner != ZERO)
	{
		++counter;
		runner = *((long *)((long)pool + sizeof(fsa_t) + runner));
	}
return counter;
}


ver2
size_t FSACountFree(const fsa_t *pool)
{
	const char *runner = (const char *)pool;
	size_t counter = 0;

	assert(NULL != pool);

	while( (long)pool != (long)(runner += *(long *)runner) )
	{
		++counter;
	}
	
	return counter;
}

*/
