/**********************************\
* RECURSION   source file          *
* Developer:  Tanya                *
* Written: 2021-1-25               *
*                                  *
* Reviewer:                        *
\**********************************/

#include <assert.h> /* assert */
#include <string.h> /* strlen, strncmp*/


#include "recursion.h" /* program header*/



static void InSortedStack(stack_t *stack, int val);
static int RecStrnCmp(const char *s1, const char *s2, size_t len);
	

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
	int peek = 0;

	if ((StackIsEmpty(stack)) || (val <= (*(int *)StackPeek(stack))))
	{
		StackPush(stack, &val);
		return;
	}

	peek = *(int *)StackPeek(stack);
	StackPop(stack);

	InSortedStack(stack, val);

	StackPush(stack, &peek);

}

void RecSort(stack_t *stack)
{
	int peek = 0;

	assert(NULL != stack);

	if(StackIsEmpty(stack))
	{
		return;
	}

	peek = *(int *)StackPeek(stack);
	StackPop(stack);

	RecSort(stack);
	InSortedStack(stack, peek);

}


size_t RecStrLen(const char *strq)
{
	size_t len = 0;

	assert(NULL != strq);

	if( '\0' == *strq)
	{
		return len;
	}

	return (RecStrLen(++strq) + (++len));

}

int RecStrCmp(const char *s1, const char *s2)
{
	
	if(( *s1 != *s2) || ( '\0' == *s1)  )
	{
		return (*s1 - *s2);
	}
	
	return RecStrCmp(++s1, ++s2);
}



char *RecStrCpy(char *dest, const char *src)
{
	char *runner = dest;

	assert(NULL != dest);

	if('\0' == *src)
	{
		return runner;
	}
	*dest = *src;
	return RecStrCpy(++dest, ++src);
}

char *RecStrCat(char *dest, const char *src)
{
	char *runner = dest + strlen(dest);
	
	assert(NULL != dest);

	if('\0' == *src)
	{
		return dest;
	}
	*runner = *src;
	return RecStrCpy(++runner, ++src); /*also: return RecStrCat(++runner, ++src) */
}

char *RecStrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);

	if ( ('\0' == *haystack) || (NULL == haystack))
	{
	  	return NULL;
	}
     
   if(strncmp(haystack, needle, RecStrLen(needle)) == 0)
   {
     return (char *)haystack;
   }

   return RecStrStr(++haystack, needle);
}

static int RecStrnCmp(const char *s1, const char *s2, size_t len)
{
	
	if( ( '\0' == *s1) || (0 == len) || ( *s1 != *s2) )
	{
		return (*s1 - *s2);
	}
	
	return RecStrnCmp(++s1, ++s2,--len);
}




