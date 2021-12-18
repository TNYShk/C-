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
    size_t size;
    char buffy[1];
};

static void CBuffPrint(cbuffer_t *buffer)
{
	size_t start = buffer->head;
	size_t capac = buffer->capacity;
	printf("printing buffer:\n");
	while(start != buffer->size)	
	{
		printf("%c", buffer->buffy[start]);
		start = (start + 1)%capac;
	}
	printf("\n");

}



cbuffer_t *CBuffCreate(size_t capacity)
{
	cbuffer_t *cyc_buff = NULL;

	cyc_buff = (cbuffer_t *)calloc(offsetof(cbuffer_t, buffy) + capacity + 1, sizeof(char));

	assert(NULL != cyc_buff);
	assert(0 < capacity);

	cyc_buff->capacity = capacity;
	cyc_buff->head = cyc_buff->buffy[capacity];
	cyc_buff->size = cyc_buff->buffy[0];

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

	assert(NULL != buffer);
	assert(0 < count);


	while ( (buffer->head != buffer->size + 1 ) && count )
	
	{
		
		buffer->buffy[buffer->size] = *(*(const char **)&src)++;
		buffer->size = (buffer->size + 1) % buffer->capacity; 
		--count;
		printf("tail moved to idx %ld\n", buffer->size);
	}
	
	CBuffPrint(buffer);
	return (counter - count);
}



ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{
	ssize_t counter = count;


	while ((buffer->head != buffer->size ) && count)
	{ 
		 *(*(char **)&dest)++ = buffer->buffy[buffer->head];
		buffer->head = (buffer->head + 1) % buffer->capacity; 
		--count;
		printf("head moved to idx %ld\n", buffer->head);
		
	}
	
	return (counter - count);
}	

int CBuffIsEmpty(const cbuffer_t *buffer)
{
	return (buffer->head == buffer->size ? 1 : 0);
}


size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	if( (buffer->capacity - buffer->size + buffer->head) >buffer->capacity)
	{
		return ((buffer->capacity - buffer->size + buffer->head)% buffer->capacity);
	}
	return (buffer->capacity - buffer->size + buffer->head);
}

