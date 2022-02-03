#ifndef __COMP_SORT_H__
#define __COMP_SORT_H__

#include <stddef.h> /* size_t*/

typedef int (*cmp_func_t)(const void *, const void *);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by checking each couple of sequential elements
 * 
 * PARAMS: 
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: None
 *complexity: time: O(n^2) space: O(1)*/
void BubbleSort(int *arr, size_t arr_size);

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
void SelectionSort(int *arr, size_t arr_size);

/*
 * DESCRIPTION: 
 * Algorithm sorts given array, by inserting the indexed element to the 'right' place in the array
 * 
 *
 * PARAMS:
 * array to sort
 * size_t length of the array 
 * 
 * RETURN: None
 *complexity: time: O(n^2) space: O(1)*/
void InsertionSort(int *arr, size_t arr_size);

int BinarySearch(int *s_arr, int target, size_t length);
int RecBinarySearch(int *s_arr, int target, size_t length);
int MergeSort(int *arr_to_sort, size_t num_elements);
void QuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp);

#endif /*__COMP_SORT_H__ */
