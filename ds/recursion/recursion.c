#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */
#include <stdlib.h>


typedef struct node
{
	void *data;
	struct node *next;
}node_t;


static void TestFlip();
static void TestFibo();
static void PrintRec(int);
int FibonacciIterate(int element_index);
int FibonacciRec(int element_index);
node_t *FlipRec(node_t *head);
static char ReverseString(char *input);





int main(void)
{
	TestFibo();
	TestFlip();
	
	/*ReverseString(" hello my name");
	printf("\n");
	
	PrintRec(5);
	printf("\n");
	
	*/
	
	return 0;
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

int FibonacciIterate(int element_index)
{
	int ans = 1;
	int x1 = 1, x2 = 1;
	
	while(element_index > 2)
	{
		ans = x1 + x2;
		x1 = x2;
		x2 = ans;
		--element_index;
	}
	return ans;
}


int FibonacciRec(int element_index)
{
	if( (element_index == 0) ||(element_index == 1) )
	{
		return element_index;
	}
	return (FibonacciRec(element_index - 1) + FibonacciRec(element_index - 2) );
}

static char ReverseString(char *input)
{
	if( '\0' == *input)
		return *input;
	
	++input;
	return (ReverseString(input)+ printf("%c", *input));
}


node_t *FlipRec(node_t *head)
{
	node_t *new;
	if((NULL == head) || (NULL == head->next))
	{
		return head;
	}
	new = FlipRec(head->next);
	head->next->next = head;
	head->next = NULL;
	return new;
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
	FlipRec(head);
	printf("post flip data in two.next->data is %d\n", *(int *)two.next->data);
	printf("post flip data in three.next->data is %d\n", *(int *)three.next->data);
}

static void TestFibo()
{
	printf("\n\t-----------------------Fibonacci, get element----------------------------------------\n");
	printf("\nRecursive(5): %d ",FibonacciRec(5));
	printf("\nIterative(5): %d ",FibonacciIterate(5));
	printf("\n");
	printf("\nIterative (40): %d ",FibonacciIterate(40));
	printf("\nRecursive(40): %d ",FibonacciRec(40));
	printf("\n");
}