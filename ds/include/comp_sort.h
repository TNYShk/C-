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

/* 
 * DESCRIPTION: 
 * Search for target int in a given array, returns the location (index) of the target.
 * 
 *
 * PARAMS:
 * Sorted array to search
 * size_t length of the array 
 * int target to search for
 * 
 * RETURN: index of the target, if not found returns negative number
 */
int BinarySearch(int *s_arr, int target, size_t length);

/* 
 * DESCRIPTION: 
 * Recursive Binary Search for target int in a given array.
 * 
 *
 * PARAMS:
 * Sorted array to search
 * size_t length of the array 
 * int target to search for
 * 
 * RETURN: the target itself if found (can be turned to index) , 
 * if not found returns negative number
 */
int *RecBinarySearch(int *s_arr, int target, size_t length);

/* 
 * DESCRIPTION: 
 * Recursive Merge Sort Algorithm, sorts the array by divide & conquere technique
 * 
 *
 * PARAMS:
 * array to sort
 * size_t num of elements
 * 
 * 
 * RETURN: Zero for SUCCESS
 */
int MergeSort(int *arr_to_sort, size_t num_elements);

/* 
 * DESCRIPTION: 
 * Recursive Quick Sort Algorithm, sorts the array by divide & conquere technique
 * 
 *
 * PARAMS:
 * array to sort
 * size_t num of elements
 * 
 * 
 * RETURN: Zero for SUCCESS
 */
void QuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp);

void IntQuickSort(void *arr, size_t nmemb, size_t size, cmp_func_t cmp_fun);

#endif /*__COMP_SORT_H__ */
