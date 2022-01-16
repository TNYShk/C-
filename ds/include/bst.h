#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node* bst_iter_t;

typedef int (*bst_cmp_func_t)(const void *data1, const void *data2);
typedef int (*bst_action_func_t)(void *data, void *param);

/*
In C file: 

enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct bst_node bst_node_t;

struct bst_node
{
    void *data;
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
};

struct bst
{
    bst_node_t root_stub;
    bst_cmp_func_t *CmpFunc;
};

*/

/*
 *  Complexity: O(1) time, O(1) space.
 */
bst_t *BSTCreate(bst_cmp_func_t cmp_func);

/*
 *  Complexity: O(n) time, O(1) space.
 */
void BSTDestroy(bst_t *tree);

/*
 *  Complexity: O(n) time, O(1) space.
 */
size_t BSTSize(const bst_t *tree);

/*
 *  Complexity: O(1) time, O(1) space.
 */
int BSTIsEmpty(const bst_t *tree);

/*
 *  Complexity: O(log n) average time. O(1) space.
 */
bst_iter_t BSTInsert(bst_t *tree, void *data);

/*
 *  Complexity: O(log n) average time. O(1) space.
 */
void BSTRemove(bst_iter_t iter);

/*
 *  Complexity: O(log n) average time, O(n) worst case. O(1) space.
 */
bst_iter_t BSTBegin(const bst_t *tree);

/*
 *  Complexity: O(1) average time, O(n) worst case. O(1) space.
 */
bst_iter_t BSTEnd(const bst_t *tree);

/*
 *  Complexity: O(log n) time, O(1) space.
 */
bst_iter_t BSTPrev(bst_iter_t iter);

/*
 *  Complexity: O(log n) time, O(1) space.
 */
bst_iter_t BSTNext(bst_iter_t iter);

/*
 *  Complexity: O(1) time, O(1) space.
 */
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);

/*
 *  Complexity: O(1) time, O(1) space.
 */
void *BSTGetData(bst_iter_t iter);

/*
 *  Complexity: O(log n) time, O(1) space.
 */
bst_iter_t BSTFind(const bst_t *tree, void *data_to_find);

/*
 *  Complexity: O(n) time, O(1) space.
 */
int BSTForEach(bst_iter_t from, bst_iter_t to,
	bst_action_func_t action_func, void *param);

#endif /* __BST_H__ */