/**********************************************
 * Variable-Size Allocator - Source File      *
 * Developer:  Tanya                          *
 * Written:   05/01/2022                      *
 * Reviewer: Nurit                            *
 *                                            *
 **********************************************/
#include <stdlib.h> /* size_t, labs  */
#include <assert.h> /* asserts */
#include <limits.h> /* LONG_MIN */

#include "vsa.h" /* header file */


#define ALIGNUP(a) ( (a - 1) + (WORD_SIZE) - ((a - 1) & (WORD_SIZE - 1)) )
#define WORD_SIZE (sizeof(size_t))
#define MAGIC (0x666AAA666AAA6666l)
#define STOP (LONG_MIN)
#define NEG_CONVERT (-1)
#define ZERO (0l)

enum status
{
	END,
	CONTINUE
};

struct vsa
{
	long start;

#ifdef DEBUG
	long magic;
#endif

};


/*** Service funcs ***/
static int DefragPool(vsa_t *pool);
static vsa_t *GetNext(vsa_t *pool);


vsa_t *VSAInit(void *pool, size_t mem_size)
{
	char *runner = NULL;

	assert (NULL != pool);
	assert (mem_size >= WORD_SIZE * WORD_SIZE);
	
	mem_size -= sizeof(vsa_t);
	runner = (char *)pool + mem_size;
	
	((vsa_t *)runner)->start = STOP;
	((vsa_t *)pool)->start = mem_size - sizeof(vsa_t);
	
#ifdef DEBUG
	pool->magic = MAGIC;
#endif

	return (vsa_t *)pool;
}


void VSAFree(void *block)
{

	if (NULL != block) 
	{

#ifdef DEBUG
		assert(*((long *)((char *)block)->magic  == MAGIC));    
#endif
		assert(*(long *)((char *)block - sizeof(vsa_t)) < ZERO);

		*(long *)((char *)block - sizeof(vsa_t)) *= NEG_CONVERT;
	}
}


void *VSAAlloc(vsa_t *pool, size_t alloc_size)
{
	vsa_t *allocated = pool;
	
	assert(NULL != pool);
	assert(ZERO < alloc_size);
	
	alloc_size = ALIGNUP(alloc_size) + sizeof(vsa_t);

	while (allocated->start != STOP)
	{
		if (allocated->start > ZERO)
		{
			while ( ((size_t)allocated->start < alloc_size) && DefragPool(allocated) );
		
			if ( (size_t)allocated->start >= alloc_size )
			{
				long size = allocated->start;

				allocated->start = NEG_CONVERT * ((long)alloc_size - sizeof(vsa_t));

				*(long *)((char *)allocated + alloc_size ) = size - alloc_size;

				*(char **)&allocated += sizeof(vsa_t);
#ifdef DEBUG
	allocated->magic = MAGIC;
#endif
				return allocated;
			}
		}

		allocated = GetNext(allocated);		
	}

	return NULL;	
}



size_t VSALargestFreeChunck(vsa_t *pool)
{
	long chunk = ZERO;

	while (pool->start != STOP)
	{
		DefragPool(pool);

		if(pool->start >= chunk)
		{
			chunk = pool->start;
		}	

		pool = GetNext(pool);
			
	}

	return chunk - sizeof(vsa_t);
}
	  
	
static vsa_t *GetNext(vsa_t *pool)
{
	*(char **)&pool += labs(pool->start) + sizeof(vsa_t);
	
	return pool;
}

static int DefragPool(vsa_t *pool)
{
	vsa_t *slow = pool;
	vsa_t *fast = GetNext(slow);
	
	if ( (slow->start >= ZERO) && (fast->start >= ZERO) )
	{
		slow->start += fast->start + sizeof(vsa_t);
		pool = slow;

		return CONTINUE;
	}
					
	return END;
}




	
