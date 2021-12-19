#include <unistd.h> /* size_t ssize_t*/
#include <stdlib.h> /* memort allocation */
#include <assert.h> /* assert */
#include <stddef.h> /* offsetof*/

#include <stdio.h> /* printf */


#include "cir_buffer.h"



struct cbuffer
{
    size_t capacity;
    size_t head;
    size_t tail;
    char buffy[1];
};

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

}
*/

cbuffer_t *CBuffCreate(size_t capacity)
{
	cbuffer_t *cyc_buff = NULL;

	cyc_buff = (cbuffer_t *)calloc(offsetof(cbuffer_t, buffy) + capacity , sizeof(char));

	assert(NULL != cyc_buff);
	assert(0 < capacity);

	cyc_buff->capacity = capacity;
	cyc_buff->head = 0;
	cyc_buff->tail = 0; 

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
	ssize_t counter = count;
	ssize_t size = 0;

	assert(NULL != buffer);
	assert(0 < count);

	
	if (0 == CBuffFreeSpace(buffer))
	{
		return -1;
	}
	
	while ((size_t)size < count && CBuffFreeSpace(buffer) > 0)
	{
		if((size_t)size >= buffer->capacity)
		{
			buffer->tail = 0;
		}

		buffer->buffy[buffer->tail] = *(*(const char **)&src);
		++(*(const char **)&src);
		buffer->tail = (buffer->tail + 1);             
		--counter;
		++size;
		
	}
	
	/*CBuffPrint(buffer);*/
	return (size);
}


ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{
	ssize_t counter = count;
	
	assert(NULL != buffer);
	assert( 0 < count);
	
	if(CBuffFreeSpace(buffer) == buffer->capacity)
	{
		return -1;
	}
	if(buffer->head == buffer->capacity)
	{
		buffer->head = buffer->head % buffer->capacity; 
	}

	while ((buffer->head != buffer->tail) && count)
	{ 
		*(*(char **)&dest) = buffer->buffy[buffer->head];
		++(*(char **)&dest);
		buffer->head = (buffer->head + 1) % buffer->capacity; 
		--count;
	}
	
	return (counter - count);
}	

int CBuffIsEmpty(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return ((buffer->tail == 0) ? 1 : 0);
}


size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return (buffer->capacity - buffer->tail + buffer->head);
}

