#include <stdlib.h> /* size_t  */
#include <stdio.h> /* printf */
#include <assert.h> /* asserts */

#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))

#define ALIGN(adrs_size) (adrs_size - ((adrs_size + WORD_SIZE)&(WORD_SIZE - 1)))

#define ZERO (0ul)


struct fsa
{
	size_t pool;
};

/* eager initialization */
static void *MemSetZero(void *s, size_t n);


size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return(sizeof(fsa_t) + (ALIGN(block_size) * num_of_blocks))
}

/*initialize the FSA, eager initialization of all blocks? */
fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	
	block_size = WORD_SIZE + ALIGN(block_size);
	memory = MemSetZero(memory, mem_size * block_size);

	fsa->pool = (size_t)memory;

	return memory;

}

void *FSAAlloc(fsa_t *pool)
{
	void *ptr = NULL;
	ptr = pool->pool;
	pool->pool -=WORD_SIZE;

	return ptr;
}


size_t FSACountFree(const fsa_t *pool)
{
	return pool->pool / WORD_SIZE;
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