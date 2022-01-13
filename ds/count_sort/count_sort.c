/**********************************************
 * count_sort - Source File                   *
 * Developer: Tanya			                  *
 *          Jan 12, 2022                      *
 *                                            *
 * Reviewer:_________	                      *
 **********************************************/
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdlib.h> /* calloc*/


#include "count_sort.h"



static int FindMin(int *arr, size_t len);
static int FindMax(int *arr, size_t len);
static void CopyArrs(int *dest, int *src, size_t len);


void CountingSort(int *arr, size_t length)
{
	size_t index = 0; 
	int i = 0;
	size_t max = 0;

	int *count_arr = NULL;
	int *output = NULL;

	assert(NULL != arr);
	assert( 0 != FindMin(arr,length));

	max = FindMax(arr, length);

	count_arr = (int *)calloc((max + 1) ,sizeof(int));
	output = (int *)calloc(length,sizeof(int));

	if((count_arr != NULL) && (output != NULL))
	{

		while(index < length)
		{
			++count_arr[arr[index++]];
		}

		for(index = 1; index < max + 1; ++index)
		{
			count_arr[index] += count_arr[index - 1];
		}
		
		for(i = length -1; i >= 0; --i)
		{
			--count_arr[arr[i]];
			output[count_arr[arr[i]]] = arr[i];
		}
		
		CopyArrs(arr, output, length);

		free(count_arr);
		count_arr = NULL;
		free(output);
		output = NULL;
	}
}

static int FindMin(int *arr, size_t len)
{
	int *left = arr;
	int *end = arr + len -1;
	int min = *arr;
	
	while(left < end)
	{
		if(*left < min)
		{
			min = *left;
		}
		++left;
		
	}
	return min;
}

static int FindMax(int *arr, size_t len)
{
	int *left = arr;
	int *right = arr + len -1;
	int max = *arr;

	while(left < right)
	{
		if(*left > max)
		{
			max = *left;
		}
		++left;
	}
	return max;
}

static void CopyArrs(int *dest, int *src, size_t len)
{
	
	int *dest_run = NULL;
	int *src_run = NULL;

	assert(NULL != dest);
	assert(NULL != src);

	dest_run = dest;
	src_run = src;
	while(len)
	{
		*dest_run = *src_run;
		++dest_run;
		++src_run;
		--len;

	}


}
