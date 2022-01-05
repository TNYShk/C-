/**********************************************
 * Variable-Size Allocator - Source File      *
 * Developer:  Tanya                          *
 * Written:   04/01/2022                      *
 * Reviewer: __________                       *
 *                                            *
 **********************************************/
#include <stdlib.h> /* size_t, labs  */
#include <assert.h> /* asserts */
#include <stdio.h>
#include <limits.h> /* for LONG_MAX, LONG_MIN */

#include "vsa.h" /* header file */


#define WORD_SIZE (sizeof(size_t))
#define LONG_SIZE ((long)sizeof(long))

#define ALIGNDOWN(a) (a - ((a + WORD_SIZE) & (WORD_SIZE - 1)))
#define ALIGNUP(a) ((a + WORD_SIZE - 1) & -(WORD_SIZE))
#define ZERO (0l)
#define MAGIC (0x666AAA666AAA6666l)
#define STOP (3)

enum status
{
	FAIL = -1,
	END,
	SUCCESS
};

struct vsa
{
	long start;

#ifdef DEBUG
	long magic;
	
#endif

};



static int DefragPool(vsa_t *pool);
static vsa_t *GetNext(vsa_t *pool);

/*pseudo
	using a runner, create a block guard at the end of the space 
	(runner = mem_size- sizeof(vsa), and put zero value in it *(long*)runner = 0;
	this marks the end.
	now create a Block Header at the start of the pool, 
	its value- is the remaining free space (memsize - 2*sizeof(vsa_t))
*/
vsa_t *VSAInit(void *pool, size_t mem_size)
{
	
	char *runner = NULL;

	assert (NULL != pool);
	assert (mem_size >= WORD_SIZE * WORD_SIZE);
	
	mem_size -= sizeof(vsa_t);
	runner = (char *)pool + mem_size;
	
	((vsa_t*)runner)->start = STOP;
	((vsa_t*)pool)->start = mem_size - sizeof(vsa_t);
	
	return (vsa_t*)pool;

}



/*access given block (-sizeof to access its BH), verify its negative (been used) and turn to positive */
void VSAFree(void *block)
{
	if (NULL != block)
	{
		assert( (((vsa_t *)((char *)block - sizeof(vsa_t)))->start ) < ZERO);
		( ((vsa_t *)((char *)block - sizeof(vsa_t)))->start ) *= -1;
	}
}


void *VSAAlloc(vsa_t *pool, size_t alloc_size)
{
	vsa_t *allocated = pool;
	long temp = allocated->start;
	printf("temp is %ld\n",temp );
	assert(NULL != pool);
	assert(WORD_SIZE < alloc_size);
	
	alloc_size = ALIGNUP(alloc_size) + sizeof(vsa_t);
/*
	if (alloc_size < VSALargestFreeChunck(pool))
	{
		*/
		while( allocated->start < ( (long)(alloc_size )) )
		{
			allocated = GetNext(allocated);
			printf("Alloc_size is %ld\n",alloc_size );
		}

		allocated->start = -1 * ((long)alloc_size - sizeof(vsa_t));

		*(long *)((char *)allocated + alloc_size ) = temp - alloc_size ;

		

	return allocated;	
	
	
}




	



static int DefragPool(vsa_t *pool)
{
	vsa_t *slow = pool;
	vsa_t *fast = GetNext(slow);
	if ( (slow->start > ZERO) && (fast->start > ZERO))
	{
		pool = GetNext(pool);
		return SUCCESS;
	}
					
	return END;
}


size_t VSALargestFreeChunck(vsa_t *pool)
{
	long chunk = ZERO;

	while (pool->start != STOP)
	{
		DefragPool(pool);	
		if(pool->start >= chunk )
		{
			chunk = pool->start;
		}	

	pool = GetNext(pool);
			
	}

	return chunk;
}
	  
	

static vsa_t *GetNext(vsa_t *pool)
{
	*(char **)&pool += labs(pool->start) + sizeof(vsa_t);
	
	return pool;
}






	
