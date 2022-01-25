#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */
#include <stdlib.h>

#include "recursion.h"

static void TestFibo();
static void TestFlip();
static void TestStringH();
static void TestStack();
static void PrintRec(int);
static char ReverseString(char *input);
static void PrintStack(stack_t *stack);



int main(void)
{

	TestFibo();
	TestFlip();
	TestStringH();
	TestStack();
	return 0;
}


static void TestFlip()
{
	int x = 1;
	int y = 2;
	int z = 3;
	int w = 4;
	

	node_t *head = NULL;

	node_t one;
	node_t two; 
	node_t three; 
	node_t four; 

	one.data = &x;
	one.next = &two;

	two.data = &y;
	two.next = &three;
	three.data = &z;
	three.next = &four;
	four.data = &w;
	four.next = NULL;
	
	head = &one;
	printf("\n\t----------------------------Recursive Flip-------------------------------------------\n");
	printf("before: data in two.next->data is %d\n", *(int *)two.next->data);
	printf("before: data in three.next->data is %d\n", *(int *)three.next->data);
	RecFlipList(head);
	printf("post flip data in two.next->data is %d\n", *(int *)two.next->data);
	printf("post flip data in three.next->data is %d\n", *(int *)three.next->data);
}

static void TestFibo()
{
	printf("\n\t-----------------------Fibonacci, get element----------------------------------------\n");
	printf("\t excluding zero");
	printf("\nRecursive(5): %d ",RecFibonacci(5));
	printf("\nIterative(5): %d ",IterFibonacci(5));
	printf("\n");
	printf("\nIterative (20): %d ",IterFibonacci(20));
	printf("\nRecursive(20): %d ",RecFibonacci(20));
	printf("\n");
}

static void TestStringH()
{
	printf("\n\t----------------------------Recursive string.h-------------------------------------------\n");
	printf("\nhello my name\n");
	ReverseString(" hello my name");
	printf("\n");
	printf("strlen %ld\n",RecStrLen("hello my name"));
	printf("\nhello\n");
	printf("strlen %ld\n",RecStrLen("hello"));
	printf("\nhell hell\n");
	printf("strcmp: %d\n",RecStrCmp("hell", "hell"));
	printf("\nhello hell\n");
	printf("strcmp: %d\n",RecStrCmp("hello", "hell"));
	printf("\nhell help\n");
	printf("strcmp: %d\n",RecStrCmp("hell", "help"));
}

static char ReverseString(char *input)
{
	if( '\0' == *input)
		return *input;
	
	++input;
	return (ReverseString(input)+ printf("%c", *input));
}

static void PrintRec(int val)
{
	if (val == 10)
	{
		return;
	}
	printf("%d ", val);
	PrintRec(val + 1);


}

static void TestStack()
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