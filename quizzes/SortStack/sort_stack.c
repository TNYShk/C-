
#include <stdio.h> /*print */
#include <assert.h> /* assert*/
#include <stdlib.h> /*memory allocation & free */
#include <string.h> /* testing strlen, strcmp, strstr*/

#include "stack.h"

void RecSort(stack_t *stack);
void InSortedStack(stack_t *stack, int number);
void SortStacks(stack_t *stack, stack_t *temp);
stack_t *SortStackss(stack_t **stack, size_t capacity, size_t size);

static void PrintStack(stack_t *stack);
void TestStack();
void Test2Stacks();

int main(void)
{
    TestStack(); 
	Test2Stacks();

/* stack_t *tosort = StackCreate(6, sizeof(int));
	stack_t *another = NULL;
	int num1 = 100;
    int num2 = 1;
    int num3 = 2;
    int num4 = -5;
    int num5 = 4;
	int num6 = 101;

	StackPush(tosort, &num1);
    StackPush(tosort, &num2);
    StackPush(tosort, &num3);
    StackPush(tosort, &num4);
    StackPush(tosort, &num5);
    StackPush(tosort, &num6);
	printf("stack is empty? %d\n", StackIsEmpty(tosort));
	printf("\nStack before:\n");
    PrintStack(tosort);

	another = SortStackss(&tosort, 6,sizeof(int));
	printf("\nStack after:\n");
    PrintStack(another);

	StackDestroy(tosort);
    StackDestroy(another);

 */

    return 0;
}

void Test2Stacks(void)
{
	stack_t *tosort = StackCreate(6, sizeof(int));
	stack_t *another = StackCreate(6, sizeof(int));
	int num1 = 100;
    int num2 = 1;
    int num3 = 2;
    int num4 = -5;
    int num5 = 4;
	int num6 = 101;

	StackPush(tosort, &num1);
    StackPush(tosort, &num2);
    StackPush(tosort, &num3);
    StackPush(tosort, &num4);
    StackPush(tosort, &num5);
    StackPush(tosort, &num6);
	printf("stack is empty? %d\n", StackIsEmpty(tosort));
	printf("\nStack before:\n");
    /* PrintStack(tosort); */

	SortStacks(tosort, another);
	printf("\nStack after:\n");
    PrintStack(another);

	  StackDestroy(tosort);
    StackDestroy(another);

}



void TestStack(void)
{
	stack_t *sstack = NULL;
	stack_t *copy_stack = NULL;

	int num1 = 10;
    int num2 = 3;
    int num3 = -12;
    int num4 = 5;
    int num5 = 4;
    printf("\n\t----------------------------Recursive Stack Sort-------------------------------------------\n");
    sstack = StackCreate(5, sizeof(int));
    copy_stack = StackCreate(5, sizeof(int));

    StackPush(sstack, &num1);
    StackPush(copy_stack, &num1);
    StackPush(sstack, &num2);
    StackPush(copy_stack, &num2);
    StackPush(sstack, &num3);
    StackPush(copy_stack, &num3);
    StackPush(sstack, &num4);
    StackPush(copy_stack, &num4);
    StackPush(sstack, &num5);
    StackPush(copy_stack, &num5);

   	printf("\nStack before:\n");
    PrintStack(copy_stack);

    RecSort(sstack);
    printf("\nStack after:\n");
    PrintStack(sstack);

    StackDestroy(sstack);
    StackDestroy(copy_stack);
}

static void PrintStack(stack_t *stack)
{
	while(!StackIsEmpty(stack))
	{
		int peek = *(int *)StackPeek(stack);
		printf("%d ", peek);
		StackPop(stack);
	}
	printf("\n");
}

void SortStacks(stack_t *stack, stack_t *temp)
{
	int peek = 0;
	
	assert(NULL != temp);
	assert(NULL != stack);


	while(!StackIsEmpty(stack))
	{
		peek = *(int *)StackPeek(stack);
		
		StackPop(stack);

		while(!StackIsEmpty(temp) && (peek > *(int *)StackPeek(temp)))
		{
			StackPush(stack, StackPeek(temp));
			StackPop(temp);
		}
		
		StackPush(temp, &peek);
	}
	
	
	
}

stack_t *SortStackss(stack_t **stack, size_t capacity, size_t size)
{
	int peek = 0;
	stack_t *temp = StackCreate(capacity, size);

	assert(NULL != temp);
	assert(NULL != stack);

	printf("stack is empty? %d\n", StackIsEmpty(*stack));
	while(!StackIsEmpty(*stack))
	{
		peek = *(int *)StackPeek(*stack);
		printf("peekyyyyy is %d\n", peek);
		StackPop(*stack);

		while(!StackIsEmpty(temp) && (peek > *(int *)StackPeek(temp)))
		{
			StackPush(*stack, StackPeek(temp));
			StackPop(temp);
		}
		
		StackPush(temp, &peek);
	}
	
	return temp;
	
}




void RecSort(stack_t *stack)
{
	int peek = 0;

	assert(NULL != stack);
	
	if (StackIsEmpty(stack))
	{
		return;
	}

	peek = *(int *)StackPeek(stack);
	StackPop(stack);

	RecSort(stack);

	InSortedStack(stack, peek);

}

void InSortedStack(stack_t *stack, int number)
{
	if (!(StackIsEmpty(stack)) && (number > (*(int *)StackPeek(stack))))
	{
		int peek = *(int *)StackPeek(stack);
		StackPop(stack);
		
		InSortedStack(stack, number);
		
		StackPush(stack, &peek);
		
		return;
	}

	StackPush(stack, &number);
}