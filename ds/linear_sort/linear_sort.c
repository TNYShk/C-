/**********************************************
 * count_sort - Source File                   *
 * Developer: Tanya			                  *
 *          Jan 14, 2022                      *
 *                                            *
 * Reviewer: Ori		                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc */
#include <string.h> /* memcpy */
#include <stddef.h> /* size_t*/
#include "linear_sort.h"

#define BASE (10)


/*** Servie Funcs ***/
static int FindMin(int *arr, size_t len);
static int FindMax(int *arr, size_t len);
static void CopyArrs(int *dest, int *src, size_t len);
static int PowerTen(size_t radix);
static void EmptyBucket(int *arr, size_t len);
static void FillBucket(int *bucket, int holder);
static int MaxDigits(int max);
static void SumBucket(int *bucket, size_t len);
static void ReduceBucket(int *bucket, int holder);
static int ChunkedValue(int elem, int radix);

void CountingSort(int *arr, size_t length)
{
	size_t max = 0;

	int *count_arr = NULL;
	int *output = NULL;

	assert(NULL != arr);
	assert( 0 != FindMin(arr,length));

	max = FindMax(arr, length);

	count_arr = (int *)calloc((max + 1) ,sizeof(int));
	output = (int *)calloc(length + 1,sizeof(int));

	if((count_arr != NULL) && (output != NULL))
	{
		size_t index = 0; 
		int i = 0;
		
		for(index = 0; index<length; ++index)
		{
			FillBucket(count_arr,arr[index]);
		}

		SumBucket(count_arr, max +1);
		
		for(i = length -1; i >= 0; --i)
		{
			ReduceBucket(count_arr,arr[i] );
			output[count_arr[arr[i]]] = arr[i];
		}
		
		CopyArrs(arr, output, length);
	
		free(count_arr);
		count_arr = NULL;
		free(output);
		output = NULL;
	}
}


void RadixSort(int *arr, size_t len, int chunk)
{
    int radix = 1;
    int max = 0;

    int *temp_arr = NULL;
	int *bucket = NULL;
	
	assert(NULL != arr);
	assert(0 < len);
	assert(0 < chunk);

   	max = FindMax(arr, len);
	max = MaxDigits(max);
	
	while((max - (2 * chunk)) > 0)
   	{
   		++chunk;
   	}

	radix = PowerTen(chunk);
   	
	temp_arr = (int *)calloc(len , sizeof(int));
	bucket = (int *)calloc(radix, sizeof(int));
     
    if ((NULL != temp_arr) && (NULL != bucket))
    {
    	int i = 0;

    	for(i = 0; i < (int)len; ++i)
    	{
    		int holder = arr[i] % radix;

    		FillBucket(bucket, holder);
    	}

    	SumBucket(bucket, radix);
    	
    	for(i = len - 1; i >= 0; --i)
    	{
    		int holder = arr[i] % radix;

    		temp_arr[bucket[holder] - 1] = arr[i];
    		ReduceBucket(bucket,holder);

    	}
    	
    	EmptyBucket(bucket, radix);
    	
    	for(i = 0; i < (int)len; ++i)
    	{
    		int holder = ChunkedValue(temp_arr[i], radix);
    		
    		FillBucket(bucket, holder);
    	}
    	
    	SumBucket(bucket, radix);
    	
    	for(i = len - 1; i >= 0; --i)
    	{
    		int holder = ChunkedValue(temp_arr[i], radix);
    		arr[bucket[holder] - 1] = temp_arr[i];

    		ReduceBucket(bucket,holder);
    	}
    	
    	free(temp_arr);
    	temp_arr = NULL;

    	EmptyBucket(bucket, radix);

    	free(bucket);
    	bucket = NULL;
    }
}
static int ChunkedValue(int elem, int radix)
{
	return ((elem / radix) % radix);
}

static void FillBucket(int *bucket, int holder)
{
	bucket[holder] += 1;
}

static void ReduceBucket(int *bucket, int holder)
{
	bucket[holder] -= 1;
}


static void SumBucket(int *bucket, size_t len)
{
	size_t i = 0;

	for(i = 1; i < len ; ++i)
	{
		bucket[i] += bucket[i - 1];
	}
}


static int FindMin(int *arr, size_t len)
{
	int *left = arr;
	int *end = arr + len -1;
	int min = *arr;
	
	while(left < end)
	{
		if(*left < min)
		{
			min = *left;
		}
		++left;
	}

	return min;
}

static int FindMax(int *arr, size_t len)
{
	int *left = arr;
	int *right = arr + len - 1;
	int max = *arr;

	while(left < right)
	{
		if(*left > max)
		{
			max = *left;
		}
		++left;
	}
	return max;
}

static int MaxDigits(int max)
{
	int digit_counter = 0;

	assert(0 < max);

	while(max)
	{
		++digit_counter;
		max /= BASE;
	}
	return digit_counter;
}


static void CopyArrs(int *dest, int *src, size_t len)
{
	assert(0 < len);

	memcpy(dest, src, sizeof(int)* len);
	
}

static int PowerTen(size_t radix)
{
    int base = BASE;
    int ans = 1;

    assert(0 < radix);

    while(radix)
    {
        ans *= base;
        --radix;
    }

    return ans;
}

static void EmptyBucket(int *arr, size_t len)
{
	size_t i = 0;

	assert(NULL != arr);

	for(;i < len; ++i)
	{
		arr[i] = 0;
	}
} 
