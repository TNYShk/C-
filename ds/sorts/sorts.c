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

#define NOTTHERE (-1)

int BinarySearch(int *s_arr, int target, size_t length);
int RecBinarySearch(int *s_arr, int target, size_t length);
int MergeSort(int *arr_to_sort, size_t num_elements);
static void Swap(int *arr);
int BubbleSort(int *arr_to_sort, size_t num_elements);
static void PrintArr(int *arr, size_t len);
static void RMS(int *arr, int *helper, size_t low, size_t len);
static void Merge(int *arr, int *help, size_t low, size_t mid, size_t high);
static void CopyArr(int *src, size_t len, int *dest);

int main(void)
{
    int arr[] = {1,4,7,8,9,11,15,16};
    int arr1[] = {7,1,3,11,5,2,8};
    int rec = 0;
    size_t leng = sizeof(arr)/sizeof(arr[0]);

    int ans = BinarySearch(arr,16, leng);
    printf("array: 1,4,7,8,9,11,15,16 \n\n");
    printf("\nIterative Binary Search\n");
    printf("index of 16 is %d\n", ans);
    ans = BinarySearch(arr,4, leng);
    printf("index of 4 is %d\n", ans);
     ans = BinarySearch(arr,11, leng);
    printf("index of 11 is %d\n", ans);
    ans = BinarySearch(arr,17, leng);
    printf("index of 17 is %d\n", ans);
 
    printf("\nRecursive Binary Search\n");
    rec = RecBinarySearch(arr, 7,leng);
    printf("index of 7 is %d\n", rec);
    rec = RecBinarySearch(arr, 4,leng);
    printf("index of 4 is %d\n", rec);
    rec = RecBinarySearch(arr, 17,leng);
    printf("index of 17 is %d\n", rec);
     rec = RecBinarySearch(arr, 9,leng);
    printf("index of 9 is %d\n", rec);
    printf("\nRecursive Merge Sort\n");
    printf("before:\n");
    PrintArr(arr1, 7);
    MergeSort(arr1, 7);
    PrintArr(arr1, 7);
    /*printf("after:\n");
    BubbleSort(arr1,8);
    */
  
  
    return 0;
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

int MergeSort(int *arr_to_sort, size_t num_elements)
{
    static int *helper = NULL;
    if(NULL == helper)
    {
        helper = (int *)malloc(num_elements * sizeof(int));
        if(NULL == helper)
            return NOTTHERE;
    }

    CopyArr(arr_to_sort, num_elements, helper);
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


static void CopyArr(int *src, size_t len, int *dest)
{
    while(len)
    {
        *dest++ = *src++;
        --len;
    }
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