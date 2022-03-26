/**********************************************
 * Comp_Sort - Source File                    *
 * Developer: Tanya			                  *
 * Written: 2022-1-12 + Added Rec: Feb 3      *
 * Re-written Jan 16 post CR                  *
 * Reviewer:Amit Shlomo	 Ziv                  *
 **********************************************/
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdlib.h> /* calloc, malloc, free*/
#include <string.h> /*memcpy */
#include <pthread.h> /* threads*/
#include <unistd.h> /* sleep, wait*/
#include "comp_sort.h" /* program header */

#define MIN(a,b) ((a)< (b)? (a) : (b))
#define MIN3(a,b,c) ( (MIN(a,b)) < (c) ? (MIN((a),(b))): (c) )



typedef enum status
{
	MALLOC_ERROR = -2,
	NOTTHERE = -1,
	SUCCESS = 0
}status_e;



/* Service funcs */
static void PSwap(int *i , int *j);
static int FindMinIndex(int *arr, size_t len);
static void RMS(int *arr, int *helper, size_t low, size_t len);
static void Merge(int *arr, int *help, size_t low, size_t mid, size_t high);

static void RecQS(void *arr, size_t size, int left, int right, cmp_func_t cmp_fun);
void IntQuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun);
static void RQS(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun);
static int Partition(char *arr, size_t size, int left, int right, cmp_func_t cmp_fun);
static void GenericSwap(char *left, char *right, size_t sz);
/*****************/

void HeapSort(int *arr, size_t length);
static void ConverttoMaxHeap(int *arr, size_t length);
static void HeapifyDown(int *arr, size_t idx, size_t length);


void HeapSort(int *arr, size_t length)
{
    assert(NULL != arr);
    ConverttoMaxHeap(arr,length);
    
    do
    {
        PSwap(arr, arr + (--length));
        HeapifyDown(arr,0,length);

    } while (0 < length);
}

static void ConverttoMaxHeap(int *arr, size_t length)
{
    size_t idx = length;

    while(idx)
    {
        HeapifyDown(arr, --idx,length);
    }
}
static void HeapifyDown(int *arr, size_t idx, size_t length)
{
    size_t left_child = (idx << 1) + 1;
    size_t right_child = (idx << 1) + 2;
    size_t parent = idx;

    if((left_child < length) && (arr[parent] < arr[left_child]))
    {
        parent = left_child;
    }
    if((right_child < length) && (arr[parent] < arr[right_child]))
    {
        parent = right_child;
    }
    if(idx != parent)
    {
        PSwap(arr + idx, arr + parent);
        HeapifyDown(arr, parent, length);
    }

}

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
    int *left = s_arr;
    int *right = s_arr + length -1;
    int *where = s_arr + (length >> 1);

    while((target != *where) && (left < right))
    {
        if(target > *where)
        {
            left = where + 1;
        }  
        else
        {
            right = where - 1;
        }

        where = left + (right - left)/2;
    }
   return (target == *where)? (where - s_arr): NOTTHERE;
}


int *RecBinarySearch(int *s_arr, int target, size_t length)
{
    size_t index = length >> 1;
    int *where = s_arr + index;
   
    if (*where == target)
    {
        return where;
    }

    if (0 == index)
    {
        return (s_arr - *where);
    }
    
    return (*where < target) ? RecBinarySearch(where, target, length - index): 
                                RecBinarySearch(s_arr, target, index); 
}


void QuickSort(void *arr, size_t nmemb, size_t elem_sz, cmp_func_t cmp_fun)
{
    RecQS(arr, elem_sz, 0,nmemb -1, cmp_fun );
}

static void RecQS(void *arr, size_t size, int left, int right, cmp_func_t cmp_fun)
{
    int pivot = 0;

    if (left >= right)
    {
        return;
    }

    pivot = Partition(arr,size,left,right, cmp_fun);

    RecQS(arr, size, left,      pivot - 1, cmp_fun);
    RecQS(arr, size, pivot + 1, right,   cmp_fun);
}

static int Partition(char *arr, size_t size, int left, int right, cmp_func_t cmp_fun)
{
    void  *arr_help = NULL;
    void *arr_left = NULL;
    void *arr_right = NULL;

    int i = 0;
    int last = left;
    int mid = (right + left) >> 1;

    arr_left = (arr + (left * size));
    arr_right = (arr + (mid * size));
    
    GenericSwap(arr_left, arr_right, size);

    for(i = left + 1; i <= right; ++i)
    {
        void *pivot_p = (arr + (i * size));

        if(0 < cmp_fun(arr_left,pivot_p))
        {
            ++last;
            arr_help = (arr + (last * size));
            
            GenericSwap(pivot_p, arr_help, size);
        }
    }
    arr_help = (arr + (last * size));
    
    GenericSwap(arr_left, arr_help, size);

    return last;
}



void IntQuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun)
{
    RQS(arr, 0, size - 1, cmp_fun);
}

static void RQS(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun)
{
 
 if(0 < cmp_fun(&size, &nmemb))
  {
    size_t pivot = nmemb; 
    size_t left = nmemb;
    size_t right = size;
    
    do
    {
      while(0 <= cmp_fun(((int *)arr + pivot), ((int *)arr + left)) && left <= size)
        ++left;
     
      while(0 < cmp_fun(((int *)arr + right), ((int *)arr + pivot)) && right >= nmemb)
        --right;
     
      if(left < right) 
      {
        PSwap(((int *)arr + left), ((int *)arr + right));
      }

    } while(left < right);

    PSwap(((int *)arr + right), ((int *)arr + pivot));
   
    RQS(arr, nmemb, right - 1, cmp_fun);
    RQS(arr, right + 1, size, cmp_fun);
  }
}



int MergeSort(int *arr_to_sort, size_t num_elements)
{
    int *helper = (int *)calloc(num_elements ,sizeof(int));
    if(NULL == helper)
    {
        return MALLOC_ERROR;
    }
    assert(NULL != arr_to_sort);

    memcpy(helper, arr_to_sort, sizeof(*arr_to_sort) * num_elements);
   
    RMS(arr_to_sort, helper, 0, num_elements - 1);
      
    free(helper);
    helper = NULL;

    return SUCCESS;
}

static void RMS(int *arr, int *helper, size_t low, size_t len)
{
    size_t mid = 0;

    if (len == low)
    {
        return;
    }

    mid = (low + ((len - low) >> 1));

    RMS(arr, helper, low, mid);
    RMS(arr, helper, mid + 1, len);

    Merge(arr, helper, low, mid, len);
}

static void Merge(int *arr, int *help, size_t low, size_t mid, size_t high)
{
    size_t right = mid + 1;
    size_t lefty = low;
    size_t i = lefty;
	
    while ((lefty <= mid) && (right <= high))
    {
        (arr[lefty] <= arr[right])? (help[i++] = arr[lefty++]) : 
                                (help[i++] = arr[right++]);
    }

    if(lefty <= mid)
    {
        memcpy(help + i, arr + lefty, sizeof(*arr) * (mid - lefty + 1));
    }

   memcpy(arr + low, help + low, sizeof(*help) * (high - low + 1));
}






static void GenericSwap(char *left, char *right, size_t size)
{
    while (0 < size)
    {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        ++right;
        --size;
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





