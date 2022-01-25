#include <stdlib.h> /* size_t, dyncamic memory allocation  */
#include <assert.h> /* asserts */
#include <string.h> /* memcpy*/

#include "../include/stack.h"


struct stack
{
	void *top;
	size_t capacity; 
	size_t elem_size;
	void *base;
}; 


stack_t *StackCreate(size_t num_of_elements, size_t element_size)
{
	stack_t *sptr = NULL;
	
	sptr = (stack_t *)malloc(sizeof(stack_t));
	sptr->base = malloc(num_of_elements * element_size);

	if ((NULL != sptr) && (NULL != sptr->base))
	{ 

		sptr->capacity = num_of_elements;
		sptr->elem_size = element_size;
	
		sptr->top = sptr->base;
	}

	return sptr;


}

void StackPush(stack_t *sptr, const void *element)
{
	assert(NULL != sptr);

	memcpy(sptr->top, element, (sptr->elem_size));
	sptr->top = ((char *)sptr->top + sptr->elem_size);
}


int StackIsEmpty(const stack_t *sptr)
{
	assert(NULL != sptr);
	return (sptr->top == sptr->base);
}

void StackDestroy(stack_t *sptr)
{
	free(sptr->base);
	sptr->base = NULL;
	
	free(sptr);
	sptr = NULL;
}

size_t StackSize(const stack_t *sptr)
{
	assert(NULL != sptr);

	return(((size_t)sptr->top - (size_t)sptr->base)/sptr->elem_size);
}

void *StackPeek(const stack_t *sptr)
{
	assert(NULL != sptr);

	return ((char *)sptr->top - sptr->elem_size);
}

void StackPop(stack_t *sptr)
{
	assert(NULL != sptr);

	sptr->top = ((char *)sptr->top - sptr->elem_size);
}

size_t StackCapacity(const stack_t *sptr)
{
	assert(NULL != sptr);

	return (sptr->capacity);
}









	


