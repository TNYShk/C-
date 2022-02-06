/**********************************************
 * Sorts - Source File                        *
 * Developer: Tanya			                  *
 *          Feb 03, 2022                      *
 *                                            *
 * Reviewer:        	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* memset */
#include <stdio.h>


typedef enum status
{
    MALLOC_ERROR = -2,
    NOTTHERE = -9,
    SUCCESS = 0
}status_e;



typedef int (*cmp_func_t)(const void *, const void *);


int BinarySearch(int *s_arr, int target, size_t length);
int *RecBinarySearch(int *s_arr, int target, size_t length);
int MergeSort(int *arr_to_sort, size_t num_elements);
static void Swap(int *arr);
int BubbleSort(int *arr_to_sort, size_t num_elements);
static void PrintArr(int *arr, size_t len);
static void RMS(int *arr, int *helper, size_t low, size_t len);
static void Merge(int *arr, int *help, size_t low, size_t mid, size_t high);

static void PSwap(int *i , int *j);
void QuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun);
static void RQS(void *arr, size_t low, size_t high, cmp_func_t cmp_fun);
int cmpfunc(const void *a, const void *b);



int main(void)
{
    int arr[] = {1,4,7,8,9,11,15,16};
    int arr1[] = {7,1,3,11,5,2,8};
    int arr2[] = {7,-5,2,5,12};
    int *rec = NULL;
    int ans = 0;
    size_t leng = sizeof(arr)/sizeof(arr[0]);
    PrintArr(arr2, 5);
    QuickSort(arr2,0,5, cmpfunc);
    PrintArr(arr2, 5);

     
    ans = BinarySearch(arr,16, leng);
    printf("array: 1,4,7,8,9,11,15,16 \n\n");
    printf("\nIterative Binary Search\n");
    printf("index of 16 is %d\n", ans);
    ans = BinarySearch(arr,4, leng);
    printf("index of 4 is %d\n", ans);
     ans = BinarySearch(arr,11, leng);
    printf("index of 11 is %d\n", ans);
    ans = BinarySearch(arr,17, leng);
    printf("index of 17 is %d\n", ans);
     ans = BinarySearch(arr,9, leng);
    printf("index of 9 is %d\n", ans);
    
    printf("\nRecursive Binary Search\n");
    rec = RecBinarySearch(arr, 7,leng);
    printf("index of 7 is %ld\n", rec - arr);
    rec = RecBinarySearch(arr, 4,leng);
    printf("index of 4 is %ld\n", rec - arr);
    rec = RecBinarySearch(arr, 18,leng);
    printf("index of 18 is %ld\n", rec - arr);
     rec = RecBinarySearch(arr, 9,leng);
    printf("index of 9 is %ld\n", rec - arr);
    rec = RecBinarySearch(arr, 16,leng);
    printf("index of 16 is %ld\n", rec - arr);
   
    printf("\nRecursive Merge Sort\n");
    printf("before:\n");
    
    PrintArr(arr1, 7);
    MergeSort(arr1, 7);
    
    PrintArr(arr1, 7);
   
    
  
  
    return 0;
}

void QuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun)
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
    
    while(left < right)
    {
      /*while(*((int *)arr + left) <= *((int *)arr + pivot) && left <= size) */
      while(0 <= cmp_fun(((int *)arr + pivot), ((int *)arr + left)) && left <= size)
        ++left;
     /* while(*((int *)arr + right)  > *((int *)arr + pivot) && right >= nmemb) */
      while(0 < cmp_fun(((int *)arr + right), ((int *)arr + pivot)) && right >= nmemb)
        --right;
     
      if(left < right) 
      {
        PSwap(((int *)arr + left), ((int *)arr + right));
      }
    } 

    PSwap(((int *)arr + right), ((int *)arr + pivot));
   
    RQS(arr, nmemb, right - 1, cmp_fun);
    RQS(arr, right + 1, size, cmp_fun);
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


int BinarySearch(int *s_arr, int target, size_t length)
{
    int index = length / 2;

    while (s_arr[index] != target && (index != ((int)length) - 1))
    {
        (s_arr[index] > target)? (index /= 2) : (index = (index + length ) / 2);
        
    }
    return ((s_arr[index] == target)? index : NOTTHERE);

}





int *RecBinarySearch(int *s_arr, int target, size_t length)
{
    size_t index = length / 2;
    int *where = s_arr + index;
   
    if (*where == target)
    {
        return where;
    }

    if (index == 0)
    {
        return (s_arr - *where);
    }
    
    return (*where < target) ? RecBinarySearch(where, target, length - index): 
                                RecBinarySearch(s_arr, target, index); 
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
    int *helper = (int *)malloc(num_elements * sizeof(int));
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
        
        (arr[i] <= arr[right]) ? (help[left++] = arr[i++]) : (help[left++] = arr[right++]);
       
    }

    if(i <= mid)
    {
        memcpy(help + left, arr + i, sizeof(*arr) * (mid - i + 1));
    }

    memcpy(arr + low, help + low, sizeof(*help) * (high - low + 1));
     
   
}








/* works only for even num_elements*/
int BubbleSort(int *arr_to_sort, size_t num_elements)
{
    if (num_elements == 1)
    {
        Swap(++arr_to_sort);
        return 0;
    }
    
    Swap(arr_to_sort);
    
    BubbleSort(++arr_to_sort, (num_elements -1));
    return BubbleSort(arr_to_sort, (num_elements / 2));
}




static void Swap(int *arr)
{
    if(arr[0] > arr[1])
    {
        int temp = arr[1];
        arr[1] = arr[0];
        arr[0] = temp;
    }
}

static void PrintArr(int *arr, size_t len)
{
    size_t i = 0;

    for(i = 0; i < len; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int cmpfunc(const void *a, const void *b) 
{
   return ( *(size_t *)a - *(size_t *)b );
}