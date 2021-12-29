#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include "dll.h"  /* dlist_iter_t */

/*go to insert */
typedef int (*cmp_func_t)(const void *left, const void *right);

typedef struct sort_list sort_list_t;
typedef struct sort_list_iter sort_list_iter_t;

struct sort_list_iter
{
    dlist_iter_t diter;            
#ifdef DEBUG
    sort_list_t *slist;
#endif
};

/*
 * DESCRIPTION: 
 * Creates a new Sorted Linked List 
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: sort function to use for the sorting of the list
 * 
 * RETURN: Pointer to the newly created sorted list, otherwise NULL
 * Complexity: O(1) time, O(1) memory. */
sort_list_t *SortListCreate(cmp_func_t sort_func);

/*
 * DESCRIPTION: 
 * Destroy Sorted Linked List 
 * 
 * free's allocated memory
 *
 * PARAMS: Pointer to the list to remove
 * 
 * RETURN: 
 * Complexity: O(n) time, O(1) memory. */
void SortListDestroy(sort_list_t *slist);

/*
 * DESCRIPTION: 
 * Counts elements of the list
 * 
 * PARAMS: Pointer to the list
 * 
 * RETURN: number of elements counted 
 * Complexity: O(n) time, O(1) memory. */
size_t SortListSize(const sort_list_t *slist);

/*
 * DESCRIPTION: 
 * Checks if the list is Empty
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: 1 if Empty, 0 if not 
 * Complexity: O(1) time, O(1) memory. */
int SortListIsEmpty(const sort_list_t *slist);

/*
 * DESCRIPTION: 
 * Inserts and sorts element to the correct location
 * based on return value of compare_func, inserts the element
 * PARAMS: Destination element, void data to insert
 * 
 * RETURN: Inserted Element, in case of FAIL, returns the last element of the dll 
 * Complexity: O(n) time, O(1) memory. */
sort_list_iter_t SortListInsert(sort_list_t *slist, void *data);

/*
 * DESCRIPTION: 
 * Remove requested element from the list
 * 
 * PARAMS: Element to remove 
 * 
 * RETURN: Element thats now in place of the removed (next in line)
 * Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListRemove(sort_list_iter_t iter);

/*
 * DESCRIPTION: 
 * Returns the Top/first element of the list
 * 
 * PARAMS: Pointer to the dll
 *  
 * RETURN: The first element of the list
 * Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListBegin(const sort_list_t *slist);

/*
 * DESCRIPTION: 
 * Returns the Tail of the list
 * Tail can't be removed and isn't part of the list (not counted). 
 * like a Sheep Herder
 * PARAMS: Pointer to the list
 * 
 * RETURN: The closing element of the list, cant be removed
 * Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListEnd(const sort_list_t *slist);

/*
 * DESCRIPTION: 
 * Returns the next element in the sorted list
 * 
 * PARAMS: iter 
 * 
 * RETURN: iter After
 * Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListNext(sort_list_iter_t iter);

/*
 * DESCRIPTION: 
 * Returns the previous element
 * undefined behavior if prev of head is request
 * PARAMS: Iterator - Element 
 * 
 * RETURN: Element before Iterator received 
 * Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListPrev(sort_list_iter_t iter);

/*
 * DESCRIPTION: 
 * Get the data from the element
 * 
 * PARAMS: Iterator - Element 
 * 
 * RETURN: the data stored in that element
 * Complexity: O(1) time, O(1) memory. */
void *SortListGetData(sort_list_iter_t iter);

/*
 * DESCRIPTION: 
 * Checks wether given iterators (elements) are equal
 * 
 * PARAMS: Iterators - Elements to compatr
 * 
 * RETURN: Boolean, 1 if they are equal, 0 otherwise
 * Complexity: O(1) time, O(1) memory. */
int SortListIterIsEqual(sort_list_iter_t iter1, sort_list_iter_t iter2);

/*
 * DESCRIPTION: 
 * Pops element from the top of the list (smallest)
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: Data stored in the element that was removed
 * Complexity: O(1) time, O(1) memory. */
void *SortListPopFront(sort_list_t *slist);

/*
 * DESCRIPTION: 
 * Pops element from the back of the list
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: Data stored in the element that was removed
 * Complexity: O(1) time, O(1) memory. */
void *SortListPopBack(sort_list_t *slist);

/*
 * DESCRIPTION: 
 * performs action on the given range of elements.
 * !list might not be sorted after this!
 * PARAMS: from - to elements to work on, the desired action and its parameter
 * 
 * RETURN: Zero for SUCCESS, -1 FAIL
 * Complexity: O(n) time, O(1) memory.
 * ifdef NDEBUG: checks that 'from' and 'to' are from the same list */
int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, 
    action_func_t action_func, void *param);

/*
 * DESCRIPTION: Merges the src sorted list into the dest list. 
 * end result dest list is also sorted
 * 
 * PARAMS: sorted lists, destination and source
 * 
 * RETURN: None
 * Complexity: O(n) time, O(1) memory. */
void SortListMerge(sort_list_t *dest, sort_list_t *src);

/*
 * DESCRIPTION: 
 * Searches for the an element (contating the desired data) in the list
 * 
 * PARAMS: sorted list to search in, range of elements, 
 * and the critera (data) to look for
 * 
 * RETURN: element that matched, otherwise NULL
 * Complexity: O(n) time, O(1) memory.*/
sort_list_iter_t SortListFind(sort_list_t *slist, sort_list_iter_t from, 
    sort_list_iter_t to, const void *data);

/*
 * DESCRIPTION: 
 * Searches the list for the given param, using the match function, 
 * provided in the struct
 * 
 * PARAMS: range of elements to search, comparison function 
 * and the critera (param) to look for
 * 
 * RETURN: element that matched, otherwise NULL
 * Complexity: O(n) time, O(1) memory. */
sort_list_iter_t SortListFindIf(sort_list_iter_t from, sort_list_iter_t to, 
    match_func_t match_func, const void *param);


#endif /* __SORTED_LIST_H__ */
