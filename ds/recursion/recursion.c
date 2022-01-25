#include <stdio.h>    /* printf */
#include <assert.h> /* assert */



#include "recursion.h"




static void PrintRec(int);
int IterFibonacci(int element_index);
int RecFibonacci(int element_index);
node_t *RecFlipList(node_t *head);
static char ReverseString(char *input);


	
	/*ReverseString(" hello my name");
	printf("\n");
	
	PrintRec(5);
	printf("\n");
	
	*/
	





static void PrintRec(int val)
{
	if (val == 10)
	{
		return;
	}
	printf("%d ", val);
	PrintRec(val + 1);


}

int IterFibonacci(int element_index)
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


int RecFibonacci(int element_index)
{
	if( (element_index == 0) ||(element_index == 1) )
	{
		return element_index;
	}
	return (RecFibonacci(element_index - 1) + RecFibonacci(element_index - 2) );
}

static char ReverseString(char *input)
{
	if( '\0' == *input)
		return *input;
	
	++input;
	return (ReverseString(input)+ printf("%c", *input));
}


node_t *RecFlipList(node_t *head)
{
	node_t *new;
	if((NULL == head) || (NULL == head->next))
	{
		return head;
	}
	new = RecFlipList(head->next);
	head->next->next = head;
	head->next = NULL;
	return new;
}

