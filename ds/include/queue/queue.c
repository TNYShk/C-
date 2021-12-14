#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy */

#include "sll.h"
#include "queue.h"


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

	slist_iter_t qtlist = NULL;

	assert(NULL != queue);
	assert(NULL != data);

	qtlist = SListInsertAfter(SListBegin(queue->slist),data);

	return (!SListIsEmpty(queue->slist));
}


void QueueDequeue(queue_t *queue)
{
	assert (NULL != queue);

	SListRemove(SListBegin(queue->slist));
}

void *QueuePeek(const queue_t *queue)
{
	assert (NULL != queue);

	return SListGetData(SListNext(SListBegin(queue->slist)));
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