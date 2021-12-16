#ifndef __CIR_BUFFER_H__
#define __CIR_BUFFER_H__

#include <unistd.h> /* size_t ssize_t*/

/*
struct cbuffer
{
    size_t capacity;
    char *front;
    char *rear;
    char buffer[1];
};

struct cbuffer
{
    size_t capacity;
    size_t front;
    size_t rear;
    char buffer[1];
};

struct cbuffer
{
    size_t capacity;
    size_t front;
    size_t size;
    char buffer[1];
};
*/

typedef struct cbuffer cbuffer_t;

/* Time complexity O(1), Space complexity O(n) */
cbuffer_t *CBuffCreate(size_t capacity);

/* Time complexity O(1), Space complexity O(1) */
void CBuffDestroy(cbuffer_t *buffer);

/* Time complexity O(1), Space complexity O(1) */
size_t CBuffCapacity(const cbuffer_t *buffer);

/* Time complexity O(n), Space complexity O(1) */
ssize_t CBuffWrite(cbuffer_t *buffer,const void *src, size_t count);

/* Time complexity O(n), Space complexity O(1) */
ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count);

/* Time complexity O(1), Space complexity O(1) */
int CBuffIsEmpty(const cbuffer_t *buffer);

/* Time complexity O(1), Space complexity O(1) */
size_t CBuffFreeSpace(const cbuffer_t *buffer);

#endif /* __CIR_BUFFER__ */
