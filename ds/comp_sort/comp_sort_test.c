/**********************************************
 * Comp_Sort - Source File                    *
 * Developer: Tanya			                  *
 * Written: 2022-1-12     Added R: Feb 3      *
 * Re-written Jan 16 post CR                  *
 * Reviewer:Amit Shlomo	                      *
 **********************************************/
#include <assert.h> /*assert */
#include <stdio.h> /*print */
#include <stdlib.h> /* qsort*/
#include <time.h> /* clock, time_t*/

#include "comp_sort.h" /*program header */

#define RANGE (1000)
#define FIVEK (5000)


static void PrintArr(int *arr, size_t length);
static void InitArr(int *ar, size_t len, int max_num);
void InitArrOne(int *ar, size_t len);
int cmpfunc(const void * a, const void * b);
int IsSorted(int *arr, size_t length);



int main (void)
{

	clock_t start = 0;
	clock_t end = 0;
	int arr[] = {4,2,3,8,1,15};
	int arr2[] = {3,5,1,0,1,6};
	int arr3[] = {1,2,5,0,11,-6};
	int arr4[] = {7,1,3,11,5,2,8};
	int arr5[] = {7,1,-3,11,5,29,8};
    
  
	int five_hund[500] = {1};
	int five_k[5000] = {0};
	int fifty[50] = {0};

	int fivek[FIVEK] = {1};
	printf("\n\t--------------------MergeSort--------------------\n");
	PrintArr(arr4,7);
	MergeSort(arr4, 7);
	PrintArr(arr4,7);
	/*
	printf("\n\t--------------------MergeSort 500--------------------\n");
    InitArr(five_hund,500,RANGE);
    start = clock();
	MergeSort(five_hund,500);
	end = clock();
	assert(1 == IsSorted(five_hund,500));
	printf("sorted array, MergeSort took %ld m.sec to run \n", end - start);
	*/
	printf("\n\t--------------------QuickSort--------------------\n");
	PrintArr(arr5, 7);
    QuickSort(arr5,0,7, cmpfunc);
    PrintArr(arr5, 7);
    printf("\n\t--------------------QuickSort 5K--------------------\n");
    InitArr(five_k,5000,RANGE);
    start = clock();
	QuickSort(five_k,0,5000, cmpfunc);
	end = clock();
	assert(1 == IsSorted(five_k,5000));
	printf("sorted array, QuickSort took %ld m.sec to run \n", end - start);

	printf("\n\t--------------------qsort function --------------------\n");
	InitArr(fivek,FIVEK,RANGE);
	assert(0 == IsSorted(fivek,FIVEK));
	start = clock();
	qsort(fivek,FIVEK, sizeof(int), cmpfunc);
	end = clock();
	
	assert(1 == IsSorted(fivek,FIVEK));

	printf("5K qsort tested!\n");
	printf("5K - qsort took %ld m.sec to run \n", end - start);
	

	printf("\n\t--------------------Arrays Before Sort--------------------\n");
	PrintArr(arr,6);
	PrintArr(arr2,6);
	PrintArr(arr3,6);
	printf("5K and 50 element arrays will not be printed here.\n They are initialized, specifially 5K is somewhat random\n");
	

	printf("\n--------------------Bubble Sort--------------------\n");
	BubbleSort(arr,6);

	start = clock();
	BubbleSort(arr,6);
	end = clock();
	PrintArr(arr,6);
	printf("sorted array, bublesort took %ld m.sec to run \n", end - start);

	InitArr(fifty, 50, RANGE);
	BubbleSort(fifty,50);
	/*PrintArr(fifty,50);*/
	assert(1 == IsSorted(fifty,50));
	
	printf("--------------------Buble Sort 5k elements --------------\n");
	
	
	InitArr(fivek,FIVEK, RANGE);

	start = clock();
	BubbleSort(fivek,FIVEK);
	end = clock();
	
	assert(1 == IsSorted(fivek,FIVEK));
	
	printf("5K BubbleSort tested!\n");
	printf("5K -Bubble sort took %ld m.sec to run \n", end - start);
	
printf("\n--------------------Selection Sort--------------------\n");
	SelectionSort(arr2,6);
	PrintArr(arr2,6);

	InitArr(fifty, 50, RANGE);
	SelectionSort(fifty,50);
	PrintArr(fifty, 50);
	assert(1 == IsSorted(fifty,50));
	
	/*PrintArr(fifty, 50);*/
	
	printf("--------------------Selection Sort 5k elements --------------\n");
	InitArr(fivek,FIVEK, RANGE);
	assert(0 == IsSorted(fivek,FIVEK));
	start = clock();
	SelectionSort(fivek,FIVEK);
	end = clock();
	
	assert(1 == IsSorted(fivek,FIVEK));
	
	printf("5K SelectionSort tested!\n");
	printf("5K- Selection sort took %ld m.sec to run \n", end - start);
	
	printf("\n--------------------Insertion Sort--------------------\n");
	InsertionSort(arr3,6);
	PrintArr(arr3,6);

	InitArr(fifty, 50, RANGE);
	InsertionSort(fifty,50);
	assert(1 == IsSorted(fifty,50));
	
	printf("--------------------Insertion Sort 5K elements --------------\n");
	InitArr(fivek,FIVEK, RANGE);
	start = clock();
	InsertionSort(fivek,FIVEK);
	end = clock();
	
	assert(1 == IsSorted(fivek,FIVEK));
	
	printf("5K InsertionSort tested!\n");
	printf("5K - Insertion sort took %ld m.sec to run \n", end - start);
	

	
	
	return 0;
}


static void InitArr(int *arr, size_t size, int max_num)
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

	while (i < length)
	{
		printf("%d, ",arr[i]);
		++i;

		if (i % 10 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}

int cmpfunc(const void *a, const void *b) 
{
   return ( *(size_t *)a - *(size_t *)b );
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