#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node* bst_iter_t;

typedef int (*bst_cmp_func_t)(const void *data1, const void *data2);
typedef int (*bst_action_func_t)(void *data, void *param);


/* DESCRIPTION: 
 * Creates Binary Search Tree- root stub- like baby Groot
 *
 * PARAMS: 
 * cmp_func   user-provided function to compare data of nodes of tree
 * 
 * RETURN:
 * pointer to the newlty created empty tree
 *
 * Complexity: O(1) time, O(1) space.
 */
bst_t *BSTCreate(bst_cmp_func_t cmp_func);

/* DESCRIPTION: 
 * Destroys Binary Search Tree
 *
 * PARAMS: 
 * pointer to the tree to be destroyed
 * 
 * RETURN:
 * None
 *
 *  Complexity: O(n) time, O(1) space.
 */
void BSTDestroy(bst_t *tree);

/* DESCRIPTION: 
 * Counts number of nodes in BST
 *
 * PARAMS: 
 * pointer to the tree 
 * 
 * RETURN:
 * size_t size of the tree - current amount of nodes
 *
 *  Complexity: O(n) time, O(1) space.
 */
size_t BSTSize(const bst_t *tree);

/* DESCRIPTION: 
 * Checks wether the BST is empty, root stub isnt part of tree
 *
 * PARAMS: 
 * pointer to the tree 
 * 
 * RETURN:
 * TRUE(1) if empty, otherwise Zero
 *
 *  Complexity: O(1) time, O(1) space.
 */
int BSTIsEmpty(const bst_t *tree);

/* DESCRIPTION: 
 * Inserts data (new node) to the BST, BST is sorted
 *
 * PARAMS: 
 * bst_t *tree  pointer to the tree 
 * void *data   data to be inserted
 * 
 * RETURN:
 * iterator - the new node
 *
 *  Complexity: O(log n) average time. O(1) space.
 */
bst_iter_t BSTInsert(bst_t *tree, void *data);

/* DESCRIPTION: 
 * removes data (node) from the BST, the Next node replaces position in tree
 *
 * PARAMS: 
 * iterator - the node to remove
 * 
 * RETURN:
 * NONE
 *
 *  Complexity: O(log n) average time. O(1) space.
 */
void BSTRemove(bst_iter_t iter);

/* DESCRIPTION: 
 * Returns the first node of the tree (in order), thus the leftmost node, smallest data node
 *
 * PARAMS: 
 * bst_t *tree  pointer to the tree 
 * 
 * RETURN:
 * iterator - to the leftmost node
 *
 *  Complexity: O(log n) average time, O(n) worst case. O(1) space.
 */
bst_iter_t BSTBegin(const bst_t *tree);

/* DESCRIPTION: 
 * Returns the root stub, the upmost iterator- the grandparent
 *
 * PARAMS: 
 * bst_t *tree  pointer to the tree 
 * 
 * RETURN:
 * iterator - to the grandparent 
 *
 *  Complexity: O(1) average time, O(n) worst case. O(1) space.
 */
bst_iter_t BSTEnd(const bst_t *tree);

/* DESCRIPTION: 
 * Returns the node previous to the provided iter
 *
 * PARAMS: 
 * bst_iter_t iter  iterator of node to return its previous
 * 
 * RETURN:
 * iterator - the previous node
 *
 *  Complexity: O(log n) time, O(1) space.
 */
bst_iter_t BSTPrev(bst_iter_t iter);

/* DESCRIPTION: 
 * Returns the node next to the provided iter
 *
 * PARAMS: 
 * bst_iter_t iter  iterator of node to return its next
 * 
 * RETURN:
 * iterator - the next node
 *
 *  Complexity: O(log n) time, O(1) space.
 */
bst_iter_t BSTNext(bst_iter_t iter);

/* DESCRIPTION: 
 * Checks wether two given iterator nods are equal
 *
 * PARAMS: 
 * bst_iter_t iter, iter2  iterators to compare
 * 
 * RETURN:
 * TRUE 1, otherwise Zero
 *
 *  Complexity: O(1) time, O(1) space.
 */
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);

/* DESCRIPTION: 
 * returns the data of the given node
 * ! NULL is not a valid data
 * 
 * PARAMS: 
 * bst_iter_t iter iterator node
 * 
 * RETURN:
 * void *data stored in that node
 *
 *  Complexity: O(1) time, O(1) space.
 */
void *BSTGetData(bst_iter_t iter);

/* DESCRIPTION: 
 * Searches given tree for desired data
 * ! NULL is not a valid data
 * 
 * PARAMS: 
 * const bst_t *tree pointer to the tree to search
 * void *data_to_find in the tree
 * 
 * RETURN:
 * iterator to the found data, if not fount BSTEnd is returned (which is NULL)
 *
 *  Complexity: O(log n) amortized time, O(1) space. O(n) if the tree is not balanced
 */
bst_iter_t BSTFind(const bst_t *tree, void *data_to_find);

/* DESCRIPTION: 
 * perform an action for the provided range of nodes (from-to), 
 * using the provided action function and data
 *
 * ! NULL is not a valid data
 * 
 * PARAMS: 
 * iterators from, to -  first and last to perform the action
 * action_func  the function to perform
 * void *data to perform
 * 
 * RETURN:
 * ZERO for SUCCESS, 
 *
 *  Complexity: O(n) time, O(1) space.
 */
int BSTForEach(bst_iter_t from, bst_iter_t to,
	bst_action_func_t action_func, void *param);

#endif /* __BST_H__ */
