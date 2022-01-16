/**********************************************
 * Binary Search Tree - Source File           *
 * Developer: Tanya			                  *
 *          Jan 16, 2022                      *
 *                                            *
 * Reviewer:    		                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc */
#include <string.h> /* memcpy */
#include <stddef.h> /* size_t*/
#include "bst.h" /* program header*/

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
    bst_cmp_func_t CmpFunc;
};


bst_t *BSTCreate(bst_cmp_func_t cmp_func)
{
    bst_t *start = NULL;
    bst_node_t *dummy_root = NULL;

    start = (bst_t *)malloc(sizeof(bst_t));

    if(NULL != start)
    {
        dummy_root = (bst_node_t *)malloc(sizeof(bst_node_t));
        
        if(NULL != dummy_root)
        {

            start->root_stub = dummy_root;
            start->CmpFunc = &cmp_func;

            dummy_root->data = NULL;
            dummy_root->parent = NULL;

            return start;
        }

    free(start);
    start = NULL;

    }

    return NULL;
}


void BSTDestroy(bst_t *tree)
{
    assert(NULL != tree);

    while (!BSTIsEmpty(tree))
    {

    }
    free(tree);
    tree = NULL;
}

bst_iter_t BSTBegin(const bst_t *tree)
{
    bst_iter_t runner = NULL;
    assert(NULL != tree);

    runner = tree->root_stub->children[LEFT];
    
    while (runner != NULL)
    {
        runner = runner->children[LEFT];

    }

    return runner;
}

static void InitNode(bst_node_t parent, bst_node_t new, void *data)
{
    new = (bst_node_t *)malloc(sizeof(bst_node_t));
   
    if (NULL != new)
    {
        new->data = data;
        new->parent = parent;
    }
}

void *BSTGetData(bst_iter_t iter)
{
    assert(NULL != iter);

    return iter->data;
}

int BSTIsEmpty(const bst_t *tree)
{
    assert(NULL != tree);

    return (tree->root_stub == NULL);
}