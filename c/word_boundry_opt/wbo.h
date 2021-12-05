#ifndef __WBO_H__
#define __WBO_H__

#define WORD_SIZE (sizeof(size_t))
#include <stddef.h>


/* 
copies c n times into memory area pointed by s.

Receive:
 pointer,c integer, n bytes

Fill the pointer s with c for n bytes


Return:
pointer to s 

*/
void *MemSet(void *s, int c, size_t n);



/* 
Receive pointer to src, pointer to dest, n bytes size 
safe to use in case of overlap?
copies memory area pointed to by src n times into memory area pointed by dest.
Return:
pointer to dest 
*/
void *MemCpy(void *dest, const void *src, size_t n);



/* Receive pointer to src, pointer to dest, n bytes size 
Move the src memory locations into dest
Return pointer to dest */
void *MemMove(void *dest, const void *src, size_t n);

#endif /* __WBO_H__ */
