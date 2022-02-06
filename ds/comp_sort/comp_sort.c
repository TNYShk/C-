/**********************************************
 * Comp_Sort - Source File                    *
 * Developer: Tanya			                  *
 * Written: 2022-1-12 + Added Rec: Feb 3      *
 * Re-written Jan 16 post CR                  *
 * Reviewer:Amit Shlomo	                      *
 **********************************************/
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdlib.h> /* calloc, malloc, free*/
#include <string.h> /*memcpy */

#include "../include/comp_sort.h" /* program header */





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
    int index = length >> 1;

   while (s_arr[index] != target && (index != ((int)length) - 1))
    {
        (s_arr[index] > target)? (index >>= 1) : (index = (index + length ) >> 1);
        
    }
    return ((s_arr[index] == target)? index : NOTTHERE);
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
    void  *pivot = NULL, *a_left = NULL, *a_right = NULL;
    int i = 0;
    int last = left;
    int mid = (right + left) >> 1;

    a_left = (arr + (left * size));
    a_right = (arr + (mid * size));
    
    GenericSwap(a_left, a_right, size);

    for(i = left + 1; i <= right; ++i)
    {
        void *temp = (arr + (i * size));

        if(0 < cmp_fun(a_left,temp))
        {
            ++last;
            pivot = (arr + (last * size));
            
            GenericSwap(temp, pivot, size);
        }
    }
    pivot = (arr + (last * size));
    
    GenericSwap(a_left, pivot, size);

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
    size_t i = low;
    size_t left = i;
	
    while ((i <= mid) && (right <= high))
    {
        (arr[i] <= arr[right]) ? (help[left++] = arr[i++]) : (help[left++] = arr[right++]);
    }

    if(i <= mid)
    {
        memcpy(help + left, arr + i, sizeof(*arr) * (mid - i + 1));
    }

   memcpy(arr + low, help + low, sizeof(*help) * (high - low + 1));
}




static void GenericSwap(char *left, char *right, size_t size)
{
    while(0 < size)
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



