/***********************************************
 * Recursive Balanced Binary Search Tree (AVL) *
 * Developer:                                  *
 * Written: 2021-01-31                         *
 *                                             *
 * Reviewer: Nurit                             *
 **********************************************/
#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct avl avl_t;

typedef int (*avl_cmp_func_t)(const void *left, const void *right);
typedef int (*avl_action_func_t)(void *data, void *param);

typedef enum traversal_order
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    NUM_OF_ORDERS = 3
} order_t;

/* DESCRIPTION: 
 * Creates Binary Search Tree- root stub- like baby Groot
 *
 * PARAMS: 
 * cmp_func   user-provided function to compare data of nodes of tree
 * 
 * RETURN:
 * pointer to the newlty created empty tree
 *
 * Complexity: O(1) time, O(1) space. */
avl_t *AVLCreate(avl_cmp_func_t cmp_func);

/* DESCRIPTION: 
 * Destroys Binary Search Tree
 *
 * PARAMS: 
 * pointer to the tree to be destroyed
 * 
 * RETURN:
 * None
 *
 * Complexity: O(n) time, O(log n) average space. */
void AVLDestroy(avl_t *avl);

/* DESCRIPTION: 
 * Counts number of nodes in AVL Tree
 *
 * PARAMS: 
 * pointer to the tree 
 * 
 * RETURN:
 * size_t size of the tree - current amount of nodes
 *
 * Complexity: O(n) time, O(log n) average space. */
size_t AVLSize(const avl_t *avl);

/* DESCRIPTION: 
 * Checks wether the AVL is empty, root stub isnt part of tree
 *
 * PARAMS: 
 * pointer to the tree 
 * 
 * RETURN:
 * TRUE(1) if empty, otherwise Zero
 *
 * Complexity: O(1) time, O(1) space. */
int AVLIsEmpty(const avl_t *avl);

/* DESCRIPTION: 
 * Inserts data (new node) to the AVL, while keeping it balanced
 *
 * PARAMS: 
 * avl_t *tree  pointer to the tree 
 * void *data   data to be inserted
 * 
 * RETURN:
 * Status of action: zero for SUCCESS, otherwise fail
 *
 * Complexity: O(log n) average time, O(log n) average space. */
int AVLInsert(avl_t *avl, void *data);

/* DESCRIPTION: 
 * Removes data (node) from the AVL, while keeping tree balanced
 *
 * PARAMS: 
 * avl_t *tree  pointer to the tree 
 * void *data   data to be removed
 * 
 * RETURN:
 * NONE
 *
 * Complexity: O(log n) average time, O(log n) average space. */
void AVLRemove(avl_t *avl, const void *data);

/* DESCRIPTION: 
 * Counts Levels in the tree. aka Height. 
 * longest path from root node to leaf. in a balanced tree, subtrees height must be < 2
 * Height of an empty tree is 0. Leaf node height is 1
 * PARAMS: 
 * avl_t *tree  pointer to the tree 
 * 
 * 
 * RETURN:
 * size_t height of the tree.
 *
 * Complexity: O(1) time, O(1) space. */
size_t AVLHeight(const avl_t *avl);

/* DESCRIPTION: 
 * Searches given tree for desired data
 * ! NULL is not a valid data
 * 
 * PARAMS: 
 * const avl_t *tree pointer to the tree to search
 * void *data_to_find in the tree
 * 
 * RETURN:
 * data of the located node, otherwise NULL
 *
 * Complexity: O(log n) average time, O(log n) average space. */
void *AVLFind(const avl_t *avl, const void *data);

/* DESCRIPTION: 
 * perform an action on the AVL tree, in s pecific order 
 * using the provided action function and data
 *
 * ! NULL is not a valid data
 * 
 * PARAMS: 
 * avl_t *tree pointer to the AVL
 * action_func  the function to perform
 * order_t order - enum for the trabesal order of the tree (pre, in,post -order)
 * 
 * RETURN:
 * ZERO for SUCCESS, 
 *
 * Complexity: O(n) time, O(log n) average space. */
int AVLForEach(avl_t *avl, avl_action_func_t action_func, 
    void *param, order_t order);

#endif /* __AVL_H__ */
