#ifndef __CIR_BUFFER_H__
#define __CIR_BUFFER_H__

#include <unistd.h> /* size_t ssize_t*/



typedef struct cbuffer cbuffer_t;

/* Time complexity O(1), Space complexity O(n) 
Create a Cyclic Buffer based in desired Capacity
Return ptr to the Struct, NULL if failed*/
cbuffer_t *CBuffCreate(size_t capacity);

/* Time complexity O(1), Space complexity O(1) 
Destroys the Structs, frees allocated memory*/
void CBuffDestroy(cbuffer_t *buffer);

/* Time complexity O(1), Space complexity O(1) 
Returns capacity of the buffer*/
size_t CBuffCapacity(const cbuffer_t *buffer);

/* Time complexity O(n), Space complexity O(1) 
Write byte-count into the buffer, from a given source
Returns bytes written, -1 if nothing was written*/
ssize_t CBuffWrite(cbuffer_t *buffer,const void *src, size_t count);

/* Time complexity O(n), Space complexity O(1) 
Read bytes (count) from the buffer, into given destination
Returns bytes read, -1 if there's nothing to read*/
ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count);

/* Time complexity O(1), Space complexity O(1) 
Checks if the Buffer is Empty
Returns 1 if empty*/
int CBuffIsEmpty(const cbuffer_t *buffer);

/* Time complexity O(1), Space complexity O(1) 
checks how much bytes can be written into buffer*/
size_t CBuffFreeSpace(const cbuffer_t *buffer);

#endif /* __CIR_BUFFER__ */
