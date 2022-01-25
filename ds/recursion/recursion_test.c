#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */
#include <stdlib.h>

#include "recursion.h"

static void TestFibo();
static void TestFlip();

int main(void)
{

	TestFibo();
	TestFlip();
	
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
	printf("\nRecursive(5): %d ",RecFibonacci(5));
	printf("\nIterative(5): %d ",IterFibonacci(5));
	printf("\n");
	printf("\nIterative (40): %d ",IterFibonacci(40));
	printf("\nRecursive(40): %d ",RecFibonacci(40));
	printf("\n");
}