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
	printf("peekaboo %p\n",ptr2);

	
	StackPush(stacky, &f1);
	ptr2 = StackPeek(stacky);
	printf("peekaboo adrs %p\n",StackPeek(stacky));
	printf("peekaboo val is %f\n",(*(float*)StackPeek(stacky)));
	

	StackPush(stacky, ptr);
	printf("peekaboo adrs %p\n",StackPeek(stacky));
	

	StackPush(stacky, &test2);
	ptr2 = StackPeek(stacky);
	printf("peekaboo adrs %p\n",ptr2);
	printf("peekaboo val is %ld\n",(*(size_t*)StackPeek(stacky)));
	StackIsEmpty(stacky)? printf("stack is empty\n") : printf("stack is not empty\n");
	
	printf("occupied elements are: %ld\n",StackSize(stacky));

	StackPop(stacky); 
	printf("after pop occupied elements are: %ld\n",StackSize(stacky));
	printf("peekaboo %p\n",StackPeek(stacky));
	StackPop(stacky); 
	printf("after pop occupied elements are: %ld\n",StackSize(stacky));
	printf("total capacity is: %ld\n",StackCapacity(stacky));
	
	StackDestroy(stacky);

	return 0;

	


}
