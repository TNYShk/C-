/**********************************************
 * count_sort - Source File                   *
 * Developer: Tanya			                  *
 *          Jan 12, 2022                      *
 *                                            *
 * Reviewer:_________	                      *
 **********************************************/
#include <stdlib.h> /* rand()*/
#include <time.h> /*time_t */
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdio.h> /*print */

#define FIVEK (5000)
#define MAX_EL (99)
#define TEN (10)

#include "count_sort.h"


static void InitArr(int *arr, size_t size);
static void PrintArr(int *arr, size_t length);
int IsSorted(int *arr, size_t length);
void SmallScale();
void FiveKScale();


int main (void)
{
    

    SmallScale();
   FiveKScale();
    
    return 0;
}

void SmallScale()
{
    clock_t start = 0;
    clock_t end = 0;
    int arr[TEN] = {1};
   
    size_t length = sizeof(arr)/ sizeof(arr[0]);
    printf("\t******Small Scale Test******\n");
    InitArr(arr, length);

    PrintArr(arr,length);
    
    start = clock();
    CountingSort(arr,length);
    end = clock();
    printf("post Counting Sort:\n");
    PrintArr(arr,length);
    assert(1 == IsSorted(arr,length));
    printf("Passed assert Test!\n");
    printf("Counting Sort took %ld m.sec to run \n", end - start);
    
   
}

void FiveKScale()
{
    clock_t start = 0;
    clock_t end = 0;

    int fivek[FIVEK] = {1};
   

    printf("\n\t****************5K Scale Test***************************\n");
    InitArr(fivek, FIVEK);
   

    start = clock();
    CountingSort(fivek, FIVEK);
    end = clock();
    assert(1 == IsSorted(fivek,FIVEK));
    printf("Passed assert Test!\n");
    printf("Counting Sort of 5K elements took %ld m.sec to run \n", end - start);
}



static void InitArr(int *arr, size_t size)
{
    time_t random = time(0);
    assert(NULL != arr);

    srand (time(&random));

    while(size)
    {
        arr[size -1] = 1 + rand()% MAX_EL;
        --size;
    }
}

static void PrintArr(int *arr, size_t length)
{
    size_t i = 0;
    printf("Array:\n");
    assert(NULL != arr);
    while (i < length)
    {
        printf("%d, ",arr[i]);
        ++i;

        if (i % 5 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

int IsSorted(int *arr, size_t length)
{
    size_t i = 1;
    int flag = 1;

    while(flag && (i < length))
    {
        flag = (arr[i - 1] <= arr[i]);
        ++i;
    }
    return flag;
}
