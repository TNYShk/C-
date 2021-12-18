#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy */

#include "sll.h"
#include "queue.h"

/*menory leak and error in append */



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

	(QueueIsEmpty(qt) == 1) ? printf("\nQ is Empty\n") : printf("\nQ has been stuffed\n");
	ptr = &f;

	printf("---------------------------enque Q and Q2---------------------\n");
	printf("enque (%d)\n", QueueEnqueue(qt,ptr));
	printf("\nenque to Q2 (%d)\n\n", QueueEnqueue(qt2,ptr));
	(QueueIsEmpty(qt) == 1) ? printf("Q is Empty\n") : printf("Q has been stuffed\n");
	(QueueIsEmpty(qt2) == 1) ? printf("Q2 is Empty\n") : printf("Q2 has been stuffed\n");
	
	printf("---------------------------peek into Q---------------------\n");
	peek = QueuePeek(qt);
	printf("peekaboo! %f\n", *(float*)peek);

	printf("------------------enque Q & Q2 same val---------------------\n");
	ptr = &t;
	printf("enque to Q(%d)\n", QueueEnqueue(qt,ptr));
	printf("\nenque to Q2 (%d)\n", QueueEnqueue(qt2,ptr));
	printf("---------------------------peek into Q2---------------------\n");
	peek = QueuePeek(qt2);
	printf("peekaboo!  %f\n", *(float*)peek);

	printf("Q2 size? %ld\n",QueueSize(qt2));
	printf("Q size? %ld\n",QueueSize(qt));

	QueueAppend(qt,qt2);
	printf("\nAppended Q2 into Q1\n");
	printf("post append Q2 size: %ld\n",QueueSize(qt2));
	printf("post append Q2 size: %ld\n",QueueSize(qt));

	printf("---------------------------enque and deque into Q---------------------\n");
	
	
	QueueDequeue(qt);
	printf("post dequeue Q size: %ld\n",QueueSize(qt));
	peek = QueuePeek(qt);
	printf("peekaboo!  %ld\n", *(size_t*)peek);
	printf("enque Q (%d)\n", QueueEnqueue(qt,ptr));
	printf("Q size? %ld\n",QueueSize(qt));
	QueueDequeue(qt);
	printf("post dequeue Q size: %ld\n",QueueSize(qt));

	
	printf("---------------------------peek into Q---------------------\n");
	peek = QueuePeek(qt);
	printf("peekaboo!  %f\n", *(float*)peek);


	


	
	QueueDestroy(qt2);
	QueueDestroy(qt);
	return 0;
}