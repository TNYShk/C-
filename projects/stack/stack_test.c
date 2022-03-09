#include <stdlib.h> /* size_t, dyncamic memory allocation  */
#include <stdio.h> /* printf*/
#include <assert.h> /* asserts */

#include "stack.h"



int main()

{
	stack_t *stacky = NULL;
	size_t test = 9,test2 = 5;
	float f1 = 3.14;
	
	void *ptr = &test;
	void *ptr2 = NULL;
	
	stacky = StackCreate(10,8);
	assert (NULL != stacky);
	
	StackPush(stacky, &test);
	ptr2 = StackPeek(stacky);
	printf("\telement pushed!, adrs is now %p\n",StackPeek(stacky));
	
	StackPush(stacky, &f1);
	ptr2 = StackPeek(stacky);
	printf("\telement pushed!, adrs is now %p\n",ptr2);
	printf("peekaboo val is %f\n",(*(float*)StackPeek(stacky)));
	

	StackPush(stacky, ptr);
	printf("\telement pushed!, adrs is now %p\n",StackPeek(stacky));
	

	StackPush(stacky, &test2);
	ptr2 = StackPeek(stacky);
	printf("\telement pushed!, adrs is now %p\n",ptr2);
	
	printf("peekaboo value is %ld\n",(*(size_t*)StackPeek(stacky)));
	StackIsEmpty(stacky)? printf("\nstack is empty\n") : printf("\nstack is not empty\n");
	
	printf("\ncurrently, occupied elements are: %ld\n",StackSize(stacky));

	StackPop(stacky); 
	printf("\nafter pop occupied elements are: %ld\n",StackSize(stacky));
	
	StackPop(stacky); 

	printf("after pop occupied elements are: %ld\n",StackSize(stacky));
	
	printf("\ntotal capacity is: %ld\n",StackCapacity(stacky));
	printf("remaining slots: %ld\n",StackCapacity(stacky) - StackSize(stacky));
	
	StackDestroy(stacky);

	return 0;

	


}
