#include <stdlib.h>
#include <stdio.h>
#include <string.h>




static ParLut[255] = {0};

typedef struct stack
{
	void *top;
	size_t capacity; 
	size_t elem_size;
	void *base;

}stack_t; 

stack_t *StackCreate(size_t num_of_elements, size_t element_size);
int CheckParent(char *);
void StackPush(stack_t *, const void *);
void StackPop(stack_t *);
void *StackPeek(const stack_t *sptr);
void StackDestroy(stack_t *sptr);
int StackIsEmpty(const stack_t *sptr);


stack_t *StackCreate(size_t num_of_elements, size_t element_size)
{
	stack_t *sptr = NULL;
	sptr = (stack_t *)malloc(sizeof(stack_t));
	
	sptr->base = malloc(num_of_elements * element_size);

	if ((NULL != sptr) && (NULL != sptr->base))
	{ 

		sptr->capacity = num_of_elements;
		sptr->elem_size = element_size;
	
		sptr->top = sptr->base;
	}

	return sptr;


}


void StackPush(stack_t *sptr, const void *element)
{
	memcpy(sptr->top, element, (sptr->elem_size));

	sptr->top = ((char *)sptr->top + sptr->elem_size);
}

void *StackPeek(const stack_t *sptr)
{
	return ((char *)sptr->top - sptr->elem_size);
}

void StackPop(stack_t *sptr)
{
	
	sptr->top = ((char *)sptr->top - sptr->elem_size);
}

int StackIsEmpty(const stack_t *sptr)
{
	return (sptr->top == sptr->base);
}

int CheckParent(char *str2check)
{
	stack_t *par_t = NULL;
	size_t index = 0;
	size_t length = strlen(str2check);
	
	par_t = StackCreate(length, sizeof(char));

	while('\0' != *str2check)
	{
		if(( *str2check == '{') || (*str2check == '(') || (*str2check == '['))
		{
			StackPush(par_t, str2check);
			ParLut[*str2check] += 1; /* not sure how to use it yet*/
		}

		else
		{
			char *temp = StackPeek(par_t);
			size_t bb = *str2check - *temp; /*ASCII TABLE closing minus opening parenths are up to 2 */
			if (bb <= 2)
			{
				StackPop(par_t);	
			}
			else
			{
			StackDestroy(par_t);	
			return 12;	
			}
			
		}
		
		++str2check;
	}
	index = StackIsEmpty(par_t);
	StackDestroy(par_t);
	return index;

}

void StackDestroy(stack_t *sptr)
{
	free(sptr->base);
	sptr->base = NULL;
	free(sptr);
	sptr = NULL;
}


int main()
{
	char str[] = "[()](){[()]()}";
	char st[] = "[{}(])";
	printf("1 is ok, 12 is not\n");
	printf("str is %d\n",CheckParent(str));
	printf("st is %d\n",CheckParent(st));
	return 0;
} 