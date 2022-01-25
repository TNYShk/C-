#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */

long *SumIntPairsToLongs(int arr[], size_t length);


int main(void)
{
	int arr[] = {1,6,456,-3,8,12};
	long *l_arr = NULL;
	l_arr = SumIntPairsToLongs(arr,6);
	printf("%ld ",*(l_arr ));
	printf("%ld ",*(l_arr +1));
	printf("%ld ",*(l_arr +2));
	return 0;
}


long *SumIntPairsToLongs(int arr[], size_t length)
{
	long *l_ptr = (long*)arr;
	size_t idx = 0;

	for(idx = 0; idx < length; idx += 2)
	{
		long new_num = arr[idx];
		arr[idx] = new_num + arr[idx + 1];
	}
	for(idx = 1; idx < length; idx += 2)
	{
		long zero = 0;
		arr[idx] = zero;
	}
	return l_ptr;
}