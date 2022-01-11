#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

/************************************
*   Author: Tanya
*	Exercise: Doubley Linked List
*   Date: Dec 20, 2021
************************************/


typedef struct dlist dlist_t;
typedef struct dlist_node * dlist_iter_t;
typedef int (*match_func_t)(const void *data, void *param);
typedef int (*action_func_t)(void *data, void *param);

/*
 * DESCRIPTION: 
 * Creates a new Double Linked List ("dll")
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: Nada
 * 
 * RETURN: Pointer to the newly created dll, otherwise NULL
 * O(1) time, O(1) memory */
dlist_t *DListCreate(void);

/*
 * DESCRIPTION: 
 * Destroy Double Linked List ("dll")
 * 
 * free's allocated memory
 *
 * PARAMS: Pointer to the dll to remove
 * 
 * RETURN: 
 * O(n) time, O(1) memory */
void DListDestroy(dlist_t *dll);

/*
 * DESCRIPTION: 
 * Checks if the dll is Empty
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: 1 if Empty, 0 if not 
 * O(1) time, O(1) memory */
int DListIsEmpty(const dlist_t *dll);

/*
 * DESCRIPTION: 
 * Counts elements of the dll
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: number of elements counted 
 * O(n) time, O(1) memory */
size_t DListSize(const dlist_t *dll);

/*
 * DESCRIPTION: 
 * Inserts new element before the requested location
 * 
 * PARAMS: Destination element, void data to insert
 * 
 * RETURN: Inserted Element, in case of FAIL, returns the last element of the dll 
 * O(1) time, O(1) memory */
dlist_iter_t DListInsert(dlist_iter_t where, void *data);

/*
 * DESCRIPTION: 
 * Remove requested element from the dll
 * 
 * PARAMS: Element to remove 
 * 
 * RETURN: Element thats now in place of the removed (next in line)
 * O(1) time, O(1) memory */
dlist_iter_t DListRemove(dlist_iter_t iter);


/*
 * DESCRIPTION: 
 * Push new element at the top of the dll
 * 
 * PARAMS: Pointer to the dll, void data to insert
 * 
 * RETURN: Newly added element (Beginning)
 * O(1) time, O(1) memory */
dlist_iter_t DListPushFront(dlist_t *dll, void *data);

/*
 * DESCRIPTION: 
 * Push new element to the back of the dll
 * 
 * PARAMS: Pointer to the dll, void data to insert
 * 
 * RETURN: Newly added element (Last in line)
 * O(1) time, O(1) memory */
dlist_iter_t DListPushBack(dlist_t *dll, void *data);

/*
 * DESCRIPTION: 
 * Pops element from the top of the dll (remove)
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: Data stored in the element that was removed
 * O(1) time, O(1) memory */
void *DListPopFront(dlist_t *dll);

/*
 * DESCRIPTION: 
 * Pops element from the back of the dll (removes)
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: Data stored in the element that was removed
 * O(1) time, O(1) memory */
void *DListPopBack(dlist_t *dll);

/*
 * DESCRIPTION: 
 * Splices (cuts) the requested elements out of the list
 * 
 * PARAMS: Where - place the spliced elements, From - element to cut from, 
 * To - element to cut up to
 * 
 * RETURN: None
 * O(1) time, O(1) memory */
void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);

/*
 * DESCRIPTION: 
 * Returns the Top/first element of the dll
 * 
 * PARAMS: Pointer to the dll
 * 
 * RETURN: The first element of the list
 * O(1) time, O(1) memory */
dlist_iter_t DListBegin(const dlist_t *dll);

/*
 * DESCRIPTION: 
 * Returns the Tail of the dll
 * Tail can't be removed and isn't part of the dll (not counted). 
 * like a Sheep Herder
 * PARAMS: Pointer to the dll
 * 
 * RETURN: The closing element of the list, cant be removed
 * O(1) time, O(1) memory */
dlist_iter_t DListEnd(const dlist_t *dll);

/*
 * DESCRIPTION: 
 * Returns the next element
 * 
 * PARAMS: Iterator - Element
 * 
 * RETURN: Element After
 * O(1) time, O(1) memory */
dlist_iter_t DListNext(dlist_iter_t iter);

/*
 * DESCRIPTION: 
 * Returns the previous element
 * 
 * PARAMS: Iterator - Element 
 * 
 * RETURN: Element before Iterator received 
 * O(1) time, O(1) memory */
dlist_iter_t DListPrev(dlist_iter_t iter);

/*
 * DESCRIPTION: 
 * Get the data from the element
 * 
 * PARAMS: Iterator - Element 
 * 
 * RETURN: the data stored in that element
 * O(1) time, O(1) memory */
void *DListGetData(dlist_iter_t iter);

/*
 * DESCRIPTION: 
 * Checks wether given iterators (elements) are equal
 * 
 * PARAMS: Iterators - Elements to compatr
 * 
 * RETURN: Boolean, 1 if they are equal, 0 otherwise
 * O(1) time, O(1) memory */
int DListIsEqual(dlist_iter_t iter1, dlist_iter_t iter2);

/*
 * DESCRIPTION: 
 * Searched the given range for the desired param, with given function
 * 
 * PARAMS: Iterators - Elements range to llok for (from -to), 
 * Comparing Function, Data to look for
 * 
 * RETURN: matching Iterator, NULL if not found
 * O(n) time, O(1) memory */
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param);

/*
 * DESCRIPTION: 
 * Searched the given range for the desired param, 
 * places located elements into a new dll.
 * 
 * PARAMS: Iterators - Elements range to look for (from -to), 
 * Data to look for, Result dll to places found elements
 * 
 * RETURN: Boolean val:  0 Success, -1 Fail
 * O(n) time, O(1) memory */
int DListMultiFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param, dlist_t *result_list);

/*
 * DESCRIPTION: 
 * Performs an action on the given range of elements, using the given parameter
 * 
 * PARAMS: Iterators - Elements range for the action (from -to), 
 * Param to do, Action function that does the action with the param on the range
 * 
 * RETURN: Boolean,  0 Success, -1 Fail
 * O(n) time, O(1) memory */
int DListForEach(dlist_iter_t from, dlist_iter_t to,
	action_func_t action_func, void *param);

#endif /* __DLIST_H__ */
