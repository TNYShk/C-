/**********************************************
 * Dynamic Vector- Source Code          	  *
 * Developer: Tanya                   		  *
 * 2021-12 -13                       		  *
 *                                            *
 *      reviewed by Amit               		  *
**********************************************/

#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memmove                      */
#include <assert.h>    /* assert                      */ 
                                                
#include "dynamic_vector.h"

#define GROWTHFACTOR (2)
#define ANDONE (1)


enum
{
	ERROR = -1,
	SUCCESS 
};

struct vector
{
	void *start;
	size_t capacity;
	size_t elem_size;
	size_t size;	
	
}; 


vector_t *VectorCreate(size_t element_size, size_t cap)
{
	vector_t *vector = NULL;
	
	assert(0 < cap);
	assert(0 < element_size);
	
	vector = (vector_t *)malloc(sizeof(vector_t));
	if(NULL == vector)
	{
		return NULL;
	}

	vector->start = calloc(cap, element_size);
	if (NULL == vector->start )
	{
		free (vector);
		vector = NULL;
		return NULL;
	}
	
	vector->capacity = cap;
	vector->elem_size = element_size;
	vector->size = 0;

	return vector;
}


void VectorDestroy(vector_t *vec_ptr)
{
	free(vec_ptr->start);
	vec_ptr->start = NULL;

	free(vec_ptr);
	vec_ptr = NULL;
}


void *VectorGetAccessToElement(vector_t *vec_ptr, size_t index)
{
	
	assert (NULL != vec_ptr);
	
	
	return ((char *)vec_ptr->start + (index * vec_ptr->elem_size)); 
}


int VectorPushBack(vector_t *vec_ptr, const void *element)
{
	void *start = NULL;

	assert(NULL != vec_ptr);

	if ( ANDONE >= vec_ptr->capacity - vec_ptr->size)
	{
		vec_ptr = VectorReserve(vec_ptr, GROWTHFACTOR * vec_ptr->capacity);
	}

	start = memmove(((char*)vec_ptr->start + (vec_ptr->size * vec_ptr->elem_size)), element, vec_ptr->elem_size);
	
	if (NULL == start)
	{
		return ERROR;
	}
	
	++(vec_ptr->size);
	return (vec_ptr == NULL);	
}


void VectorPopBack(vector_t *vec_ptr)
{
	assert(NULL != vec_ptr);

    if (0 == vec_ptr->size)
    {
        return;
    }

    if (--vec_ptr->size < vec_ptr->capacity >> 2)
    {
        VectorReserve(vec_ptr, vec_ptr->capacity >> 1);
    }

}

/* if vec_ptr is NULL, return value is undefined and its users problem?*/
size_t VectorSize(const vector_t *vec_ptr)
{
	return (vec_ptr->size);
	
}
/* if vec_ptr is NULL, return value is undefined and its users problem?*/
size_t VectorCapacity(const vector_t *vec_ptr)
{
	return vec_ptr->capacity;
}


vector_t *VectorReserve(vector_t *vec_ptr, size_t new_size)
{
	void *real_start = NULL;
	
	assert(NULL != vec_ptr);

	if ((vec_ptr->size) > new_size)
	{
		++new_size;
	}
		
	real_start = realloc(vec_ptr->start, (vec_ptr->elem_size * new_size));
	
	if (NULL == real_start)
	{
		return vec_ptr;
	}
	
	vec_ptr->capacity = new_size; 
	vec_ptr->start = real_start;

	return vec_ptr;
}


