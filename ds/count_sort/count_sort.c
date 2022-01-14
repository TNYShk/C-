/**********************************************
 * count_sort - Source File                   *
 * Developer: Tanya			                  *
 *          Jan 12, 2022                      *
 *                                            *
 * Reviewer:_________	                      *
 **********************************************/
#include <stddef.h> /* size_t*/
#include <assert.h> /* assert*/
#include <stdlib.h> /* calloc*/
#include <string.h> /* memset*/
#include <stdio.h> /*print */

#include "count_sort.h"



static int FindMin(int *arr, size_t len);
static int FindMax(int *arr, size_t len);
static void CopyArrs(int *dest, int *src, size_t len);
static int PawPatrol(size_t radix);
static void EmptyBucket(int *arr, size_t len);
static void FillBucket(int *bucket, int holder);
static int MaxDigits(int max);
static void SumBucket(int *bucket, size_t len);






void CountingSort(int *arr, size_t length)
{
	size_t index = 0; 
	int i = 0;
	size_t max = 0;

	int *count_arr = NULL;
	int *output = NULL;

	assert(NULL != arr);
	assert( 0 != FindMin(arr,length));

	max = FindMax(arr, length);

	count_arr = (int *)calloc((max + 1) ,sizeof(int));
	output = (int *)calloc(length,sizeof(int));

	
	if((count_arr != NULL) && (output != NULL))
	{

		while(index < length)
		{
			++count_arr[arr[index++]];
			
		}

		for(index = 1; index < max + 1; ++index)
		{
			count_arr[index] += count_arr[index - 1];
		}
		
		for(i = length -1; i >= 0; --i)
		{
			--count_arr[arr[i]];
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
    int *temp_arr = NULL;
	int *bucket = NULL;
	int i = 0;
	int max = 0;
	
   	max = FindMax(arr, len);
	max = MaxDigits(max);
	
	while((max - (2 * chunk)) > 0)
   	{
   		++chunk;
   	}

   radix = PawPatrol(chunk);
   	
	temp_arr = (int *)calloc(len , sizeof(int));
	bucket = (int *)calloc(radix + 1, sizeof(int));
    
    
    if ((NULL != temp_arr) && (NULL != bucket))
    {
    	

    	for(i = 0; i < (int)len; ++i)
    	{

    		int holder = arr[i] % radix;
    		FillBucket(bucket, holder);
    	}

    	SumBucket(bucket, radix);
    	

    	for(i = len -1; i >= 0; --i)
    	{
    		int holder = arr[i] % radix;
    		temp_arr[bucket[holder] - 1] = arr[i];
    		--bucket[holder];
    	}
    	
    	
    	EmptyBucket(bucket, radix);
    	
    	for(i = 0; i < (int)len; ++i)
    	{
    		int holder = (temp_arr[i] / radix) % radix;
    		
    		FillBucket(bucket, holder);
    	}
    	
    	SumBucket(bucket, radix);
    	
    	for(i = len -1; i >= 0; --i)
    	{
    		int holder = (temp_arr[i] / radix) % radix;
    		
    		arr[bucket[holder] - 1] = temp_arr[i];
    		
    		--bucket[holder];
    	}
    	
    	
    	free(temp_arr);
    	temp_arr = NULL;
    	EmptyBucket(bucket, radix);
    	free(bucket);

    
    }

    
}

static void FillBucket(int *bucket, int holder)
{
	bucket[holder] += 1;
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
	int *right = arr + len -1;
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
	int counter = 0;
	assert(max > 0);

	while(max)
	{
		++counter;
		max /= 10;
	}
	return counter;
}


static void CopyArrs(int *dest, int *src, size_t len)
{
	
	assert(NULL != dest);
	assert(NULL != src);

	memcpy(dest, src, sizeof(int)* len);
	

}

static int PawPatrol(size_t radix)
{
    int base = 10;
    int ans = 1;

    assert(radix > 0);

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
