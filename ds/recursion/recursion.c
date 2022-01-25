#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */

static void PrintRec(int);
int FibonacciIterate(int element_index);
int FibonacciRec(int element_index);
unsigned long GetFibonacci(unsigned int n);

int main(void)
{
	PrintRec(5);
	
	printf("\nRecursive: %d ",FibonacciRec(5));
	printf("\nIterative: %d ",FibonacciIterate(5));
	printf("\nIterative: %d ",FibonacciIterate(40));
	printf("\nRecursive: %d ",FibonacciRec(40));
	
	
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

unsigned long GetFibonacci(unsigned int n)
{
	int index = 2;
	int ans = 1;
	int *fibo = (int *)calloc(1+n,sizeof(size_t));
	assert (fibo != NULL);
	fibo[0] = 1;
	fibo[1] = 1;

	while(index <= n)
	{
		fibo[index] = fibo[index-1] + fibo[index-2];
		++index;
	
	}
	
	ans = fibo[n-1];

	free(fibo);
	fibo = NULL;
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