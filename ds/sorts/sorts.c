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


int main(void)
{
    int arr[] = {1,4,7,8,9,11,15,16};
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
    return 0;
}


int BinarySearch(int *s_arr, int target, size_t length)
{
    int index = length/2;

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
    
    int index = length /2; 

    if (s_arr[index] == target)
    {
        return index;
    }

    if (s_arr[index] > target)
    {
        return RecBinarySearch(s_arr, target, (length/2));
    }
    else if(s_arr[index] > target)
    {
        return RecBinarySearch(s_arr, target, ((index + length ) / 2));
    }

    return NOTTHERE;
}