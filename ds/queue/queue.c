#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */

#include "sll.h"
#include "queue.h"

/*********Reviewed by David**********
*		Dec 16						*
*									*
*		created by Tanya			*
*		Updated Dec 18				*
************************************/

struct queue
{
	slist_t *slist;
};




queue_t *QueueCreate(void)
{
	queue_t *qt = NULL;

	qt = (queue_t *)malloc(sizeof(struct queue));

	if(NULL == qt)
	{
		return NULL;
	}

	qt->slist = SListCreate();

	if (NULL == qt->slist)
	{
		free(qt);
		qt = NULL;
		return NULL;
	}

	return qt;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue->slist);

	SListDestroy(queue->slist);

	free(queue);
	queue = NULL;
}



int QueueEnqueue(queue_t *queue, void *data)
{
	size_t org_size = 0, new_size = 0;
	
	assert(NULL != queue);

	org_size = QueueSize(queue);
	SListInsertBefore(SListEnd(queue->slist),data);
	new_size = QueueSize(queue);

	return (org_size != new_size);
}

void QueueDequeue(queue_t *queue)
{
	assert (NULL != queue);

	SListRemove(SListBegin(queue->slist));
}

void *QueuePeek(const queue_t *queue)
{
	assert (NULL != queue);

	return SListGetData(SListBegin(queue->slist));
}

size_t QueueSize(const queue_t *queue)
{
	assert (NULL != queue);

	return SListCount(queue->slist);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert (NULL != queue);

	return SListIsEmpty(queue->slist);
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert (NULL != dest);
	assert (NULL != src);

	SlistAppend(dest->slist, src->slist);
}

