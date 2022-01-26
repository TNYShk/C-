/**********************************\
* Recursive Binary Search Tree     *
* Developer:                       *
* Written: 2021-1-26               *
*                                  *
* Reviewer:                        *
\**********************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct avl avl_t;

typedef int (*avl_cmp_func_t)(const void *data1, const void *data2);
typedef int (*avl_action_func_t)(void *data, void *param);

typedef enum traversal_order
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} order_t;

/*

typdef struct avl
{
   avl_node *root  
   avl_cmp_func_t cmp_func
   
} avl_t;

enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

struct avl_node
{
    void *data;
    size_t height  
    avl_node_t *children[NUM_OF_CHILDREN];
};

*/

/* 
 * time complexity: O(1), space complexity O(1)
 */
avl_t *AVLCreate(avl_cmp_func_t cmp_func);

/* 
 * time complexity: O(n), avg space complexity O(log n)
 */
void AVLDestroy(avl_t *tree);

/* 
 * time complexity: O(n), avg space complexity O(log n)
 */
size_t AVLSize(const avl_t *tree);

/* 
 * time complexity: O(1), space complexity O(1)
 * boolean int
 */
int AVLIsEmpty(const avl_t *tree);

/* 
 * avg time complexity: O(log n), avg space complexity O(log n)
 * status int
 */
int AVLInsert(avl_t *tree, void *data);

/* 
 * avg time complexity: O(log n), avg space complexity O(log n)
 */
void AVLRemove(avl_t *tree, const void *data);

/*
 * time complexity: O(1), space complexity O(1)
 */
size_t AVLHeight(const avl_t *tree);

/* 
 * avg time complexity: O(log n), avg space complexity O(log n)
 */
void *AVLFind(const avl_t *tree, const void *data_to_find);

/* 
 * time complexity: O(n), space complexity O(1)
 */
int AVLForEach(avl_t *tree, avl_action_func_t 
                action_func, void *param, order_t order);

#endif /* __AVL_H__ */
