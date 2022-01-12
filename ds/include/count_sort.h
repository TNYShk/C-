#ifndef __COUNT_SORT_H__
#define __COUNT_SORT_H__

#include <stddef.h> /* size_t*/

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by checking each couple of sequential elements
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: None
 *complexity: time: O(n + k) space: O(n)*/
void CountingSort(int *arr, int *out, size_t arr_size, size_t max_val);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by finding the minimal value element 
 * and moving it to the start of the array
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: None
 *complexity: time: O(n^2) space: O(1)*/
void RadixSort(int *arr, size_t arr_size);



#endif /*__COUNT_SORT_H__ */
