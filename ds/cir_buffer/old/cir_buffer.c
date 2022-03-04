
#include <unistd.h> /* size_t ssize_t*/
#include <stdlib.h> /* memort allocation */
#include <assert.h> /* assert */
#include <stddef.h> /* offsetof*/
#include <stdio.h> /* printf for internal Print Func */
#include <string.h> /* memset*/

#include "cir_buffer.h"
#define WORD_SIZE (sizeof(size_t))
#define MIN(a,b)  (((size_t)a > (size_t)b) ? ((size_t)b) : ((size_t)a))
#define R_W_ERROR (-1)

struct cbuffer
{
    size_t capacity;
    char *front;
    char *back;
    char buffy[1];
};



static void AlignCBuff(cbuffer_t *buffer);
static char *CBuffFullCycle(cbuffer_t *buffer, char *location);
static size_t CBuffTakenSpace(const cbuffer_t *buffer);
static int ISCBuffFull(const cbuffer_t *buffer);


cbuffer_t *CBuffCreate(size_t capacity)
{
	cbuffer_t *cyc_buff = NULL;
	
	assert(0 < capacity);

	cyc_buff = (cbuffer_t *)calloc(offsetof(cbuffer_t, buffy) + capacity , sizeof(char));
	if(NULL == cyc_buff)
	{
		return NULL;
	}

	cyc_buff->capacity = capacity;
	cyc_buff->front = NULL;
	cyc_buff->back = cyc_buff->buffy; 

	return cyc_buff;

}

void CBuffDestroy(cbuffer_t *buffer)
{
	memset(buffer, 0, sizeof(offsetof(cbuffer_t, buffy)));
	free(buffer);

	buffer = NULL;
}


size_t CBuffCapacity(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return buffer->capacity;
}

int CBuffIsEmpty(const cbuffer_t *buffer)
{
    assert(NULL != buffer);


    return (NULL == buffer->front);
}


ssize_t CBuffWrite(cbuffer_t *buffer,const void *src, size_t count)
{
	size_t available_space = CBuffFreeSpace(buffer);
	size_t written = 0;
	char *copy = NULL;

	assert(NULL != buffer);
	assert(NULL != src);
	assert(0 < count );
	if(ISCBuffFull(buffer))
	{
		return R_W_ERROR;
	}
	copy = *(char **)&src;

	count = MIN(available_space, count);
	written = MIN(count, (buffer->buffy + buffer->capacity - buffer->back));
	
	AlignCBuff(buffer);

	memcpy(buffer->back, src, written);
	buffer->back += written;
	copy += written;

	buffer->back = CBuffFullCycle(buffer, buffer->back);
	available_space = count - written;
	memcpy(buffer->back, copy, available_space);
	buffer->back += available_space;

	return count;
}

ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{
	size_t taken_space = CBuffTakenSpace(buffer);
	size_t written = 0;
	
	assert(NULL != buffer);
	assert(NULL != dest);
	assert(0 < count );
	
	if(CBuffIsEmpty(buffer))
	{
		return R_W_ERROR;
	}
	
	count = MIN(taken_space, count);
	written = MIN(count, (buffer->buffy + buffer->capacity - buffer->front));
	
	memcpy(dest, buffer->front, written);
	buffer->front += written;
	*(char **)&dest += written;

	buffer->front = CBuffFullCycle(buffer, buffer->front);
	taken_space = count - written;
	memcpy(dest, buffer->front, taken_space);
	buffer->front += taken_space;
	AlignCBuff(buffer);

	return count;
}



static void AlignCBuff(cbuffer_t *buffer)
{
    assert(NULL != buffer);
    if(CBuffIsEmpty(buffer))
    {
    	buffer->front = buffer->back;
    	
    }
    else if(buffer->front == buffer->back)
    {
    	buffer->front = NULL;	
    }
}

static char *CBuffFullCycle(cbuffer_t *buffer, char *location)
{
    assert(NULL != buffer);

    if(location == buffer->buffy + buffer->capacity)
    {
    	return buffer->buffy;
    }
    return location;

    
}


static size_t CBuffTakenSpace(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return(CBuffCapacity(buffer) - CBuffFreeSpace(buffer));
}




static int ISCBuffFull(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	return (buffer->front == buffer->back);
}



size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	assert(NULL != buffer);

	if(CBuffIsEmpty(buffer))
	{
		return buffer->capacity;
	}

	return (buffer->capacity * (buffer->back > buffer->front) + (buffer->front - buffer->back));
}