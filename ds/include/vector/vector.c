#include <stdlib.h> /* size_t */
#include <stdio.h> /*         */
#include <string.h>
#include <assert.h>
#include "dynamic_vector.h"

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

	assert ((NULL != vicky) && (NULL != vicky->start));

	vicky->capacity = cap;
	vicky->elem_size = element_size;
	vicky->size = (size_t)0;

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
	return ((char*)vptr->start + (vptr->elem_size * (index-1))); 
}

int VectorPushBack(vector_t *vptr, const void *element)
{
	if ( vptr->capacity - vptr->size == 1)
	{
		vptr = VectorReserve(vptr, 2 * vptr->capacity);
	}

	memmove(((char*)vptr->start + (vptr->size * vptr->elem_size)), element, vptr->elem_size);
	++(vptr->size);
	return (vptr == NULL);
	
}


void VectorPopBack(vector_t *vptr)
{
	assert (vptr->size > 0);
	if (vptr->capacity - vptr->size == vptr->size)
	vptr = VectorReserve(vptr, vptr->size + 1);
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
	void **start = realloc(vptr->start, sizeof(size_t *) * new_size);
		vptr->capacity = new_size; 
		vptr->start = start;

		return vptr;
}



/*
vector_t *VectorReserve(vector_t *vptr, size_t new_size)
{
	if(vptr->capacity < (vptr->size + new_size) )
	{
		vector_t *victoria = VectorCreate(vptr->elem_size, vptr->size + new_size);
		memmove(victoria, vptr, new_size);
		printf("victoria is reserved?elem size %ld\n", victoria->capacity);
		VectorDestroy(vptr);
		return victoria;
	}
	return vptr;
	
}
*/