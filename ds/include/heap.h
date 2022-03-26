#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;
typedef int (*heap_cmp_func_t)(const void *data1, const void *data2);
typedef int (*heap_is_match_func_t)(const void *element, const void *param);


 /*
 * DESCRIPTION: 
 * Create Heap using provided comp_func
 * 
 * PARAMS:
 * array to sort
 * size_t num of elements
 * 
 * 
 * RETURN: Zero for SUCCESS
 * complexity: O(1) Space: O(1)*/
heap_t *HeapCreate(heap_cmp_func_t cmp_fun); 

 /*
 * DESCRIPTION: 
 * Destroy Heap 
 * 
 * PARAMS:
 * heap to destroy
 * 
 * 
 * RETURN: None
 * complexity: O(1) Space: O(1)*/
void HeapDestroy(heap_t *heap);

 /*
 * DESCRIPTION: 
 * Push new element into Heap, always inserts to the lowest & right-most node. then bubble node up accordingly
 * 
 * PARAMS:
 * heap to destroy
 * 
 * 
 * RETURN: int status, 0 SUCCESS
/* complexity: O(log n) Space: O(1)*/
int HeapPush(heap_t *heap, void *data);

/*
 * DESCRIPTION: 
 * remove the top (root) value of the heap. Swap, remove and heapify
 * 
 * PARAMS:
 * ptr to the heap
 * 
 * 
 * RETURN: None
/* complexity: O(log n) Space: O(1)*/
void HeapPop(heap_t *heap);

/*
 * DESCRIPTION: 
 * returns the top (root) element of the heap. 
 * 
 * PARAMS:
 * ptr to the heap
 * 
 * 
 * RETURN: void *data of the peeked root
/* complexity: O(1) Space: O(1)*/
void *HeapPeek(const heap_t *heap);

/*
 * DESCRIPTION: 
 * Counts number of elements in the heap
 * 
 * PARAMS:
 * ptr to the heap
 * 
 * 
 * RETURN: total amount of elements in the given heap
/* complexity: O(1) Space: O(1)*/
size_t HeapSize(const heap_t *heap);

/*
 * DESCRIPTION: 
 * Checks wether the heap is empty
 * 
 * PARAMS:
 * ptr to the heap
 * 
 * 
 * RETURN: Boolean. 1 for Empty, otherwise 0;
/* complexity: O(1) Space: O(1)*/
int HeapIsEmpty(const heap_t *heap);

/*
 * DESCRIPTION: 
 * removes an element from the heap, assuming its found in it by the provided match function
 * 
 * PARAMS:
 * ptr to the heap
 * match_func - to search elements in the heap
 * param - to be evaluated against while traversing the heap vua the match function
 * 
 * 
 * RETURN: Boolean. 1 for Empty, otherwise 0;
/* complexity: find O(n) remove O(log n) Space: O(1)*/
void *HeapRemove(heap_t *heap, heap_is_match_func_t match_func, void *param);

#endif /* __HEAP_H__ */
