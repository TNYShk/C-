/***********************************************
 * Recursive Balanced Binary Search Tree (AVL) *
 * Developer:                                  *
 * Written: 2021-01-26                         *
 *                                             *
 * Reviewer:                                   *
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
    POST_ORDER
} order_t;

/**
enum children
{
    LEFT,
    RIGHT,
    NUM_CHILDREN
};

typedef struct avl_node avl_node_t;
struct avl_node
{
    void *data;
    size_t height; // height of a leaf is 1.
    avl_node_t *children[NUM_CHILDREN];
};

struct avl
{
    avl_node_t *root;
    avl_cmp_func_t cmp_func;
};
*/

/* Complexity: O(1) time, O(1) space. */
avl_t *AVLCreate(avl_cmp_func_t cmp_func);

/* Complexity: O(n) time, O(log n) average space. */
void AVLDestroy(avl_t *avl);

/* Complexity: O(n) time, O(log n) average space. */
size_t AVLSize(const avl_t *avl);

/* Complexity: O(1) time, O(1) space. */
int AVLIsEmpty(const avl_t *avl);

/* Complexity: O(log n) average time, O(log n) average space. */
int AVLInsert(avl_t *avl, void *data);

/* Complexity: O(log n) average time, O(log n) average space. */
void AVLRemove(avl_t *avl, const void *data);

/* Complexity: O(1) time, O(1) space. */
/* Height of an empty tree is 0. Height of a non empty tree with only one node is 1. */
size_t AVLHeight(const avl_t *avl);

/* Complexity: O(log n) average time, O(log n) average space. */
void *AVLFind(const avl_t *avl, const void *data);

/* Complexity: O(n) time, O(log n) average space. */
int AVLForEach(avl_t *avl, avl_action_func_t action_func, 
    void *param, order_t order);

#endif /* __AVL_H__ */
