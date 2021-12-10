#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memmove                      */
#include <assert.h>    /* assert                      */ 
                                                 /* reviewed by Amit*/
#include "dynamic_vector.h"

#define DOUBLEDWON (2)
#define ANDONE (1)


struct vector
{
	size_t capacity;
	size_t elem_size;
	size_t size;	
	void *start;
}; 


vector_t *VectorCreate(size_t element_size, size_t cap)
{
	vector_t *vicky = NULL;
	vicky = (vector_t *)malloc(sizeof(vector_t));
	vicky->start = calloc(cap, element_size);

	assert (NULL != vicky);
	assert(NULL != vicky->start);

	vicky->capacity = cap;
	vicky->elem_size = element_size;
	vicky->size = 0;

	return vicky;
}


void VectorDestroy(vector_t *vptr)
{
	free(vptr->start);
	vptr->start = NULL;
	free(vptr);
	vptr = NULL;
}


void *VectorGetAccessToElement(vector_t *vptr, size_t index)
{
	return ((char*)vptr->start + (vptr->elem_size * (index - ANDONE))); 
}


int VectorPushBack(vector_t *vptr, const void *element)
{
	if ( ANDONE >= vptr->capacity - vptr->size)
	{
		vptr = VectorReserve(vptr, DOUBLEDWON * vptr->capacity);
	}

	memmove(((char*)vptr->start + (vptr->size * vptr->elem_size)), element, vptr->elem_size);
	++(vptr->size);
	return (vptr == NULL);	
}


void VectorPopBack(vector_t *vptr)
{
	assert (vptr->size > 0);

	if (vptr->capacity - vptr->size >= vptr->size)
		vptr = VectorReserve(vptr, vptr->size + ANDONE);
	--(vptr->size);
}

size_t VectorSize(const vector_t *vptr)
{
	assert(NULL != vptr);
	return (vptr->size);
}

size_t VectorCapacity(const vector_t *vptr)
{
	assert(NULL != vptr);
	return vptr->capacity;
}


vector_t *VectorReserve(vector_t *vptr, size_t new_size)
{
	void **start = NULL;
	if ((vptr->size) > new_size)
	{
		++new_size;
	}
		start = realloc(vptr->start, sizeof(size_t *) * new_size);
		vptr->capacity = new_size; 
		vptr->start = start;

		return vptr;
}


