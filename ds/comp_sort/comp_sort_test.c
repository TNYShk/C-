#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "comp_sort.h"


#define FIVEK (5000)

static void PrintArr(int *arr, size_t length);
void InitArr(int *ar, size_t len);
void InitArrOne(int *ar, size_t len);
int cmpfunc(const void * a, const void * b);



int main (void)
{

	clock_t start = 0;
	clock_t end = 0;
	int arr[] = {4,2,3,8,1,15};
	int arr2[] = {3,5,1,0,1,6};
	int arr3[] = {1,2,5,0,11,-6};
	int fifty[50] = {0};

	int fivek[FIVEK] = {1};




	printf("\n\t--------------------Arrays Before Sort--------------------\n");
	PrintArr(arr,6);
	PrintArr(arr2,6);
	PrintArr(arr3,6);
	printf("5K and 50 element arrays will not be printed here.\n They are initialized, specifially 5K is somewhat random\n");
	

	printf("\n--------------------Bubble Sort--------------------\n");
	BubbleSort(arr,6);
	PrintArr(arr,6);

	InitArr(fifty, 50);
	BubbleSort(fifty,50);
	printf("--------------------Buble Sort 50 elements --------------\n");
	PrintArr(fifty, 50);
	
	InitArrOne(fivek,FIVEK);
	start = clock();
	BubbleSort(fivek,FIVEK);
	end = clock();
	printf("5K -Bubble sort took %ld m.sec to run \n", end - start);
	/*PrintArr(fivek, FIVEK);*/

	printf("\n--------------------Selection Sort--------------------\n");
	SelectionSort(arr2,6);
	PrintArr(arr2,6);

	InitArr(fifty, 50);
	SelectionSort(fifty,50);
	printf("--------------------Selection Sort 50 elements --------------\n");
	PrintArr(fifty, 50);

	InitArrOne(fivek,FIVEK);
	start = clock();
	SelectionSort(fivek,FIVEK);
	end = clock();
	printf("5K- Selection sort took %ld m.sec to run \n", end - start);
	/*PrintArr(fivek, FIVEK);*/

	printf("\n--------------------Insertion Sort--------------------\n");
	InsertionSort(arr3,6);
	PrintArr(arr3,6);

	InitArr(fifty, 50);
	InsertionSort(fifty,50);
	printf("--------------------Insertion Sort 50 elements --------------\n");
	PrintArr(fifty, 50);

	InitArrOne(fivek,FIVEK);
	start = clock();
	InsertionSort(fivek,FIVEK);
	end = clock();
	printf("5K - Insertion sort took %ld m.sec to run \n", end - start);
	/*PrintArr(fivek, FIVEK);*/

	printf("\n\t--------------------qsort function --------------------\n");
	InitArrOne(fivek,FIVEK);
	start = clock();
	qsort(fivek,FIVEK, sizeof(int), cmpfunc);
	end = clock();
	printf("5K - qsort took %ld m.sec to run \n", end - start);
	
	return 0;
}


void InitArr(int *arr, size_t length)
{
	int i = length * 11;

	int j = 0;

	for(j = 0; j< (int)length ; ++j, --i)
	{
		arr[j] = i;
	}
	arr[15] = -7;
	arr[25] = 0;
	arr[26] = -700;
	
}

void InitArrOne(int *arr, size_t length)
{
	static int m = 5;
	int i = length * 11;

	int j = 0;

	for(j = 0; j< (int)length ; ++j, --i)
	{
		arr[j] = i * m;
	}
	arr[15] = -55;
	arr[25] = 0;
	arr[26] = -700;
	--m;
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
   return ( *(int *)a - *(int *)b );
}