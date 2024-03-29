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

#define MAX_FIBO_INT (100)

static void InSortedStack(stack_t *stack, int val);
static int RecStrnCmp(const char *s1, const char *s2, size_t len);
	

int IterFibonacci(int element_index)
{
	int ans = 1;
	int x1 = 1, x2 = 1;
	
	for(;2 < element_index; --element_index)
	{
		ans = x1 + x2;
		x1 = x2;
		x2 = ans;
	}
	return ans;
}


int RecFibonacci(int element_index)
{
	int prev = 0, pprev = 0;
	static int fibo_lut[MAX_FIBO_INT] = {0};
	
	assert(0 <= element_index);

	if( (0 == element_index) || (1 == element_index) )
	{
		return element_index;
	}

	prev = 0 != fibo_lut[element_index - 1]?
				fibo_lut[element_index - 1]:
				RecFibonacci(element_index -1);

	pprev = 0 != fibo_lut[element_index - 2]?
				fibo_lut[element_index - 2]:
				RecFibonacci(element_index -2);

	return ( prev + pprev );
}

node_t *RecFlipList(node_t *head)
{
	assert(NULL != head);

	if(NULL == head->next)
	{
		return head;
	}

	else
	{
		node_t *new = RecFlipList(head->next);
		head->next->next = head;
		head->next = NULL;

		return new;
	}
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

static void InSortedStack(stack_t *stack, int number)
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

size_t RecStrLen(const char *str)
{
	assert(NULL != str);

	if ('\0' == *str)
	{
		return 0;
	}

	return (1 + RecStrLen(str + 1));
}

int RecStrCmp(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);

	if ( ('\0' == *s1) || (*s1 != *s2) )
	{
		return (*s1 - *s2);
	}
	
	return RecStrCmp(++s1, ++s2);
}



char *RecStrCpy(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	*dest = *src;

	if ('\0' == *src)
	{
		return dest;
	}
	
	return (RecStrCpy(++dest, ++src) -1);
}



char *RecStrCat(char *dest, const char *src)
{
	size_t len = RecStrLen(dest);

	assert(NULL != src);
	
	return (RecStrCpy((dest + len), src) - len); 
}


char *RecStrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);

	if ('\0' == *haystack)
	{
	  	return NULL;
	}


    if (*haystack == *needle)
    {
     	if (!RecStrnCmp(haystack, needle, RecStrLen(needle)))
   		{
     		return (char *)haystack;
   		}
    }

   return RecStrStr(haystack + 1, needle);
}



static int RecStrnCmp(const char *s1, const char *s2, size_t len)
{
	
	if ( ('\0' == *s1) || (1 == len) || (*s1 != *s2) )
	{
		return (*s1 - *s2);
	}
	
	return RecStrnCmp(++s1 , ++s2,--len);
}


/* malloc memoization option- NOT COMPLETE
int Fibonacci(int elem_idx)
{
	static int *fibo_lut = NULL;

	if (NULL = fibo_lut)
	{	
		fibo_lut = (int *)calloc(elem_idx, sizeof(int));
		if(NULL == fibo_lut)
		{
			return NULL;
		}	
	}
}
*/

/*
char *RecStrCat(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	if ('\0' == *dest)
	{
		return RecStrCpy(dest,src);
	}

	return (RecStrCat(dest + 1, src) - 1); 
	
}*/

/*
char *RecStrCat(char *dest, const char *src)
{
	char *runner = NULL;
	
	assert(NULL != dest);

	runner = dest + RecStrLen(dest);
	return (RecStrCpy(runner, src) - (runner - dest)); 
}
*/

/* NOT COMPLETE
char *RecStrStr(const char *haystack, const char *needle)
{
	assert(NULL != haystack);
	assert(NULL != needle);

	if ('\0' == *needle)
	{
	  	return (char *)haystack;
	}

	if ('\0' == *haystack)
	{
	  	return NULL;
	}
	

    if (*haystack == *needle)
    {
     	
     	RecStrStr(haystack + 1, needle + 1);
    }

   return (RecStrStr(haystack + 1, needle)) ;
}

*/
