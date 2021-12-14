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

	ptr = &f;
	printf("enqued? %d\n", QueueEnqueue(qt,ptr));
	ptr = &t;
	printf("enqued? %d\n", QueueEnqueue(qt,ptr));
	printf("size? %ld\n",QueueSize(qt));
	
	peek = QueuePeek(qt);
	printf("peekaboo! %f\n", *(float*)peek);

	QueueDequeue(qt);

	ptr = QueuePeek(qt);
	printf("peekaboo! %ld\n", *(size_t*)peek);
	


	QueueDestroy(qt);

	return 0;
}