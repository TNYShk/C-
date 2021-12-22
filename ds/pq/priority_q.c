/**********************************************
 * Sort List File - WS              		  *
 * Developer: Tanya                     	  *
 * Written: 2021-12                       	  *
 *                                            *
 * Reviewer:                         		  *
 **********************************************/

#include <stdio.h>  /* printf, size_t      */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert()          */
#include <string.h> /*memset            */
#include "dll.h"
#include "sorted_list.h"
#include "priority_queue.h"




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
		SortListDestroy(priorq->sortl);
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
	assert (NULL != pq);
	SortListInsert(pq->sortl, data);

	return (PQIsEmpty(pq));

}



