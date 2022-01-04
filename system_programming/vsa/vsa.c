/**********************************************
 * Variable-Size Allocator - Source File      *
 * Developer:  Tanya                          *
 * Written:   04/01/2022                      *
 * Reviewer: __________                       *
 *                                            *
 **********************************************/
#include <stdlib.h> /* size_t  */
#include <assert.h> /* asserts */
#include <stdio.h>

#include "vsa.h" /* header file */


#define WORD_SIZE (sizeof(size_t))

#define ALIGNDOWN(a) (a - ((a + WORD_SIZE) & (WORD_SIZE - 1)))
#define ALIGNUP(a) ((a + WORD_SIZE - 1) & -(WORD_SIZE))
#define ZERO (0l)

enum status
{
	FAIL = -1,
	END,
	SUCCESS
};

struct vsa
{
	long start;
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

	mem_size -=sizeof(vsa_t);
	((vsa_t *)pool)->start = sizeof(vsa_t);
	runner = ((vsa_t*)pool)->start + (char *)pool;
	
	*(long *)runner = mem_size - sizeof(vsa_t);
	runner += mem_size;
	*(long *)runner = END;
	
	return (vsa_t *)pool;
}



/*access given block BH, verify its negative (been used) and turn to positive */
void VSAFree(void *block)
{
	if (*(long *)block < ZERO)
	{
		*(long *)block *= -1;
	}

}

/*PSEUDO
	
	run biggest chunk func (has defrag in it)
	align alloc_size
	verify that alloc_size < biggest chunk
	run from pool start until *BH = 0 (end) or BH > alloc_size
	perform allocation- save current BH value in temp var,
	update found BH to -alloc_size
	move +alloc_size and create a new BH,
	 its value is the remainder of memory left (previous temp var - alloc_size)
	 return temp var adrs
 */
void *VSAAlloc(vsa_t *pool, size_t alloc_size);



/*
PSEUDO
run from start and until BH guard, using slow & fast runners
	check for positive value in each BH
		if found check next BH, if both are positive:
		perform merge- update first BH to be old value + next BH + 8
 */
static int DefragPool(vsa_t *pool)
{
	vsa_t *fast_runner = (vsa_t *)((char *)pool + pool->start);
	vsa_t *slow_runner = ((vsa_t *)(char *)pool);
	printf("fast runner is %ld \n", *(long *)fast_runner);
	printf("slow runner is %ld \n", *(long *)slow_runner);
	while (*(long *)fast_runner != END)
	{
		
		if ((*(long *)slow_runner > ZERO) && (*(long *)fast_runner > WORD_SIZE))
		{
			slow_runner->start += fast_runner->start ;
			return SUCCESS;
		}

		fast_runner += pool->start;
		slow_runner += pool->start;
		
	}
	return END;
}


/*
PSEUDO
run defrag
create temp value, 
move through pool until block guard reached
check BH value, if *BH > temp value, replace values
return temp value
 */
size_t VSALargestFreeChunck(vsa_t *pool)
{
	size_t chunk = 0;
	(DefragPool(pool) == 1) ? (printf("defraged!\n")) : (printf("nope!\n"));
	while (ZERO != pool->start)
	{
		if(pool->start > (long)chunk )
		{
			chunk = pool->start;
		}
		  pool = (vsa_t *)((char *)pool + pool->start);
	}
	  
	return chunk;
}