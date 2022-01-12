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



void CountingSort(int *arr,int *output, size_t length, size_t max)
{
	size_t index = 0; 
	int i = 0;

	int *count_arr = (int *)calloc(max + 1, sizeof(int));

	assert(NULL != count_arr);
	assert(NULL != output);
	assert(NULL != arr);

	while(index < length)
	{
		++count_arr[arr[index]];
		++index;
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
	
	free(count_arr);
	count_arr = NULL;

}

