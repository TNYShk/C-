/**********************************************
 * Priority Q - WS		              		  *
 * Developer: Tanya                     	  *
 * Written: 2021-12-23                   	  *
 *                                            *
 * Reviewer:  Ori Marom             		  *
 **********************************************/


#include <stdlib.h> /* memory allocation  */
#include <assert.h>  /* assert()         */
#include <string.h>   /* memset         */


#include "sorted_list.h"
#include "pq.h"


struct pqueue
{
	sort_list_t *sortl;
};

typedef sort_list_iter_t pq_iter_t;

pq_t *PQCreate(pq_cmp_func_t comp_func)
{
	pq_t *priorq = NULL;

	assert(NULL != comp_func);

	priorq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == priorq)
	{
		return NULL;
	}

	priorq->sortl = SortListCreate(comp_func);
	if(NULL == priorq->sortl)
	{
		free(priorq);
		priorq = NULL;
	}
	return priorq;
}

void PQDestroy(pq_t *pq)
{
	SortListDestroy(pq->sortl);
	pq->sortl = NULL;
	memset(pq, 0, sizeof(pq_t));

	free(pq);
	pq = NULL;
}

int PQIsEmpty(const pq_t *pq)
{
	assert (NULL != pq);

	return SortListIsEmpty(pq->sortl);
}

size_t PQSize(const pq_t *pq)
{
	assert (NULL != pq);

	return SortListSize(pq->sortl);
}

int PQEnqueue(pq_t *pq, void *data)
{
	size_t size = 0;

	assert (NULL != pq);

	size = PQSize(pq);
	SortListInsert(pq->sortl, data);

	return !(PQSize(pq) > size);
}

void *PQDequeue(pq_t *pq)
{
	assert (NULL != pq);
	return SortListPopFront(pq->sortl);
}

void *PQPeek(const pq_t *pq)
{
	assert (NULL != pq);
	return SortListGetData(SortListBegin(pq->sortl));
}

void PQClear(pq_t *pq)
{
	assert (NULL != pq);

	while(!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pq_t *pq, pq_match_func_t match_func, void *param)
{
	pq_iter_t from = {0};
	pq_iter_t to = {0};
	pq_iter_t find = {0};
	
	void *data = NULL;

	assert (NULL != pq);
	assert (NULL != match_func);

	from = SortListBegin(pq->sortl);
	to = SortListEnd(pq->sortl);

	find = SortListFindIf(from, to, (match_func_t)match_func, param);
		
		if(!SortListIterIsEqual(find,to))
		{
			data = SortListGetData(find);
			SortListRemove(find);
		}
	return data;
}



