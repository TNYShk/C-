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
static int HasChild(bst_iter_t iter, int side);
static int HasParent(bst_iter_t iter);
static bst_node_t *GetLeft(bst_iter_t iter);
static bst_node_t *GetRight(bst_node_t *node);
static bst_node_t *GetParent(bst_node_t *node);
static bst_node_t *GetRoot(bst_node_t *node);

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
    bst_node_t *runner_next;
    bst_node_t *runner_left;
    
    assert(NULL != tree);
    runner_left = BSTBegin(tree);
    runner_next = GetParent(runner_left);
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
    bst_iter_t runner = iter;
    
    if(GetRight(runner) != NULL)
    {
        runner = iter->children[RIGHT];

        while(GetLeft(runner) != NULL)
        {
            runner = runner->children[LEFT];
        }

        return runner;
    }

    runner = iter->parent;
    if(runner.children[LEFT] != iter)
    {
        runner = runner->parent;
        while(GetParent(runner).children[LEFT] != runner)
        {
            runner = runner->parent;
        }
    }
    return runner;
    
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
    bst_iter_t runner = iter;

    if(HasChild(runner,LEFT))
    {
        runner = iter->children[LEFT];
        
            while(HasChild(runner,RIGHT))
            {
                runner = runner->children[RIGHT];
            }
            
        return runner;
    }

    /*runner = iter->parent;*/

    if(runner.children[RIGHT] != iter)
    {
        runner = runner->parent;
        while(GetParent(runner).children[RIGHT] != runner)
        {
            runner = runner->parent
        }

    }
    return runner;
}


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

static void InitNode(bst_iter_t parent, bst_iter_t new_node, void *data)
{
    new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    
    assert(parent->data != data);

    if (NULL != new_node)
    {
        new_node->data = data;
        new_node->parent = parent;

        new_node->children[LEFT] = NULL;
        new_node->children[RIGHT] = NULL;
    }
}


static int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}

static bst_node_t *GetLeft(bst_iter_t iter)
{
   return node->children[LEFT];
}

static bst_node_t *GetRight(bst_node_t *node)
{
    return node->children[RIGHT];
}

static bst_node_t *GetParent(bst_node_t *node)
{
    return node->parent;
}

static bst_node_t *GetRoot(bst_node_t *node)
{
    bst_node_t *runner = node;
    while (runner->parent != NULL)
    {
        runner = GetParent(runner);
    }
    return runner;
}

static bst_iter_t ZigZag(bst_iter_t itter)
{
    bst_iter_t runner = iter;
    
    if(GetRight(runner) != NULL)
    {
        runner = iter->children[RIGHT];

        while(GetLeft(runner) != NULL)
        {
            runner = runner->children[LEFT];
        }

        return runner;

}

static int HasChild(bst_iter_t node, int side)
{
    return (node->children[side] != NULL);
}