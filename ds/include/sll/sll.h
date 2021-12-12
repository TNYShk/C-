#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h>  /* size_t */

typedef struct slist slist_t;
typedef struct slist_node* slist_iter_t;    /* current pointer*/

typedef int (*match_func_t)(const void *data, void *param);
typedef int (*action_func_t)(void *data, void *param);


/* time complexity: O(1), space complexity O(1) */
slist_t *SListCreate(void);

/* time complexity: O(n), space complexity O(1) */
void SListDestroy(slist_t *slist);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListInsertBefore(const slist_iter_t where, const void *data); 

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListInsertAfter(slist_iter_t where,const void *data);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListRemove(slist_iter_t iterator);

/* time complexity: O(n), space complexity O(1) */
size_t SListCount(const slist_t *slist);

/* time complexity: O(1), space complexity O(1) */
int SListIsEmpty(const slist_t *slist);

/* time complexity: O(n), space complexity O(1) */
slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to, match_func_t is_match, void *param); 

/* time complexity: O(n), space complexity O(1) */
int SListForEach(const slist_iter_t from, const slist_iter_t to, action_func_t action_func, void *param);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListBegin(const slist_t *slist);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListEnd(const slist_t *slist); 
/* we want the list to work with exactly one dummy for something. after we will read about dummies we will know what for*/

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListNext(const slist_iter_t iterator);

/* time complexity: O(1), space complexity O(1) */
void *SListGetData(const slist_iter_t iterator);

/* time complexity: O(1), space complexity O(1) */
void SListSetData(slist_iter_t iterator, const void *data);

/* time complexity: O(1), space complexity O(1) */
int SListIsEqual(const slist_iter_t iterator1, const slist_iter_t iterator2);

#endif /* __SLL_H__ */
