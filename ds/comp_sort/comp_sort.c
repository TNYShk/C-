#include <stddef.h>
#include <assert.h>

#include "comp_sort.h"

/* Service func */
static void Swap(int *arr , int i, int j);


void BubbleSort(int *arr, size_t arr_size)
{
	size_t swapped = 0;
	size_t i = 0;
	assert (NULL != arr);

	while(swapped < arr_size)
	{
		for(i = 1; i < arr_size ; ++i)
		{
			if (arr[i-1] > arr[i])
			{
				Swap(arr, i, i - 1);
			}
		}

		++swapped;
		i = 1;
	}
}


void SelectionSort(int *arr, size_t arr_size)
{
	int i = 0;

	assert(NULL != arr);

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

        if (i != min) 
        {
        	Swap(arr ,i ,min);
        }
    }
}	


void InsertionSort(int *arr, size_t arr_size)
{
	size_t i = 0;

	for (i = 1; i < arr_size ; ++i)
	{
		size_t j = i;

		while( j > 0 && arr[j - 1] > arr[j])
		{
			Swap(arr, j, j - 1);
			--j;
		}
	}
}


static void Swap(int *arr , int i , int j)
{
	int holder = arr[j];
	arr[j] = arr[i];
	arr[i] =  holder;
}





