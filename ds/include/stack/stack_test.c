#include <stdlib.h> /* size_t, dyncamic memory allocation  */
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "stack.h"



int main()

{
	stack_t *stacky = NULL;
	size_t test,test2 = 5;
	float f1 = 3.14;
	void *ptr = &test;
	void *ptr2;
	stacky = StackCreate(10,8);
	assert (NULL != stacky);
	
	StackPush(stacky, &test);
	ptr2 = StackPeek(stacky);
	printf("post push adrs %p\n",ptr2);

	
	StackPush(stacky, &f1);
	ptr2 = StackPeek(stacky);
	printf("\npost push adrs %p\n",StackPeek(stacky));
	printf("peekaboo val is %f\n",(*(float*)StackPeek(stacky)));
	

	StackPush(stacky, ptr);
	printf("\npost push adrs %p\n",StackPeek(stacky));
	

	StackPush(stacky, &test2);
	ptr2 = StackPeek(stacky);
	printf("post push adrs %p\n",ptr2);
	
	printf("peekaboo value is %ld\n",(*(size_t*)StackPeek(stacky)));
	StackIsEmpty(stacky)? printf("\nstack is empty\n") : printf("\nstack is not empty\n");
	
	printf("\ncurrently, occupied elements are: %ld\n",StackSize(stacky));

	StackPop(stacky); 
	printf("\nafter pop occupied elements are: %ld\n",StackSize(stacky));
	printf("adrs in now %p\n",StackPeek(stacky));
	StackPop(stacky); 

	printf("after pop occupied elements are: %ld\n",StackSize(stacky));
	printf("adrs in now %p\n",StackPeek(stacky));
	printf("\ntotal capacity is: %ld\n",StackCapacity(stacky));
	printf("remaining slots: %ld\n",StackCapacity(stacky) - StackSize(stacky));
	StackDestroy(stacky);

	return 0;

	


}
