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
#include <math.h>
#include "linear_sort.h" /* program header*/

#define BASE (10)
#define FAIL (-1)
#define SIZE (100)
int arrtest_g[SIZE] = {0};
int resultarr_g[SIZE] = {0};
/****************** Service Funcs ****************************/
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
static void FillArray(int *arr, int where, int what);
static int AdaptRadix(int max_num, int chunk);
static int IsSorted(int *arr, size_t length);
/****************** End Service Funcs *************************/


int CountingSort(int *arr, size_t length)
{
	size_t max = 0;
	size_t index = 0; 
	int i = 0;

	int *count_arr = NULL;
	int *output = NULL;

	assert(NULL != arr);
	assert( -1 < FindMin(arr,length));

	max = FindMax(arr, length) + 1;

	count_arr = (int *)calloc(max ,sizeof(int));
	if(NULL == count_arr)
	{
		return FAIL;
	}
	
	output = (int *)calloc(length,sizeof(int));
	if (NULL == output)
	{
		free(count_arr);
		return FAIL;
	}
	
			
	for(index = 0; index < length; ++index)
	{
		FillBucket(count_arr,arr[index]);
	}

	SumBucket(count_arr, max);
			
	for(i = length -1; i >= 0; --i)
	{
		ReduceBucket(count_arr,arr[i] );
		FillArray(output, count_arr[arr[i]], arr[i]);
	}
			
	CopyArrs(arr, output, length);
		

	free(count_arr);
	count_arr = NULL;

	free(output);
	output = NULL;
	
	return (IsSorted(arr,length));
}


int RadixSort(int *arr, size_t len, int chunk)
{
    int radix = 1;
    int max = 0;
    int i = 0;

    int *temp_arr = NULL;
	int *bucket = NULL;
	
	assert(NULL != arr);
	assert(0 < len);
	assert(0 < chunk);

   	max = FindMax(arr, len);

	radix = PowerTen(AdaptRadix(max,chunk));
   	
	bucket = (int *)calloc(radix, sizeof(int));
   
    if (NULL == bucket )
    {
    	return FAIL;
    }

    temp_arr = (int *)calloc(len , sizeof(int));

    if(NULL == temp_arr)
    {
    	free(bucket);
    	return FAIL;

    }

	for(i = 0; i < (int)len; ++i)
	{
	    int holder = arr[i] % radix;
	    FillBucket(bucket, holder);
	}

	SumBucket(bucket, radix);
	    	
	for(i = len - 1; i >= 0; --i)
	{
	   	int holder = arr[i] % radix;
	    FillArray(temp_arr, bucket[holder] - 1, arr[i]);
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
	    FillArray(arr, bucket[holder] - 1, temp_arr[i]);
	    ReduceBucket(bucket,holder);
	}
	    	
	EmptyBucket(bucket, radix);
    	
	free(bucket);
    bucket = NULL;

    free(temp_arr);
    temp_arr = NULL; 

    return (IsSorted(arr,len));
}

static int ChunkedValue(int elem, int radix)
{
	return ((elem / radix) % radix);
}

static void FillArray(int *arr, int where, int what)
{
	arr[where] = what;
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



static int AdaptRadix(int max_num, int chunk)
{
	max_num = MaxDigits(max_num);

	while(0 < (max_num - (2 * chunk)))
   	{
   		++chunk;
   	}
   	return chunk;
}

static int IsSorted(int *arr, size_t length)
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


void RadixTanya(size_t len, int radix)
{
	int k = FindMax(arrtest_g, len);
	int resultarr[SIZE] = {0};
	int digits = MaxDigits(k);
	int i = 0;

	for( i= 0; i < digits; ++i)
	{
		counting_sort( i, radix);
	}
}

void counting_sort(int digit, int radix)
{
	
	int *arrC = (int *)malloc(sizeof(int) * radix);
	int idx = 0;

	for(idx = 0; idx < SIZE; ++idx)
	{
		double base = ((double)arrtest_g[idx]/radix );
		double power = ((double)digit);
		int digits_of_arr = pow(base,power);
		digits_of_arr %= radix;
		arrC[digits_of_arr] = arrC[digits_of_arr] + 1;
	}
	for(idx = 1; idx < radix ; ++idx)
	{
		arrC[idx] += arrC[idx - 1];
	}

	for(idx = SIZE - 1; idx >= 0; --idx)
	{
	    double base = ((double)arrtest_g[idx]/radix );
		double power = ((double)digit);
		int digits_of_arr = pow(base,power);
		digits_of_arr %= radix;
		arrC[digits_of_arr] = arrC[digits_of_arr] - 1;
		resultarr_g[arrC[digits_of_arr]] = arrtest_g[idx];
	}

}