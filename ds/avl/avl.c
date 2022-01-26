/**********************************************
 * AVL - Source File                          *
 * Developer: Tanya			                  *
 *          Jan 26, 2022                      *
 *                                            *
 * Reviewer:         	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memmove */

#include "avl.h"

typedef enum status
{
    FAILURE = -1,
    SUCCESS = 0,
    TRUES
}status_e;


enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    size_t height; 
    avl_node_t *children[NUM_OF_CHILDREN];
};


typedef struct avl
{
   avl_node *root;  
   avl_cmp_func_t cmp_func;
   
}avl_t;


avl_t *AVLCreate(avl_cmp_func_t CmpFunc)
{
    avl_t *tree = NULL;

    assert(NULL != cmp_func);

    tree = (avl_t *)calloc(NUM_OF_CHILDREN, sizeof(avl_t));
    if (NULL == tree)
    {
        return NULL;
    }

    tree->cmp_func = CmpFunc;

    return tree;
}

void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);
}

size_t AVLSize(const avl_t *tree)
{
    assert(NULL != tree);

    return (tree->root->height);
}





int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);

    return (NULL == tree->root)
}



int AVLInsert(avl_t *tree, void *n_data)
{   
    if(NULL == tree->root)
    {
        avl_node_t *new = NULL;
        new = (avl_node_t*)calloc(1,sizeof(avl_node_t));
        if(NULL == new)
        {
            return FAILURE;
        }
        if (InitNode(new,n_data))
        {
            tree->root = new;
            tree->root->height += 1;

            return SUCCESS;
        }
    }
    if (tree->CmpFunc(n_data, data))
}



static int InitNode(avl_node_t *new, void n_data)
{
   
    new->data = n_data;
   
    return TRUES;
}

