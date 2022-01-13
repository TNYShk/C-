/**********************************************
 * Comp_Sort - Source File                    *
 * Developer: Tanya			                  *
 *          Jan 12, 2022                      *
 *                                            *
 * Reviewer:Amit Shlomo	                      *
 **********************************************/
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdio.h>
#include "comp_sort.h"

/* Service func */
static void PSwap(int *i , int *j);
static int FindMin(int *arr, size_t len);


void BubbleSort(int *arr, size_t arr_size)
{
	size_t swapped = 0;
	size_t i = 0;

	assert (NULL != arr);

	while(swapped < arr_size)
	{
		for(i = 1; i < arr_size - swapped ; ++i)
		{
			if (arr[i - 1] > arr[i])
			{
				PSwap(&arr[i], &arr[i - 1]);
			}
		}
		++swapped;
	}
}

/*
void SelectionSort(int *arr, size_t arr_size)
{
	int i = 0;

	assert(NULL != arr);
	FindMin(arr,arr_size);

   for (i = 0; i < (int)arr_size - 1; ++i) 
   {
    	int min = i;
    	int j = i;
        
        for (j = i + 1; j < (int)arr_size; ++j) 
        {
            if (arr[j] < arr[min]) 
            {
                min = j;
            }
        }
        PSwap(&arr[i], &arr[min]);
    }
}*/

void SelectionSort(int *arr, size_t arr_size)
{
	int i = 0;
	size_t len = arr_size;
	assert(NULL != arr);

	while(i < arr_size)
	{
		int min = FindMin(arr,len);
		 PSwap(&arr[i], &arr[min]);
		 ++arr;
		 --len;
		++i;
	}
}		


void InsertionSort(int *arr, size_t arr_size)
{
	size_t index = 1;

	for (; index < arr_size ; ++index)
	{
		size_t j = index;

		while( j > 0 && arr[j - 1] > arr[j])
		{
			PSwap(&arr[j], &arr[j - 1]);
			--j;
		}
	}
}



static void PSwap(int *i , int *j)
{
	int holder = *j;

	assert (&i != &j);

	*j = *i;
	*i =  holder;
}

static int FindMin(int *arr, size_t len)
{
	int min = *arr;
	int *end = arr + len;

	while(arr != end)
	{
		if(*arr < min)
		{
			min = *arr;
		}
		++arr;
		--len;
	}
	printf("min? %d\n", min);
	return min;
}



