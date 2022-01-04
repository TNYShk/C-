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

#include "vsa.h" /* header file */


#define WORD_SIZE (sizeof(size_t))
#define LONG_SIZE ((long)sizeof(long))

#define ALIGNDOWN(a) (a - ((a + WORD_SIZE) & (WORD_SIZE - 1)))
#define ALIGNUP(a) ((a + WORD_SIZE - 1) & -(WORD_SIZE))
#define ZERO (0l)
#define MAGIC (0x666AAA666AAA6666l)

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
	assert (mem_size > WORD_SIZE * WORD_SIZE);

	mem_size -=sizeof(vsa_t);
	
	((vsa_t*)pool)->start = mem_size - sizeof(vsa_t);

	runner = ((vsa_t*)pool)->start + (char *)pool;
	
	*(long *)runner = END;

	return (vsa_t *)pool;
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

/*PSEUDO
	
	
	align alloc_size
	run biggest chunk func (has defrag in it)
	verify that alloc_size < biggest chunk
	run from pool start until *BH = 0 (end) or BH > alloc_size
	perform allocation- save current BH value in temp var,
	update found BH to -alloc_size
	move +alloc_size and create a new BH,
	 
	 return temp var adrs
 */
void *VSAAlloc(vsa_t *pool, size_t alloc_size)
{
	vsa_t *allocated = ((vsa_t *)(char *)pool);
	
	assert(NULL != pool);
	assert(ZERO < alloc_size);

	alloc_size = ALIGNUP(alloc_size);
	
	if (alloc_size < VSALargestFreeChunck(pool))
	{
		while( (END != ((vsa_t *)allocated)->start ) && ( ((vsa_t *)allocated)->start < (long)alloc_size) )
		{
			*((char **)&allocated) += labs(((vsa_t *)allocated)->start);
		}
		
		

	*(long *)(((char **)&allocated) + sizeof(vsa_t)) -=  alloc_size;

		*(long *)allocated = -1 * (long)alloc_size;
					printf("VSAAlloc: allocated %ld \n", *(long*)allocated);						
		
						printf("VSAAlloc: allocated->start is %ld \n", allocated->start);	
	}
	
	return allocated;	
}



	/*
	if(VSALargestFreeChunck(pool) > alloc_size)
	{
		printf("VSAAlloc: before slow runner is %ld \n", *(long *)slow_runner);
			printf("VSAAlloc: before, pool->start is %ld \n", pool->start);
		while ( (ZERO != pool->start) && ( (*(long *)slow_runner) < (long)alloc_size ) )
		{
			long temp = labs(*(long *)slow_runner);
			slow_runner += temp;
			pool = (vsa_t *)((char *)pool + temp);
			printf("temp is %ld\n", temp);
		}
		pool->start -= alloc_size; 
		printf("VSAAlloc: pool->start is %ld \n", pool->start);
		*(long *)slow_runner = -alloc_size;
		printf("VSAAlloc:  slow runner is %ld \n", *(long *)slow_runner);
	}
		printf("VSAAlloc: post pool->start is %ld \n", pool->start);
		printf("VSAAlloc: post slow runner is %ld \n", *(long *)slow_runner);
	return slow_runner;
	*/

	




/*
PSEUDO
 using slow & fast runners check for positive value in each BH
		perform merge- update first BH to be old value + next BH
 */





static int DefragPool(vsa_t *pool)
{
	vsa_t *fast_runner = (vsa_t *)((char *)pool + pool->start);

	printf("defrag before while: fast runner is %ld \n", *(long *)fast_runner);

		if (fast_runner->start > ZERO)
		{
			pool->start += fast_runner->start;

			return SUCCESS;
		}

	return END;
}


/*
PSEUDO
run on pool until end
if current BH is positive- send to defrag
then check wether pool is bigger then chunk, if yes, replace values

return temp value
 */
size_t VSALargestFreeChunck(vsa_t *pool)
{
	size_t chunk = ZERO;
	printf("CHUNK: pool is %ld \n", *(long *)pool);
	printf("CHUNK: pool->start is %ld \n", pool->start);
	while (END != pool->start)
	{
		if(ZERO < pool->start)
		{
			DefragPool(pool);	
	
			if(pool->start >= (long)chunk )
			{
				chunk = pool->start;
			}	
		}

		*((char **)&pool) += labs(pool->start);				
	}

	return chunk;
}
	  
	






	
