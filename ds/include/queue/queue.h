#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>  /* size_t */

typedef struct queue queue_t;

/* time complexity: O(1), space complexity O(1) */
queue_t *QueueCreate(void);

/* time complexity: O(n), space complexity O(1) */
void QueueDestroy(queue_t *queue);

/* time complexity: O(1), space complexity O(1) */
int QueueEnqueue(queue_t *queue, void *data);

/* time complexity: O(1), space complexity O(1) */
void QueueDequeue(queue_t *queue);

/* time complexity: O(1), space complexity O(1) */
void *QueuePeek(const queue_t *queue);

/* time complexity: O(n), space complexity O(1) */
size_t QueueSize(const queue_t *queue);

/* time complexity: O(1), space complexity O(1) */
int QueueIsEmpty(const queue_t *queue);

/* time complexity: O(1), space complexity O(1) */
void QueueAppend(queue_t *dest, queue_t *src)

#endif /* __QUEUE_H__ */
