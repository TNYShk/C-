#ifndef __LINEAR_SORT_H__
#define __LINEAR_SORT_H__

#include <stddef.h> /* size_t*/

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by counting instances of elements
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 *complexity: time: O(n + k) space: O(n)*/
int CountingSort(int *arr, size_t arr_size);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by counting instances of 'chunks' of numbers
 * 
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array
 * chunk - size of chunks to use when counting instances 
 * 
 * RETURN: 1 if Sorted, 0 if not sorted, FAIL (-1) if malloc failed
 *complexity: time: O(n + k) space: O(n)*/
int RadixSort(int *arr, size_t arr_size, int chunk);



#endif /*__LINEAR_SORT_H__ */
