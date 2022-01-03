#ifndef __FSA_H__
#define __FSA_H__

#include <unistd.h>
#include <sys/mman.h> 

typedef struct fsa fsa_t;


/* 
 * DESCRIPTION:
 * based on user's desired param, suggest the min amount of bytes needed for the memory pool? FSA?
 * 
 * PARAMETERS:
 * num_of_block (size_t)
 * block_size in bytes
 * 
 * RETURN:
 * the total number of bytes that need to be allocated by user.
 * 
 * Complexity: time: O(1), space: O(1)*/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size); 

/* 
 * DESCRIPTION:
 * Initialize the FSA that manages the memory pool
 * 
 * PARAMETERS:
 * memory - pointer to the memory area to be managed 
 * mem_size - bytes size of the memory pool
 * block_size in bytes
 * 
 * RETURN:
 * pointer to the initialized FSA
 * 
 * Complexity: time: O(n), space: O(1)*/
fsa_t *FSAInit(void *memory, size_t mem_size, size_t block_size); 

/* 
 * DESCRIPTION:
 * allocates a single block of memory from the pool to the user
 * 
 * PARAMETERS:
 * pool - pointer to the FSA
 * 
 * 
 * RETURN:
 * pointer to the allocated block
 * Complexity: time: O(1), space: O(1)*/
void *FSAAlloc(fsa_t *pool); 

/* 
 * DESCRIPTION:
 * returns the used (by user) block back to the memory pool
 * 
 * PARAMETERS:
 * pool - pointer to the FSA
 * block - pointer to the used block of memory
 * 
 * 
 * RETURN: 
 * None
 * Complexity: time: O(1), space: O(1)*/
void FSAFree(fsa_t *pool, void *block); 

/* 
 * DESCRIPTION:
 * counts number of available blocks in the memory pool
 * 
 * PARAMETERS:
 * pool - pointer to the FSA
 * 
 * 
 * RETURN: 
 * amount of blocks that can be allocated to user
 * Complexity:time: O(n), space: O(1)*/
size_t FSACountFree(const fsa_t *pool); 

#endif /* __FSA_H__ */
