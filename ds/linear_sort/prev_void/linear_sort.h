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
 * RETURN: None
 *complexity: time: O(n + k) space: O(n)*/
void CountingSort(int *arr, size_t arr_size);

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
 * RETURN: None
 *complexity: time: O(n + k) space: O(n)*/
void RadixSort(int *arr, size_t arr_size, int chunk);



#endif /*__LINEAR_SORT_H__ */
