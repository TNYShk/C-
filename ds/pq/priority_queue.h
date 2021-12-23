#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct pqueue pq_t;

#ifndef __SORTED_LIST_H__
typedef int (*cmp_func_t)(const void *left, const void *right);
typedef int (*match_func_t)(const void *data, const void *param);
#endif /* __SORTED_LIST_H__ */
/*
 * DESCRIPTION: 
 * Creates a new Priority Queue (PQ)
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: sort function to use for the sorting of the list
 * 
 * RETURN: Pointer to the newly created Priority Queue, otherwise NULL
 * Complexity: O(1) time, O(1) memory. */
pq_t *PQCreate(cmp_func_t cmp_func);

/*
 * DESCRIPTION: 
 * Destroy the PQ
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: the PQ
 * 
 * RETURN: NULL
 * Complexity: O(n) time, O(1) memory. */
void PQDestroy(pq_t *pq);

/*
 * DESCRIPTION: 
 * Checks wether the PQ is Empty
 * 
 * PARAMS: the PQ to check
 * 
 * RETURN: Bookean, 1 Empty, otherwise 0
 * Complexity: O(1) time, O(1) memory. */
int PQIsEmpty(const pq_t *pq);

/*
 * DESCRIPTION: 
 * Calculates number of elements int the PQ
 * 
 * PARAMS: pointer to the PQ 
 * 
 * RETURN: return number of elements in the PQ
 * Complexity: O(n) time, O(1) memory. */
size_t PQSize(const pq_t *pq);

/*
 * DESCRIPTION: 
 * Inserts new element to the PQ
 * insertion based on its priority- decided by the sort func, 
 * adding NULL data possible but causes undefined bahvior
 * 
 *
 * PARAMS: Pointer to the PQ, data to insert
 * 
 * RETURN: 0 for SUCCESS, any other num is FAIL
 * Complexity: O(n) time, O(1) memory. */
int PQEnqueue(pq_t *pq, void *data);

/*
 * DESCRIPTION: 
 * Remove the top element from the PQ
 * 
 * PARAMS: Pointer to the PQ
 * 
 * RETURN: Data of the removed element
 * Complexity: O(1) time, O(1) memory. */
void *PQDequeue(pq_t *pq);

/*
 * DESCRIPTION: 
 * Peek in to the data of the top element of the PQ, doesnt remove the element
 * 
 * 
 *
 * PARAMS: Pointer to the PQ
 * 
 * RETURN: Data of the element
 * Complexity: O(1) time, O(1) memory. */
void *PQPeek(const pq_t *pq);

/*
 * DESCRIPTION: 
 * Clears the PQ from its elements
 * 
 * 
 *
 * PARAMS: Pointer to the PQ
 * 
 * RETURN: None
 * Complexity: O(n) time, O(1) memory. */
void PQClear(pq_t *pq);

/*
 * DESCRIPTION: 
 * remove data from the elements of PQ, based on desired param
 * 
 * 
 *
 * PARAMS: Pointer to the PQ, the matching func and para,eter to remove
 * 
 * RETURN: integer
 * Complexity: O(n) time, O(1) memory. */
int PQErase(pq_t *pq, match_func_t match_func, void *param);

#endif /* __PRIORITY_QUEUE_H__ */
