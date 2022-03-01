/***********************************
 * Circular Buffer Source Code     *
 * Developer: Ephraim Feldblum     *
 * Written: 2021-12-16             *
 *                                 *
 * Reviewer: Oren Goldstein        *
 ***********************************/

#include <unistd.h> /* size_t, ssize_t */
#include <stdlib.h> /* malloc(), free(), NULL */
#include <stddef.h> /* offsetof() */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy() */

#include "cir_buffer.h"

enum error_codes
{
    READ_WRITE_ERROR = -1,
    EMPTY_BUFFER = 0
};

struct cbuffer
{
    size_t cap;
    char *front;
    char *rear;
    char buf[1];
};

static int CBuffIsFull(const cbuffer_t *buffer);
static size_t CBuffFilledSpace(const cbuffer_t *buffer);
static size_t CBufBytesToCap(const cbuffer_t *buffer, const char *ptr);
static char *CBuffCyclePtr(cbuffer_t *buffer, char *ptr);
static size_t SizeTMin(size_t first, size_t second);


/******************** Constructor ********************/
cbuffer_t *CBuffCreate(size_t capacity)
{
    cbuffer_t *buffer = NULL;

    assert(EMPTY_BUFFER != capacity);

    buffer = (cbuffer_t *)malloc(offsetof(cbuffer_t, buf) + capacity);
    if (NULL == buffer)
    {
        return NULL;
    }

    buffer->cap = capacity;
    buffer->front = NULL;
    buffer->rear = buffer->buf;

    return buffer;
}

/******************** Destructor ********************/
void CBuffDestroy(cbuffer_t *buffer)
{
    assert(NULL != buffer);

    free(buffer);
    buffer = NULL;
}

/******************** Read / Write ********************/
ssize_t CBuffWrite(cbuffer_t *buffer, const void *src, size_t count)
{
    size_t num_write = 0;

    assert(NULL != buffer);
    assert(NULL != src);
    assert(EMPTY_BUFFER != count);
    if (CBuffIsFull(buffer))
    {
        return READ_WRITE_ERROR;
    }

    count = SizeTMin(count, CBuffFreeSpace(buffer));
    num_write = SizeTMin(count, CBufBytesToCap(buffer, buffer->rear));
    if (CBuffIsEmpty(buffer))
    {
        buffer->front = buffer->rear;
    }

    memcpy(buffer->rear, src, num_write);
    buffer->rear += num_write;
    *(const char **)&src += num_write;
    buffer->rear = CBuffCyclePtr(buffer, buffer->rear);
    num_write = count - num_write;
    memcpy(buffer->rear, src, num_write);
    buffer->rear += num_write;

    return (count);
}

ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count)
{
    size_t num_read = 0;

    assert(NULL != buffer);
    assert(NULL != dest);
    assert(EMPTY_BUFFER != count);
    if (CBuffIsEmpty(buffer))
    {
        return READ_WRITE_ERROR;
    }

    count = SizeTMin(count, CBuffFilledSpace(buffer));
    num_read = SizeTMin(count, CBufBytesToCap(buffer, buffer->front));

    memcpy(dest, buffer->front, num_read);
    buffer->front += num_read;
    *(char **)&dest += num_read;
    num_read = count - num_read;
    buffer->front = CBuffCyclePtr(buffer, buffer->front);
    memcpy(dest, buffer->front, num_read);
    buffer->front += num_read;

    if (CBuffIsFull(buffer))
    {
        buffer->front = NULL;
    }

    return (count);
}

/******************** Administrative ********************/
size_t CBuffCapacity(const cbuffer_t *buffer)
{
    assert(NULL != buffer);

    return buffer->cap;
}

int CBuffIsEmpty(const cbuffer_t *buffer)
{
    assert(NULL != buffer);

    return (NULL == buffer->front);
}

size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
    assert(NULL != buffer);

    return (
            buffer->cap * (buffer->rear > buffer->front) +
            (buffer->front - buffer->rear) * !CBuffIsEmpty(buffer)
           );
}

static int CBuffIsFull(const cbuffer_t *buffer)
{
    assert(NULL != buffer);

    return (buffer->front == buffer->rear);
}

static size_t CBuffFilledSpace(const cbuffer_t *buffer)
{
    assert(NULL != buffer);

    return CBuffCapacity(buffer) - CBuffFreeSpace(buffer);
}

static size_t CBufBytesToCap(const cbuffer_t *buffer, const char *ptr)
{
    assert(NULL != buffer);

    return buffer->buf + buffer->cap - ptr;
}

static char *CBuffCyclePtr(cbuffer_t *buffer, char *ptr)
{
    assert(NULL != buffer);

    return (ptr == buffer->buf + buffer->cap) ? buffer->buf : ptr;
}

static size_t SizeTMin(size_t first, size_t second)
{
    return (first < second ? first : second);
}
