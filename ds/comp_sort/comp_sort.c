/**********************************************
 * Comp_Sort - Source File                    *
 * Developer: Tanya			                  *
 *          Jan 12, 2022                      *
 *          Re-written Jan 16 post CR         *
 * Reviewer:Amit Shlomo	                      *
 **********************************************/
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdlib.h>
#include <string.h> /*memcpy */
#include "comp_sort.h" /* program header */

#define NOTTHERE (-1)

/* Service funcs */
static void PSwap(int *i , int *j);
static int FindMinIndex(int *arr, size_t len);
static void RMS(int *arr, int *helper, size_t low, size_t len);
static void Merge(int *arr, int *help, size_t low, size_t mid, size_t high);
static void RQS(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun);


void BubbleSort(int *arr, size_t arr_size)
{
	size_t i = 0;

	assert (NULL != arr);

	while(arr_size)
	{
		for(i = 1; i < arr_size ; ++i)
		{
			if (arr[i - 1] > arr[i])
			{
				PSwap(&arr[i - 1], &arr[i]);
			}
		}
	--arr_size;
	}
	
}

void SelectionSort(int *arr, size_t arr_size)
{
	int i = 0;
	int *runner = arr;
	int *end = arr + arr_size;

	assert(NULL != arr);
	

   for(i = 0; runner < end; ++runner, ++i)
   {
    	int min = FindMinIndex(runner, arr_size - i);
    	PSwap(runner, runner + min);  
	}
}


void InsertionSort(int *arr, size_t arr_size)
{
	size_t index = 1;
	size_t inner_index = 1;

	for (; index < arr_size ; ++index)
	{
		for(inner_index = index; inner_index > 0 && arr[inner_index - 1] > arr[inner_index]; --inner_index)
		{
			PSwap(&arr[inner_index - 1], &arr[inner_index]);
		}
	}
}


int BinarySearch(int *s_arr, int target, size_t length)
{
    int index = length / 2;

    while (s_arr[index] != target && (index != ((int)length)-1))
    {
        if (s_arr[index] > target)
        {
            index /= 2;
        }
        else
        {
            index = (index + length ) / 2;
        }
    }
    return ((s_arr[index] == target)? index : NOTTHERE);

}

int RecBinarySearch(int *s_arr, int target, size_t length)
{
    int index = length / 2; 

    if (s_arr[index] == target)
    {
        return index;
    }
    
    if (length == 1)
        return NOTTHERE;

    if (s_arr[index] < target)
    {
        return RecBinarySearch(s_arr + index, target, length - index);
    }
   
   return RecBinarySearch(s_arr, target, index);
    
}

void QuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun)
{
    RQS(arr, 0, size - 1, cmp_fun);
}

static void RQS(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun)
{
 if(0 < cmp_fun(&size,&nmemb))
  {
    size_t pivot = nmemb; 
    size_t i = nmemb;
    size_t j = size;
    
    while(0 < cmp_fun(&j,&i)) 
    {
      
      while(*((int *)arr + i) <= *((int *)arr + pivot) && i <= size)
        ++i;
     
      while(*((int *)arr + j)  > *((int *)arr + pivot) && j >= nmemb)
        --j;
     
      if(i < j) 
      {
        PSwap(((int *)arr + i), ((int *)arr + j));
      }
    }

    PSwap(((int *)arr + j), ((int *)arr + pivot));
   
    RQS(arr, nmemb, j-1, cmp_fun);
    RQS(arr, j+1, size, cmp_fun);
  }
}


int MergeSort(int *arr_to_sort, size_t num_elements)
{
    static int *helper = NULL;
    if(NULL == helper)
    {
        helper = (int *)malloc(num_elements * sizeof(int));
        if(NULL == helper)
            return NOTTHERE;
    }
    memcpy(helper, arr_to_sort, sizeof(*arr_to_sort) * num_elements);
   
    RMS(arr_to_sort, helper, 0, num_elements - 1);
      
    free(helper);
    return 0;
}

static void RMS(int *arr, int *helper, size_t low, size_t len)
{
    size_t mid = 0;

    if (len == low)
    {
        return;
    }

    mid = (low + ((len - low) >> 1));

    RMS(arr,helper, low, mid);
    RMS(arr, helper, mid + 1, len);

    Merge(arr, helper, low, mid, len);
}

static void Merge(int *arr, int *help, size_t low, size_t mid, size_t high)
{
    size_t right = mid + 1;
    size_t i = low;
    size_t left = i;

    while ((i <= mid) && (right <= high))
    {
        if(arr[i] <= arr[right])
        {
            help[left++] = arr[i++];
        }
        else
        {
            help[left++] = arr[right++];
        }
    }

    while(i <= mid)
    {
        help[left++] = arr[i++];
    }

    for(i = low; i <= high; ++i)
    {
        arr[i] = help[i];
    }
   
}




static void PSwap(int *i , int *j)
{
	int holder = 0;

	assert (NULL != j);
	assert (NULL != i);
	
	holder = *j;
	*j = *i;
	*i =  holder;
}

static int FindMinIndex(int *arr, size_t len)
{
	int *start = arr;
	int *end = arr + len;
	int *lowest = start;
	
	while(start < end)
	{
		if(*lowest > *start)
		{
			lowest = start;
		}
		++start;
	}
	return lowest - arr;
}



