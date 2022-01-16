/**********************************************
 * count_sort - Source File                   *
 * Developer: Tanya			                  *
 *          Jan 14, 2022                      *
 *                                            *
 * Reviewer: Ori    	                      *
 **********************************************/
#include <stdlib.h> /* rand()*/
#include <time.h> /*time_t */
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdio.h> /*print */

#include "linear_sort.h"

#define HUGENUM (1000000)
#define BIGNUM (6666)
#define FIVEK (5000)
#define RANGE (100)
#define NEWLINE (5)
#define TEN (10)

static void InitArr(int *arr, size_t size, int max_num);
static void PrintArr(int *arr, size_t length);
int IsSorted(int *arr, size_t length);
static void InitArrCount(int *arr, size_t size, int max_num);
void SmallScale();
void FiveKScale();
void FiveKRadix();
void RadixChunk();

int main (void)
{

   
    SmallScale();
    FiveKScale();
    FiveKRadix();
    RadixChunk();

    printf("\n\t\tPassed All Tests!\n");
   
    return 0;
}





void SmallScale()
{
    clock_t start = 0;
    clock_t end = 0;
    int arr[TEN] = {1};
    int same[5] = {1,60,1,2,1};
    int countzero[TEN] = {1,0,5,6,7,3,0,8,9,0};
    size_t length = sizeof(arr)/ sizeof(arr[0]);
    printf("\t********************Small Scale Test*******************\n");
    printf("\n\t******Counting Sort Test******\n");
    printf("\nTest small array, same elements +Zero, before\n");
    PrintArr(countzero,TEN);
    CountingSort(countzero,TEN);
    printf("post Counting Sort:\n");
    PrintArr(countzero,TEN);
    assert(1 == IsSorted(countzero,TEN));

    printf("Test2: Another Counting Sort:\n");
    InitArrCount(arr, length, RANGE);
    PrintArr(arr,length);
    
    start = clock();
    CountingSort(arr,length);
    end = clock();
    printf("post Counting Sort:\n");
    PrintArr(arr,length);
    assert(1 == IsSorted(arr,length));
    
    printf("Counting Sort 10 elements, ranged 1-99, took %ld clocks to run \n", end - start);

    printf("\n\t******Radix Sort Test******\n");
    InitArr(arr, length, BIGNUM);
    PrintArr(arr,length);
    
    start = clock();
    RadixSort(arr,length,1);
    end = clock();
    assert(1 == IsSorted(arr,length));

    printf("post Radix Sort:\n");
    PrintArr(arr,length);
    printf("Radix Sort of 10 elements, ranged 1-6666, chunks of 1, took %ld clocks to run \n", end - start);
    printf("\nTest small array, same elements, before\n");
    PrintArr(same,5);
    RadixSort(same,5,2);
    printf("post Radix Sort:\n");
    PrintArr(same,5);

}

void FiveKScale()
{
    clock_t start = 0;
    clock_t end = 0;

    int fivek[FIVEK] = {1};
   

    printf("\n\t****************5K Scale Test***************************\n");
     printf("\n\t******Count Sort Test******\n");
    InitArrCount(fivek, FIVEK, RANGE);
   
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
    InitArr(fivek, FIVEK, RANGE);
   

    start = clock();
    RadixSort(fivek, FIVEK,4);
    end = clock();
    assert(1 == IsSorted(fivek,FIVEK));
    
    printf("Radix Sort of 5K elements, ranged 1-99,chunks of 4, took %ld clocks to run \n", end - start);
    printf("\n\t******Radix 5K Test2******\n");
    InitArr(fivek, FIVEK, HUGENUM);
    
    start = clock();
    RadixSort(fivek, FIVEK,3);
    end = clock();
    assert(1 == IsSorted(fivek,FIVEK));
    printf("Radix Sort of 5K elements, ranged 1-1000000, chunks of 3 took %ld clocks to run \n", end - start);
}

void RadixChunk()
{
    clock_t start = 0;
    clock_t end = 0;

    int fivek[FIVEK] = {1};
    printf("\n\t**********************Radix Chunk Tests***********************************\n");
     printf("\n\t******Radix different chunks, 5K elements, ranged up tp %d , up to 5 chunks ******\n",HUGENUM);
    
     start = clock();
     InitArr(fivek, FIVEK, HUGENUM);
      RadixSort(fivek, FIVEK,1);
       end = clock();
       assert(1 == IsSorted(fivek,FIVEK));
    printf("Radix Sort of 5K elements, ranged 1-1000000, chunks of 1 took %ld clocks to run \n", end - start);

    start = clock();
    InitArr(fivek, FIVEK, HUGENUM);
      RadixSort(fivek, FIVEK,2);
        end = clock();
       assert(1 == IsSorted(fivek,FIVEK));
    printf("Radix Sort of 5K elements, ranged 1-1000000, chunks of 2 took %ld clocks to run \n", end - start);
    
 
     InitArr(fivek, FIVEK, HUGENUM);
      RadixSort(fivek, FIVEK,3);
       assert(1 == IsSorted(fivek,FIVEK));
       

    start = clock();
     InitArr(fivek, FIVEK, HUGENUM);
      RadixSort(fivek, FIVEK,4);
       end = clock();
       assert(1 == IsSorted(fivek,FIVEK));
        printf("Radix Sort of 5K elements, ranged 1-1000000, chunks of 4 took %ld clocks to run \n", end - start);
      

    start = clock();
     InitArr(fivek, FIVEK, HUGENUM);
      RadixSort(fivek, FIVEK,5);
      end = clock();
       assert(1 == IsSorted(fivek,FIVEK));
    printf("Radix Sort of 5K elements, ranged 1-1000000, chunks of 5 took %ld clocks to run \n", end - start);

    printf("\nPassed diff Radix sort chunks Test!\n");
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

static void InitArrCount(int *arr, size_t size, int max_num)
{
    time_t random = time(0);
    assert(NULL != arr);

    srand (time(&random));

    while(size)
    {
        arr[size -1] = rand()% max_num;
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

        if (i % NEWLINE == 0)
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

