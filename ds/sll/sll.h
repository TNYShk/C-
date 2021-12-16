#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h>  /* size_t */

typedef struct slist slist_t;
typedef struct slist_node* slist_iter_t;    

typedef int (*match_func_t)(void *data, void *param);
typedef int (*action_func_t)(void *data, void *param);




/* time complexity: O(1), space complexity O(1) 

initializes the list
returns pointer to the created list or NULL if memory allocation failed.
! free memory after use !
*/
slist_t *SListCreate(void);


/* time complexity: O(n), space complexity O(1) 
frees all allocated nodes
no return value
*/
void SListDestroy(slist_t *slist);


/* time complexity: O(1), space complexity O(1) 
amortized complexity! **if malloc fails*** do need to run on the sll to find and return End which is O(n) 
inserts new node right befor the requsted node (where)
returns the node that was added, or last node of the list if failed
*/
slist_iter_t SListInsertBefore(const slist_iter_t where, void *data); 


/* time complexity: O(1), space complexity O(1) 
amortized complexity! **if malloc fails*** do need to run on the sll to find and return End which is O(n) 
inserts new node right after the where node
returns node that was inserted, or last node of the list if failed
*/
slist_iter_t SListInsertAfter(slist_iter_t where,void *data);


/* time complexity: O(1), space complexity O(1) 
removes the requested node and its data
returns the node at the same location (not the same node)
*/
slist_iter_t SListRemove(slist_iter_t iterator);


/* time complexity: O(n), space complexity O(1) 
counts amount of current nodes in the sll
returns amount of current nodes
*/
size_t SListCount(const slist_t *slist);


/* time complexity: O(1), space complexity O(1) 
	checks if sll is empty.
	return 0 is list is NOT empty;
	returns 1 if its empty
*/
int SListIsEmpty(const slist_t *slist);


/* time complexity: O(n), space complexity O(1) 
	find the node based on given parameter
	if not found, returns End node
*/
slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to, match_func_t is_match, void *param); 


/* time complexity: O(n), space complexity O(1) 
	do certein function using a given param on a set of nodes (from-to)
	return SUCCESS of FAIL
*/
int SListForEach( slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param);


/* time complexity: O(1), space complexity O(1) 
	returns Begin iterator, points to the first node in sll
*/
slist_iter_t SListBegin(const slist_t *slist);


/* time complexity: O(1), space complexity O(1) 
 return the last element in the sll
*/
slist_iter_t SListEnd(const slist_t *slist); 


/* time complexity: O(1), space complexity O(1) 
return the next node in the list, unless its the end, then returns iterator
*/
slist_iter_t SListNext(const slist_iter_t iterator);


/* time complexity: O(1), space complexity O(1) 
returns the saved data in the requested node
*/
void *SListGetData(const slist_iter_t iterator);


/* time complexity: O(1), space complexity O(1) 
set data to the node
no return value
*/
void SListSetData(slist_iter_t iterator, void *data);


/* time complexity: O(1), space complexity O(1) 
checks wether 2 nodes point to the same location
1 if true
*/
int SListIsEqual(const slist_iter_t iterator1, const slist_iter_t iterator2);


/* time complexity: O(1), space complexity O(1)
** appends src to the end of dest, while maintating src viability (stand alone),
post append, the src size is zero
*/
void SlistAppend(slist_t *dest, slist_t *src);

#endif /* __SLL_H__ */
