#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */


#include "sll.h"
#include "queue.h"


void TestUno();


int main(void)
{
	TestUno();
	
	return 0;
}





void TestUno()
{
	queue_t *qt = NULL;
	queue_t *qt2 = NULL;

	void *peek = NULL;
	void *peek2 = NULL; 
	
	float f = 3.14;
	size_t tt= 60;
	int t = 250;
	printf("\n\t---------------------------starting Q---------------------\n");
	qt = QueueCreate();
	qt2 = QueueCreate();
	assert (NULL != qt);
	assert (NULL != qt2);
	assert(QueueIsEmpty(qt));

	(QueueIsEmpty(qt) == 1) ? printf("\nQ is Empty\n") : printf("\nQ has been stuffed\n");
	
	printf("\n\t---------------------------Enque Q and print ---------------------\n");
	
	assert(QueueEnqueue(qt,&f) == 1);
	(QueueIsEmpty(qt) == 1) ? printf("Q is Empty\n") : printf("Q has been stuffed\n");
	peek = QueuePeek(qt);
	printf("peekaboo! %f\n", *(float*)peek);
	printf("\n\t---------------------------Enque Q  ---------------------\n");
	assert(QueueEnqueue(qt,&t) == 1);
	printf("Enqueue Q, size is %ld\n",QueueSize(qt));

	printf("\n\t---------------------------Deque Q ---------------------\n");
	QueueDequeue(qt);
	assert(QueueSize(qt) == 1);
	peek = QueuePeek(qt);
	printf("peekaboo! %d\n", *(int*)peek);
	printf("Post Deque,Q size is %ld\n",QueueSize(qt));

	printf("\n\t---------------------------Enque Q2 and print ---------------------\n");
	(QueueIsEmpty(qt2) == 1) ? printf("\nQ2 is Empty\n") : printf("\nQ2 has been stuffed\n");
	assert(QueueEnqueue(qt2,&tt) == 1);
	printf("Enqueue Q2, size is %ld\n",QueueSize(qt2));
	peek2 = QueuePeek(qt2);
	printf("peekaboo! %ld\n", *(size_t*)peek2);
	assert(QueueEnqueue(qt2,&t) == 1);
	assert(QueueEnqueue(qt2,&f) == 1);
	printf("Enqueue Q2 , size is %ld\n",QueueSize(qt2));
	printf("\n\t---------------------------Deque Q2 ---------------------\n");
	QueueDequeue(qt2);
	peek2 = QueuePeek(qt2);
	printf("peekaboo! %d\n", *(int*)peek);
	printf("Post Deque Q2 size is %ld\n",QueueSize(qt2));
	printf("\n\t---------------------------Append Q into Q2  ---------------------\n");
	QueueAppend(qt2, qt);
	printf("Post Append Q2 size is %ld\n",QueueSize(qt2));
	printf("Post Append Q size is %ld\n",QueueSize(qt));
	printf("\n\t---------------------------Deque Appended Q2 ---------------------\n");
	QueueDequeue(qt2);
	printf("Post Deque Q2 size is %ld\n",QueueSize(qt2));
	peek2 = QueuePeek(qt2);
	printf("peekaboo! %f\n", *(float*)peek2);
	printf("\n\t---------------------------END OF TEST---------------------\n\n");
	QueueDestroy(qt);
	QueueDestroy(qt2);
}

