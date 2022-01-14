/**********************************************
 * count_sort - Source File                   *
 * Developer: Tanya			                  *
 *          Jan 13, 2022                      *
 *                                            *
 * Reviewer: Ori    	                      *
 **********************************************/
#include <stdlib.h> /* rand()*/
#include <time.h> /*time_t */
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdio.h> /*print */

#define FIVEK (5000)
#define MAX_EL (99)
#define TEN (10)

#include "linear_sort.h"

static void InitArr(int *arr, size_t size, int max_num);
static void PrintArr(int *arr, size_t length);
int IsSorted(int *arr, size_t length);

void SmallScale();
void FiveKScale();
void FiveKRadix();

int main (void)
{
    SmallScale();
    FiveKScale();
    FiveKRadix();
   
    printf("\n\t\tPassed All Tests!\n");
    return 0;
}

void SmallScale()
{
    clock_t start = 0;
    clock_t end = 0;
    int arr[TEN] = {1};
   
    size_t length = sizeof(arr)/ sizeof(arr[0]);
    printf("\t******Small Scale Test******\n");
    printf("\n\t******Count Sort Test******\n");
    InitArr(arr, length, MAX_EL);

    PrintArr(arr,length);
    
    start = clock();
    CountingSort(arr,length);
    end = clock();
    printf("post Counting Sort:\n");
    PrintArr(arr,length);
    assert(1 == IsSorted(arr,length));
    
    printf("Counting Sort 10 elements, ranged 1-99, took %ld clocks to run \n", end - start);

    printf("\n\t******Radix Sort Test******\n");
    InitArr(arr, length, 6666);
    PrintArr(arr,length);
    assert(0 == IsSorted(arr,length));
    start = clock();
    RadixSort(arr,length,1);
    end = clock();
    assert(1 == IsSorted(arr,length));
    printf("post Radix Sort:\n");
    PrintArr(arr,length);
    printf("Radix Sort of 10 elements, ranged 1-6666, chunks of 1, took %ld clocks to run \n", end - start);
}

void FiveKScale()
{
    clock_t start = 0;
    clock_t end = 0;

    int fivek[FIVEK] = {1};
   

    printf("\n\t****************5K Scale Test***************************\n");
     printf("\n\t******Count Sort Test******\n");
    InitArr(fivek, FIVEK, MAX_EL);
   
    start = clock();
    CountingSort(fivek, FIVEK);
    end = clock();
    assert(1 == IsSorted(fivek,FIVEK));
    
    printf("Counting Sort of 5K elements, ranged 1-99, took %ld clocks to run \n", end - start);
}

void FiveKRadix()
{
    clock_t start = 0;
    clock_t end = 0;

    int fivek[FIVEK] = {1};
   

    printf("\n\t****************5K Radix Test***************************\n");
    InitArr(fivek, FIVEK, MAX_EL);
   

    start = clock();
    RadixSort(fivek, FIVEK,4);
    end = clock();
    assert(1 == IsSorted(fivek,FIVEK));
    printf("Passed assert Test!\n");
    printf("Radix Sort of 5K elements, ranged 1-99,chunks of 4, took %ld clocks to run \n", end - start);
    printf("\n\t******Radix 5K Test2******\n");
    InitArr(fivek, FIVEK, 6666);
    assert(0 == IsSorted(fivek,FIVEK));
    start = clock();
    RadixSort(fivek, FIVEK,3);
    end = clock();
    assert(1 == IsSorted(fivek,FIVEK));
    printf("Radix Sort of 5K elements, ranged 1-6666, chunks of 3 took %ld clocks to run \n", end - start);
}



static void InitArr(int *arr, size_t size, int max_num)
{
    time_t random = time(0);
    assert(NULL != arr);

    srand (time(&random));

    while(size)
    {
        arr[size -1] = 1 + rand()% max_num;
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

