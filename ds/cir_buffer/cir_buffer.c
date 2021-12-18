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

static void CBuffPrint(cbuffer_t *buffer)
{
	size_t capac = buffer->capacity;
	size_t start = buffer->head;
	printf("printing buffer:\n");
	while(start != buffer->tail)	
	{
		printf("%c", buffer->buffy[start]);
		start = (start + 1)%capac;
		
	}
	printf("\n");

}
static int CBuffFull(cbuffer_t *buffer)
{
	return (buffer->head == buffer->tail);
}



cbuffer_t *CBuffCreate(size_t capacity)
{
	cbuffer_t *cyc_buff = NULL;

	cyc_buff = (cbuffer_t *)calloc(offsetof(cbuffer_t, buffy) + capacity , sizeof(char));

	assert(NULL != cyc_buff);
	assert(0 < capacity);

	cyc_buff->capacity = capacity;
	cyc_buff->head = capacity;
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
	size_t cap = buffer->capacity;

	assert(NULL != buffer);
	assert(0 < count);

	
	if ((buffer->head == buffer->tail) && (buffer->head == 0))
	{
		return -1;
	}
	
	while (cap && (buffer->head != buffer->tail+1) && count )
	
	{
		buffer->buffy[buffer->tail] = *(*(const char **)&src);
		++(*(const char **)&src);
		buffer->tail = (buffer->tail + 1) % buffer->capacity;             
		--count;
		--cap;
		
	}
	printf("tail post while in idx %ld\n", buffer->tail);

	if(CBuffFull(buffer))
	{
		buffer->head = (buffer->head) % buffer->capacity; 
	}

	if (buffer->head == buffer->tail+1)
	{
		buffer->buffy[buffer->head] = *(*(const char **)&src);
		--count;
	}
	printf("head is now in idx %ld\n", buffer->head);
	/*CBuffPrint(buffer);*/
	return (counter - count);
}


ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{
	ssize_t counter = count;
	
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
		 *(*(char **)&dest)++ = buffer->buffy[buffer->head];
		buffer->head = (buffer->head + 1) % buffer->capacity; 
		--count;
		
		
	}
	printf("tail post while in idx %ld\n", buffer->tail);
	printf("head is in idx %ld\n", buffer->head);
	
	
	return (counter - count);
}	

int CBuffIsEmpty(const cbuffer_t *buffer)
{
	return ((buffer->head + buffer->tail- buffer->capacity == 0) ? 1 : 0);
}


size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	if (buffer->head - buffer->tail == 1)
	{
		return 0;
	}
	if( (buffer->capacity - buffer->tail + buffer->head) >buffer->capacity)
	{
		return ((buffer->capacity - buffer->tail + buffer->head)% buffer->capacity);
	}
	return (buffer->capacity - buffer->tail + buffer->head);
}

