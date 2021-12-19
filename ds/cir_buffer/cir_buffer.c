#include <unistd.h> /* size_t ssize_t*/
#include <stdlib.h> /* memort allocation */
#include <assert.h> /* assert */
#include <stddef.h> /* offsetof*/
#include <stdio.h> /* printf for internal Print Func */

#include "cir_buffer.h"

/*********Reviewed by Erez**********
*		     Dec 19					*
*									*
*		created by Tanya			*
*		  							*
************************************/

enum options
{
	NOT = -1,
	START
};

struct cbuffer
{
    size_t capacity;
    size_t head;
    size_t tail;
    char buffy[1];
};


/*static void CBuffPrint(cbuffer_t *buffer)*/
/*use it to print in Write Func, before return, CBuffPrint(buffer)*/

cbuffer_t *CBuffCreate(size_t capacity)
{
	cbuffer_t *cyc_buff = NULL;

	cyc_buff = (cbuffer_t *)calloc(offsetof(cbuffer_t, buffy) + capacity , sizeof(char));

	if(NULL == cyc_buff)
	{
		return NULL;
	}

	assert(0 < capacity);

	cyc_buff->capacity = capacity;
	cyc_buff->head = START;
	cyc_buff->tail = START; 

	return cyc_buff;
}


void CBuffDestroy(cbuffer_t *buffer)
{
	free(buffer);
	buffer = NULL;
}

size_t CBuffCapacity(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return buffer->capacity;
}

ssize_t CBuffWrite(cbuffer_t *buffer,const void *src, size_t count)
{
	ssize_t counter = START;

	assert(NULL != buffer);
	assert(0 < count);

	
	if (START == CBuffFreeSpace(buffer))
	{
		return NOT;
	}
	
	while ((size_t)counter < count && CBuffFreeSpace(buffer) > START)
	{
		if(buffer->tail == buffer->capacity)
		{
			buffer->tail = START;
		}

		buffer->buffy[buffer->tail] = *(*(const char **)&src);
		++(*(const char **)&src);
		++buffer->tail;             
		++counter;
	}
	
	return (counter);
}


ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{
	ssize_t counter = count;

	assert(NULL != buffer);
	assert( 0 < count);
	
	if(CBuffFreeSpace(buffer) == buffer->capacity)
	{
		return NOT;
	}

	while ((buffer->head != buffer->tail) && count)
	{ 
		if(buffer->head == buffer->capacity)
		{
			buffer->head = START; 
		}
		*(*(char **)&dest) = buffer->buffy[buffer->head];
		++(*(char **)&dest);
		++buffer->head;
		--count;
	}
	
	return (counter - count);
}	

int CBuffIsEmpty(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return ((buffer->tail == buffer->head) ? 1 : 0);
}


size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	if( (buffer->capacity - buffer->tail + buffer->head) > buffer->capacity)
	{
		return ((buffer->capacity - buffer->tail + buffer->head)% buffer->capacity);
	}
	return (buffer->capacity - buffer->tail + buffer->head);
	
}



/*
static void CBuffPrint(cbuffer_t *buffer)
{
	size_t capac = buffer->capacity;
	size_t start = buffer->head;
	ssize_t size = 	buffer->tail;
	printf("printing buffer:\n");
	
	while((start != (size_t)size) && capac)	
	{
		printf("%c", buffer->buffy[start]);
		++start;
		--capac;
	}
	printf("\n");

}*/
