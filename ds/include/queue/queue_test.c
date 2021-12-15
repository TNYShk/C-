#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy */

#include "sll.h"
#include "queue.h"


int main(void)
{
	
	queue_t *qt = NULL;

	void *ptr = NULL; 
	void *peek = NULL;

	size_t t = 444;

	float f = 3.14;

	qt = QueueCreate();
	(QueueIsEmpty(qt) == 1) ? printf("Q is Empty\n") : printf("Q has been stuffed\n");
	ptr = &f;
	printf("enqueing %d\n", QueueEnqueue(qt,ptr));
	(QueueIsEmpty(qt) == 1) ? printf("Q is Empty\n") : printf("Q has been stuffed\n");
	
	peek = QueuePeek(qt);
	printf("peekaboo! top %f\n", *(float*)peek);

	ptr = &t;
	printf("enqueing %d\n", QueueEnqueue(qt,ptr));
	printf("size? %ld\n",QueueSize(qt));
	peek = QueuePeek(qt);
	printf("peekaboo! top %ld\n", *(size_t*)peek);
	t = 666;
	printf("enqueing %d\n", QueueEnqueue(qt,ptr));
	printf("size? %ld\n",QueueSize(qt));

	QueueDequeue(qt);
	peek = QueuePeek(qt);
	printf("peekaboo! top %ld\n", *(size_t*)peek);


	


	QueueDestroy(qt);

	return 0;
}