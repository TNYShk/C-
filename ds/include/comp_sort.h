#ifndef __COMP_SORT_H__
#define __COMP_SORT_H__

#include <stddef.h> /* size_t*/

/*complexity: time: O(n^2) space: O(1)*/
void BubbleSort(int *arr, size_t arr_size);

/*complexity: time: O(n^2) space: O(1)*/
void SelectionSort(int *arr, size_t arr_size);

/*complexity: time: O(n^2) space: O(1)*/
void InsertionSort(int *arr, size_t arr_size);

#endif /*__COMP_SORT_H__ */
