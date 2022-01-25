#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */
#include <stdlib.h>
#include <string.h>

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
	PrintRec(5);
	printf("\n");
	TestStringH();
	
	printf("\n");
	TestFibo();
	TestFlip();
	
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
	char *space = NULL;
	char *space1 = NULL;
	char *ans = NULL;
	char *ans1 = NULL;
	char *haystack = "%$#@!^%";
	char *needle = "!";
	printf("\n\t----------------------------Recursive string.h-------------------------------------------\n");
	
	printf("\nI hate strstr\n");
	ReverseString(" I hate strstr");
	printf("\n");
	printf("rec strlen %ld\n",RecStrLen("I hate strstr"));
	printf("real strlen: %ld\n", strlen("I hate strstr"));
	printf("\nhello\n");
	printf("rec strlen %ld\n",RecStrLen("hello"));
	printf("real strlen %ld\n",strlen("hello"));
	printf("\nhell hell\n");
	printf("rec strcmp: %d\n",RecStrCmp("hell", "hell"));
	printf("strcmp: %d\n",strcmp("hell", "hell"));
	printf("\nhello hell\n");
	printf("strcmp: %d\n",RecStrCmp("hello", "hell"));
	printf("strcmp: %d\n",strcmp("hello", "hell"));
	printf("\nhell help\n");
	printf("rec strcmp: %d\n",RecStrCmp("hell", "help"));
	printf("strcmp: %d\n",strcmp("hell", "help"));
	printf("\n");
	space = (char *)calloc(strlen("testing StrCpy and StrCat")+1, sizeof(char));
	space1 = (char *)calloc(strlen("testing StrCpy and StrCat")+1, sizeof(char));
	
	strcpy(space1,"testing StrCpy");
	RecStrCpy(space, "testing StrCpy");
	
	printf("\nrecursive StrCpy:\n%s\n", space);
	printf("original strcpy:\n%s\n", space1);
	
	strcat(space1," and StrCat");
	RecStrCat(space, " and StrCat");
	
	printf("\nrecursive StrCat:\n%s\n", space);
	printf("original strcat:\n%s\n", space1);
	printf("\ncomparing strings with recursive StrCmp:\n");
	(RecStrCmp(space, space1) == 0)? printf("strings are the same! Yey\n"): printf("Oh No something is wrong\n");
	memset(space,0,strlen(space));
	
	ans = RecStrStr(haystack,needle);
	printf("\nrec strstr ans is %s\n", ans);
	ans1 = strstr(haystack,needle);
	printf("real strstr ans is %s\n", ans1);

	free(space);
	free(space1);

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
	char string[10];
	if (val == 10)
	{
		return;
	}
	sprintf(string,"%d ", val);
	printf("%s ", string);
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
