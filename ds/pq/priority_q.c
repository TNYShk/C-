/**********************************************
 * Priority Q - WS		              		  *
 * Developer: Tanya                     	  *
 * Written: 2021-12-23                   	  *
 *                                            *
 * Reviewer:  Ori Marom             		  *
 **********************************************/

#include <stdio.h>  /* printf, size_t      */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert()          */
#include <string.h> /*memset            */


#include "sorted_list.h"
#include "priority_queue.h"


enum stats
{
    FAIL = -1,
    SUCCESS,
    FOUND
};


struct pqueue
{
	sort_list_t *sortl;
	cmp_func_t comp_func;
};


pq_t *PQCreate(cmp_func_t comp_func)
{
	pq_t *priorq = NULL;

	priorq = (pq_t *)malloc(sizeof(pq_t));

	assert(NULL != comp_func);
	if (NULL == priorq)
	{
		return NULL;
	}

	priorq->sortl = SortListCreate(comp_func);

	if(NULL == priorq->sortl)
	{
		free(priorq);
		return NULL;
	}

	priorq->comp_func = comp_func;

	return priorq;
}

void PQDestroy(pq_t *pq)
{
	SortListDestroy(pq->sortl);
	memset(pq, 0, sizeof(pq_t));
	pq->sortl = NULL;

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
	return (SortListPopFront(pq->sortl));
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

int PQErase(pq_t *pq, match_func_t match_func, void *param)
{
	sort_list_iter_t from = {0};
	sort_list_iter_t to = {0};
	sort_list_iter_t find;
	int statos = FAIL;

	assert (NULL != pq);
	assert (NULL != match_func);

	from = SortListBegin(pq->sortl);
	to = SortListEnd(pq->sortl);

	while (!SortListIterIsEqual(from,to))
	{
		find = SortListFindIf(from, to, match_func, param);
		statos = SUCCESS;
		
		if(!SortListIterIsEqual(find,to))
		{
			statos = FOUND;
			from = SortListRemove(find);
		}
		else
		{
			from = SortListNext(from);
		}
	}

	return statos;
}




