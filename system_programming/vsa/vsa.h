/**********************************************
 * Variable-Size Allocator - Header File      *
 * Developer:  Tanya                          *
 * Written:   05/01/2022                      *
 * Reviewer: Nurit                            *
 *                                            *
 **********************************************/
#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */


typedef struct vsa vsa_t;

/* 
 * DESCRIPTION:
 * Initialize VSA based on users request, 
 * given memory size must be atlseat 64 bytes
 * 
 * PARAMETERS:
 * void *pool - pointer to the allocated memory
 * mem_size - total memory to be managed
 * 
 * RETURN:
 * pointer to the created VSA
 * 
 * Complexity: Time O(1), Space O(1).
 **/
vsa_t *VSAInit(void *pool, size_t mem_size);

/**
 * DESCRIPTION: 
 * Allocated block of memory based
 * Memory block shall be ALIGNED to word size, algorithm is First Fit.
 * [Implementation should represent malloc(), meaning overhead]
 * 
 * 
 * to minimize NULL returns, FreeChunk function should be ran periodically
 *
 * PARAMETERS:
 * vsa pointer to the pool
 * alloc_size - desired block size, must be bigger than ZERO. otherwise undefined behavior
 *
 * RETURN:
 * pointer to the allocated memory. 
 * If space is insufficient, NULL is returned.
 * Complexity: Time O(n), Space O(1). 
 **/
void *VSAAlloc(vsa_t *pool, size_t alloc_size);

/**
 * DESCRIPTION:
 * returns used block back to memory pool
 * if given block not allocated: 
 * production- undefined behavior ; debug- assert that block was allocated.
 * [Functionality - as stdlib free().]
 * Allowed to free NULL - does nothing.
 
 * PARAMETERS:
 * pointer to the used block to free.
 *
 * RETURN:
 * None
 * Complexity: Time O(1), Space O(1). 
 **/
void VSAFree(void *block);

/** 
 * DESCRIPTION:
 * Checks for current largest available chunk of memory
 * Merges sequential free blocks
 *
 * PARAMETERS:
 * pointer to the VSA to scan.
 *
 * RETURN:
 * size_t of the largest chunk available for allocation, in bytes.
 *
 * Complexity: Time O(n), Space O(1). 
 **/
size_t VSALargestFreeChunck(vsa_t *pool);

#endif /* __VSA_H__ */
