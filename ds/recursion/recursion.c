#include <stdio.h>    /* printf */
#include <assert.h> /* assert */



#include "recursion.h"




void PrintRec(int);
int IterFibonacci(int element_index);
int RecFibonacci(int element_index);
node_t *RecFlipList(node_t *head);
char ReverseString(char *input);


	








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
	if((NULL == head->next)|| (NULL == head))
	{
		return head;
	}
	new = RecFlipList(head->next);
	head->next->next = head;
	head->next = NULL;
	return new;
}


char ReverseString(char *input)
{
	if( '\0' == *input)
		return *input;
	
	++input;
	return (ReverseString(input)+ printf("%c", *input));
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


void PrintRec(int val)
{
	if (val == 10)
	{
		return;
	}
	printf("%d ", val);
	PrintRec(val + 1);


}