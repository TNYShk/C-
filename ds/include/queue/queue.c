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

enum stats
{
	FAIL = -1, 
	NOTK, 
	OK
};


queue_t *QueueCreate(void)
{
	queue_t *qt = NULL;

	qt = (queue_t *)malloc(sizeof(struct queue));

	if(NULL == qt)
	{
		return NULL
	}
	qt->sll = SListCreate();

	if (NULL == qt->slist)
	{
		free(qt);
		qt = NULL
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

	slist_iter_t  qlist= NULL

	assert(NULL != queue);
	assert(NULL != data);


}



