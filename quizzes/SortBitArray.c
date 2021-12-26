#include <stdio.h>
#include <stdlib.h> /* size_t, dyncamic memory allocation  */

void SortBitArray(int *array, size_t length);
void SortZeroOneArray(int *array, size_t length);
static void PrintArr(int *arr, size_t length);


int main(void)
{
	int array[] = {0,1,0,0,1,1,0,1};
	size_t length = sizeof(array)/ sizeof(array[0]);
	PrintArr(array, length);
	SortZeroOneArray(array, length);
	

	SortBitArray(array, length);
	PrintArr(array, length);
	return 0;
}

void SortBitArray(int *array, size_t length)
{
	int *left = array;
	int *right = &array[length-1];

	while (left < right)
	{
		if(*left > *right)
		{
			*left = 0;
			*right = 1;
			++left;
			--right;
		}
		else if (*left == 1)
		{
			--right;
		}
		else
		{
			++left;
		}
	}
}

static void PrintArr(int *arr, size_t length)
{
	int i = 0;

	while(length)
	{
		printf("%d ",arr[i]);
		++i;
		--length;
	}
	printf("\n");
}

void SortZeroOneArray(int *array, size_t length)
{
	int *sort_ar = (int *)calloc(length, sizeof(int));

	size_t i = 0;
	int *right = &sort_ar[length - 1];

	for(i = 0; i < length; ++i)
	{
		if(array[i] == 1)
		{
			*right = 1;
			--right;
		}
	
	}
	PrintArr(sort_ar, length);

	printf("\n");
	free(sort_ar);
	sort_ar = NULL;

}