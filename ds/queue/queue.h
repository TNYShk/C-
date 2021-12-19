#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>  /* size_t */

typedef struct queue queue_t;

/* time complexity: O(1), space complexity O(1)
Creates Q and returns ptr to it, NULL if failed */
queue_t *QueueCreate(void);

/* time complexity: O(n), space complexity O(1)
Destroys given Q,frees allocated memory of all nodes */
void QueueDestroy(queue_t *queue);

/* time complexity: O(1), space complexity O(1) 
add new element to the top of the Q*/
int QueueEnqueue(queue_t *queue, void *data);

/* time complexity: O(1), space complexity O(1) 
Removes first element from the Q FIFO*/
void QueueDequeue(queue_t *queue);

/* time complexity: O(1), space complexity O(1) 
returns data of the first element in the Q
the one that will be dequeued*/
void *QueuePeek(const queue_t *queue);

/* time complexity: O(n), space complexity O(1) 
return number of elements in the Q, its current size*/
size_t QueueSize(const queue_t *queue);

/* time complexity: O(1), space complexity O(1) 
checks wether the Q is empty (1)*/
int QueueIsEmpty(const queue_t *queue);

/* time complexity: O(1), space complexity O(1)
appends src Q into dest Q.
dest now holds src, while src size is 0 */
void QueueAppend(queue_t *dest, queue_t *src);

#endif /* __QUEUE_H__ */
