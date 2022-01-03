/**********************************************
 * Variable-Size Allocator - Header File      *
 * Developer:                                 *
 * Written:   03/01/2022                      *
 * Reviewer: __________                       *
 *                                            *
 **********************************************/
#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

/**********************************************
* In C File:
* static void VSADeFrag(vsa_t *pool) 
* header struct for blocks - contains long offset to end of block (+ anything else needed?)
 **********************************************/
typedef struct vsa vsa_t;

/* 
 * DESCRIPTION:
 * Initialize VSA based on users request
 * 
 * PARAMETERS:
 * void *pool - pointer to the allocated memory
 * mem_size - total mempry allocated
 * 
 * RETURN:
 * pointer to the created VSA
 * 
 * Complexity: Time O(1), Space O(1).
 **/
vsa_t *VSAInit(void *pool, size_t mem_size);

/**
 * Complexity: Time O(n), Space O(1). 
 * Algorithm- first fit + aligned to word size.
 * Implementation should represent malloc().
 */
void *VSAAlloc(vsa_t *pool, size_t alloc_size);

/**
 * Complexity: Time O(1), Space O(1). 
 * if given block not allocated: 
 * production- undefined behavior ; debug- assert that block was allocated.
 * Functionality - as stdlib free().
 * Allowed to free NULL - does nothing.
 */
void VSAFree(void *block);

/**
 *  Complexity: Time O(n), Space O(1).
 *  + Merges free blocks.
 */
size_t VSALargestFreeChunck(vsa_t *pool);

#endif /* __VSA_H__ */
