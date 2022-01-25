#include <stdio.h>    /* printf */
#include <assert.h> /* assert */



#include "recursion.h"

#include "../include/stack.h"



static void InSortedStack(stack_t *stack, int val);

	








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
	assert(0 <= element_index );

	if( (element_index == 0) ||(element_index == 1) )
	{
		return element_index;
	}

	return (RecFibonacci(element_index - 1) + RecFibonacci(element_index - 2) );
}




node_t *RecFlipList(node_t *head)
{
	node_t *new;
	if((NULL == head->next) || (NULL == head))
	{
		return head;
	}
	new = RecFlipList(head->next);
	head->next->next = head;
	head->next = NULL;
	return new;
}

static void InSortedStack(stack_t *stack, int val)
{
	int pop = 0;
	if ((StackIsEmpty(stack)) || (val > (*(int *)StackPeek(stack))))
	{
		StackPush(stack, &val);
		return;
	}
	pop = *(int *)StackPeek(stack);
	StackPop(stack);

	InSortedStack(stack, val);

	StackPush(stack, &pop);

}

void RecSort(stack_t *stack)
{
	int peek = 0;
	if (StackIsEmpty(stack))
		return;

	peek = *(int *)StackPeek(stack);
	StackPop(stack);

	RecSort(stack);
	InSortedStack(stack, peek);

}




size_t RecStrLen(const char *strq)
{
	size_t len = 0;
	if( '\0' == *strq)
	{
		return len;
	}

	return (RecStrLen(++strq) + (++len));

}

int RecStrCmp(const char *s1, const char *s2)
{
	
	if(( '\0' == *s1) || ( '\0' == *s2) || ( *s1 != *s2))
	{
		return *s1 - *s2;
	}
	
	return (RecStrCmp(++s1, ++s2));
}










