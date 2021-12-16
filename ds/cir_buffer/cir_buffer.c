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


cbuffer_t *CBuffCreate(size_t capacity)
{
	cbuffer_t *cyc_buff = NULL;

	cyc_buff = (cbuffer_t *)malloc(offsetof(cbuffer_t, buffy) + capacity);

	assert(NULL != cyc_buff);
	assert(0 < capacity);

	cyc_buff->capacity = capacity;
	cyc_buff->head = 0;
	cyc_buff->size = 0;

	printf("offset of buffer in struct = %ld\n", offsetof(struct cbuffer, buffy));

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
	ssize_t ans = -1;
	

	assert(NULL != buffer);
	assert(0 < count);

	while ((CBuffFreeSpace(buffer) > 0) && count)
	
	{
		buffer->buffy[buffer->size] = *(*(const char **)&src)++ ;
		
		++buffer->size;
		++ans;
		--count;
	}
	
	return (ans+1);
}
/*
ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count);
*/
int CBuffIsEmpty(const cbuffer_t *buffer)
{
	return ((buffer->capacity - buffer->size == CBuffCapacity(buffer))? 1 : 0);
}


size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	return (buffer->capacity - buffer->size);
}