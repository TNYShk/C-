#ifndef __WBO_H__
#define __WBO_H__

#include <stddef.h>
/* Receive pointer, integar, n bytes
Fill the pointer s with c for n bytes
Return pointer to s */
void *MemSet(void *s, int c, size_t n);

/* Receive pointer to src, pointer to dest, n bytes size 
Copy the src memory locations into dest
Return pointer to dest */
void *MemCpy(void *dest, const void *src, size_t n);

/* Receive pointer to src, pointer to dest, n bytes size 
Move the src memory locations into dest
Return pointer to dest */
void *MemMove(void *dest, const void *src, size_t n);

#endif /* __WBO_H__ */
