/**********************************************
 * Priority Q - Heap - WS		              *
 * Developer: Tanya                     	  *
 * Written: 2021-12-23                   	  *
 *                                            *
 * Reviewer:             		  *
 **********************************************/


#include <stdlib.h> /* memory allocation  */
#include <assert.h>  /* assert()         */
#include <string.h>   /* memset         */


#include "heap.h"
#include "pq_heap.h"


struct pqueue
{
	heap_t *heap;
};



pq_t *PQCreate(pq_cmp_func_t comp_func)
{
	pq_t *pq = NULL;

	assert(NULL != comp_func);

	pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == pq)
	{
		return NULL;
	}

	pq->heap = HeapCreate(comp_func);
	if(NULL == pq->heap)
	{
		free(pq);
		pq = NULL;
	}
	return pq;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapDestroy(pq->heap);
	pq->heap = NULL;

	memset(pq, 0, sizeof(pq_t));

	free(pq);
	pq = NULL;
}

int PQIsEmpty(const pq_t *pq)
{
	assert (NULL != pq);

	return HeapIsEmpty(pq->heap);
}

size_t PQSize(const pq_t *pq)
{
	assert (NULL != pq);

	return HeapSize(pq->heap);
}

int PQEnqueue(pq_t *pq, void *data)
{
	size_t size = 0;

	assert (NULL != pq);

	size = PQSize(pq);
	HeapPush(pq->heap, data);

	return !(PQSize(pq) > size);
}

void *PQDequeue(pq_t *pq)
{
	void *peek = NULL;
	assert (NULL != pq);

	peek = HeapPeek(pq->heap);
	HeapPop(pq->heap);
	return peek;
}

void *PQPeek(const pq_t *pq)
{
	assert (NULL != pq);

	return HeapPeek(pq->heap);
}

void PQClear(pq_t *pq)
{
	assert (NULL != pq);

	while(!PQIsEmpty(pq))
	{
		HeapPop(pq->heap);
	}
}

void *PQErase(pq_t *pq, pq_match_func_t match_func, void *param)
{
	
	void *data = NULL;

	assert (NULL != pq);
	assert (NULL != match_func);

	data = HeapRemove(pq->heap, match_func, param);

	return data;
}



