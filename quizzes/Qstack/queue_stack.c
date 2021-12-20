#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "stack.h"



typedef struct qstack
{
	stack_t *stackEQ;
	stack_t *stackDQ;

}qstack_t; 




void Dequeue(qstack_t *q_t)
{
	assert(NULL != q_t->stackDQ);
	StackPop(q_t->stackDQ);
}


void Enqueue(qstack_t *q_t, void *data)
{
	while(!StackIsEmpty(q_t->stackEQ))
	{
		StackPush(q_t->stackDQ,StackPeek(q_t->stackEQ));
		StackPop(q_t->stackEQ);
	}
	StackPush(q_t->stackEQ,data);

	while(!StackIsEmpty(q_t->stackDQ))
	{
		StackPush(q_t->stackEQ,StackPeek(q_t->stackDQ));
		StackPop(q_t->stackDQ);
	}
}
void Destroy(qstack_t *q_t)
{
	StackDestroy(q_t->stackDQ);
	StackDestroy(q_t->stackEQ);

	free(q_t);
	q_t = NULL;
}

int main(void)
{

qstack_t *qt = NULL;
int test = 9,test2 = 5;
void *viewptr = NULL;
qt = (qstack_t *)calloc(2,sizeof(struct qstack));

qt->stackDQ = StackCreate(10,4);
qt->stackEQ = StackCreate(10,4);

assert(NULL!= qt);

Enqueue(qt,&test);
Enqueue(qt,&test2);


Destroy(qt);



return 0;

}