#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int *Multiplied(int *arr, int *results, size_t length);
static void PrintArr(int *arr, size_t length);


int main(void)
{
	int arr[] = {1,2,3,4,5};

	int output[] = {0,0,0,0,0};
	Multiplied(arr, output, 5);

	PrintArr(output, 5);
	return 0;

}

int *Multiplied(int *arr, int *results, size_t length)
{
	size_t i = 0;
	int *left_dup = (int *)calloc(length, sizeof(int));
	int *right_dup = (int *)calloc(length, sizeof(int));
	
	assert(left_dup != NULL);
	assert (right_dup != NULL);

	left_dup[0] = 1;

	right_dup[length -1] = 1;

	for(i = 1; i < length ; ++i)
	{
		left_dup[i] =  left_dup[i-1] * arr[i-1]; 
		right_dup[length -i - 1] = right_dup[length -i] * arr[length - i]; 
	}

	/*PrintArr(left_dup, length);
	PrintArr(right_dup, length);
*/
	for (i = 0 ; i < length ; ++i )
	{
		results[i] = left_dup[i] * right_dup[i];
	}

	/*PrintArr(results, length);*/
	free(left_dup);
	left_dup = NULL;
	free(right_dup);
	right_dup = NULL;

	return results;

}

static void PrintArr(int *arr, size_t length)
{
	size_t i = 0;
	printf("array:\n");
	while (i < length)
	{
		printf("%d, ",arr[i]);
		++i;
	}
	printf("\n");
}


