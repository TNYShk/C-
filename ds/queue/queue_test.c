#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy */

#include "sll.h"
#include "queue.h"

/*testing is a mass not complete! */



int main(void)
{
	
	queue_t *qt = NULL;
	queue_t *qt2 = NULL;

	void *ptr = NULL; 
	void *peek = NULL;

	size_t t = 444;

	float f = 3.14;

	qt = QueueCreate();
	qt2 = QueueCreate();
	(QueueIsEmpty(qt) == 1) ? printf("Q is Empty\n") : printf("Q has been stuffed\n");
	ptr = &f;
	printf("enqueing %d\n", QueueEnqueue(qt,ptr));
	printf("\nenqueing to qt2 (%d)\n\n", QueueEnqueue(qt2,ptr));
	(QueueIsEmpty(qt) == 1) ? printf("Q is Empty\n") : printf("Q has been stuffed\n");
	
	peek = QueuePeek(qt);
	printf("peekaboo! top %f\n", *(float*)peek);

	ptr = &t;
	printf("enqueing %d\n", QueueEnqueue(qt,ptr));
	printf("\nenqueing to qt2 (%d)\n\n", QueueEnqueue(qt2,ptr));
	

	printf("qt2 size? %ld\n",QueueSize(qt2));
	printf("qt size? %ld\n",QueueSize(qt));

	QueueAppend(qt,qt2);

	printf("Appended qt2 into qt1\n");
	peek = QueuePeek(qt);
	printf("\npeekaboo!  %f\n", *(float *)peek);
	t = 666;
	printf("enqueing qt1 %d\n", QueueEnqueue(qt,ptr));

	QueueDequeue(qt);
	printf("post dequeue qt1 size? %ld\n",QueueSize(qt));
	printf("enqueing qt1 %d\n", QueueEnqueue(qt,ptr));
	printf("size? %ld\n",QueueSize(qt));
	QueueDequeue(qt);
	printf("dequeue size? %ld\n",QueueSize(qt));

	
	peek = QueuePeek(qt);
	printf("peekaboo!  %ld\n", *(size_t*)peek);


	


	QueueDestroy(qt);
	QueueDestroy(qt2);

	return 0;
}