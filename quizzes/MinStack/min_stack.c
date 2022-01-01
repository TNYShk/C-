#include <stdlib.h> /* memory allocation */
#include <stdio.h> /*print */
#include <assert.h> /* assert*/


#include "stack.h"



typedef struct spstack
{
	stack_t *stack;
	stack_t *min;

}spstack_t; 


static void InitStack(spstack_t *stack, int element, size_t length)
{
	
	stack->stack = StackCreate(length,sizeof(int));
	stack->min = StackCreate(length,sizeof(int));
	
	StackPush(stack->stack, &element);
	StackPush(stack->min, &element);

}
static void Destroy(spstack_t *stack)
{
	assert(NULL != stack);

	StackDestroy(stack->stack);
	StackDestroy(stack->min);
	
	free(stack);
	stack = NULL;
}

static void PushArray(spstack_t *stack, int *array, size_t length)
{
	size_t i = 0;
	void *peek = NULL;
	for(i = 1; i < length; ++i)
	{
		peek = StackPeek(stack->min);
		if(array[i] < *(int *)peek)
		{
			StackPush(stack->min, &array[i]);
		}
		else
		{
			StackPush(stack->min, peek);
		}
		StackPush(stack->stack, &array[i]);
	}

}
void *GetMin(spstack_t *stack)
{
	void *minval = NULL;
	assert(!StackIsEmpty(stack->stack));

	minval = StackPeek(stack->min);
	
	StackPop(stack->stack);
	StackPop(stack->min);

	return minval;
}


int main(void)
{

spstack_t *minis = NULL;
void *val = NULL;
int array[] = {18, 20, 17, 16, 40, 1 };
size_t length = sizeof(array)/ sizeof(array[0]);

minis = (spstack_t *)calloc(2,sizeof(spstack_t));
assert(NULL!= minis);
InitStack(minis, array[0], length);

PushArray(minis, array, length);

val = GetMin(minis);
printf("min value is %d\n", *(int *)val);
val = GetMin(minis);
printf("min value is %d\n", *(int *)val);
val = GetMin(minis);
printf("min value is %d\n", *(int *)val);
val = GetMin(minis);
printf("min value is %d\n", *(int *)val);
val = GetMin(minis);
printf("min value is %d\n", *(int *)val);
Destroy(minis);









return 0;

}