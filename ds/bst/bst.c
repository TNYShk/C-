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

/**************  Service Funcs  *******************/
static void InitNode(bst_iter_t parent, bst_iter_t new, void *data);
static int CompareData(const void *left, const void *right);

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
  
    start = (bst_t *)malloc(sizeof(bst_t));

    if(NULL != start)
    {
        start->root_stub.data = NULL;
        start->root_stub.parent = NULL;
        start->root_stub.children[LEFT] = NULL;
        start->root_stub.children[RIGHT] = NULL;
        start->CmpFunc = cmp_func;

        return start;
        
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

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
    bst_node_t *new_n = NULL;

    new_n = InitNode(tree->root_stub.children[LEFT], new_n, data);
    
}



bst_iter_t BSTBegin(const bst_t *tree)
{
    bst_iter_t runner = NULL;
    assert(NULL != tree);

    runner = tree->root_stub.children[LEFT];
    
    while (runner->children[LEFT] != NULL)
    {
        runner = runner->children[LEFT];

    }

    return runner;
}


bst_iter_t BSTEnd(const bst_t *tree)
{
    assert(NULL != tree);
    
    return (const bst_iter_t)&tree->root_stub;
}

bst_iter_t BSTNext(bst_iter_t iter)
{
    bst_iter_t runner = iter->parent;
    
    if (runner->children[LEFT] == iter)
        return runner;
    else
    {
        return iter->children[RIGHT];
    } 
}

/*
bst_iter_t BSTPrev(bst_iter_t iter)
{
     bst_iter_t runner = iter->parent;

     whike(runner->children[LEFT] == iter)
     {
        runner = runner->parent;
     }
}
*/

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter2);

    return iter1 == iter2;

}



size_t BSTSize(const bst_t *tree)
{
    size_t counter = 0;

    bst_iter_t runner = BSTBegin(tree);
    while(runner != BSTEnd(tree) )
    {
        runner = BSTNext(runner);
        ++counter;
    }
    return counter;
}




static void InitNode(bst_iter_t parent, bst_iter_t new_node, void *data)
{
    new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    
    assert(parent->data != data);

    if (NULL != new_node)
    {
        new_node->data = data;
        new_node->parent = parent;

        if(parent->data != NULL)
        {
            if (parent->data < new_nede->data)
            {
                parent->children[RIGHT] = new_node;
            }
            else
            {
                parent->children[LEFT] = new_node;
            } 
        }
  
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

    return (tree->root_stub.children[LEFT] == NULL);
}




static int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}

static void LeftChild(bst_iter_t node)
{
    node = node->children[LEFT];
}