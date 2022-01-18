/**********************************************
 * Binary Search Tree - Source File           *
 * Developer: Tanya			                  *
 *          Jan 18, 2022                      *
 *                                            *
 * Reviewer: NURIT  	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memmove */



#include "bst.h" /* program header*/

#define ROOT(tree) (tree->root_stub.children[LEFT])
#define CHOSEN_ONE(iter) (iter == GetRight(GetParent(iter)))
#define HAS_RIGHT(node) (NULL != GetRight(node))
#define CONTINUE (0)


/**************  Service Funcs  *******************/
static void InitNode(bst_iter_t parent, bst_iter_t *new, void *data);
static int HasChild(bst_iter_t iter, int side);
static int HasParent(bst_iter_t iter);
static bst_iter_t GetLeft(bst_iter_t iter);
static bst_iter_t GetRight(bst_iter_t node);
static bst_iter_t GetParent(bst_iter_t node);
static int LonelyLeaf(bst_iter_t node);
static int FamilyNode(bst_iter_t node);
/* ********************************************** */


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

    if(NULL == start)
    {
        return NULL;
    }

    start->root_stub.data = NULL;
    start->root_stub.parent = NULL;
    start->root_stub.children[LEFT] = NULL;
    start->root_stub.children[RIGHT] = NULL;
    start->CmpFunc = cmp_func;

    return start;
}

void BSTDestroy(bst_t *tree)
{
    bst_iter_t current = BSTBegin(tree);
    int which_child = -1;

    assert(NULL != tree);

    while (!BSTIsEmpty(tree))
    {
        if (LonelyLeaf(current))
        {
            bst_iter_t terminator = GetParent(current);

            which_child = CHOSEN_ONE(current);

            terminator->children[which_child] = NULL;
           
            free(current);
            current = terminator;
                
        }
        else if (HasChild(current,RIGHT))
        {
            current = GetRight(current);
        }
        else
        {
            current = GetLeft(current);
        }
    }
    
    free(tree);
    tree = NULL;
}


bst_iter_t BSTInsert(bst_t *tree, void *data)
{
    bst_node_t *new_n = NULL;
    bst_iter_t runner = tree->root_stub.children[LEFT];
    bst_iter_t parent = runner;
    int where = 0;

    assert(NULL != tree);
    assert(NULL != data);
    
    if (ROOT(tree) == NULL)
    {
        InitNode(&tree->root_stub, &new_n, data);
        tree->root_stub.children[LEFT] = new_n;
        
        return new_n;
    } 
    
    while (runner != NULL)
    {
        where = tree->CmpFunc(data,runner->data);
        assert(where != 0);

        parent = runner;
        runner = runner->children[0 < where];
    }

    InitNode(parent, &new_n, data);

    parent->children[0 < where] = new_n;
    
 return new_n;

}



bst_iter_t BSTBegin(const bst_t *tree)
{
    bst_iter_t runner = NULL;

    assert(NULL != tree);

    runner = tree->root_stub.children[LEFT];
    
    while (runner->children[LEFT] != NULL)
    {
        runner = GetLeft(runner);

    }

    return runner;
}


bst_iter_t BSTEnd(const bst_t *tree)
{
    assert(NULL != tree);
    
    return (bst_iter_t)&tree->root_stub;
}


bst_iter_t BSTNext(bst_iter_t iter)
{
    bst_iter_t runner = iter;
    
    assert(NULL != iter);

    if(HasChild(runner,RIGHT))
    {
        runner = GetRight(runner);

        while(HasChild(runner,LEFT))
        {
            runner = GetLeft(runner);
        }
    }
    else
    {
        while(HasParent(runner) && CHOSEN_ONE(runner))
        {
            runner = runner->parent;        
        }

        runner = runner->parent;     
    }

    return runner;
}


bst_iter_t BSTPrev(bst_iter_t iter)
{
    bst_iter_t runner = iter;

    assert(NULL != iter);

    if(HasChild(runner,LEFT))
    {
        runner = iter->children[LEFT];
        
        while(HasChild(runner,RIGHT))
        {
            runner = GetRight(runner);
        }
    }

    else
    {
        while(HasParent(runner) && !CHOSEN_ONE(runner))
        {
            runner = runner->parent;        
        }

        runner = runner->parent;     
    }

    return runner;
}




void BSTRemove(bst_iter_t node2remove)
{
    int which_child = -1;

    assert(NULL != node2remove);
    assert(NULL != BSTGetData(node2remove));

    if (FamilyNode(node2remove))
    {
        bst_iter_t next_node = BSTNext(node2remove);
        node2remove->data = BSTGetData(next_node);
        node2remove = next_node;

    }
    which_child = CHOSEN_ONE(node2remove);
    node2remove->parent->children[HAS_RIGHT(node2remove)] = node2remove->children[CHOSEN_ONE(node2remove)];

    if (NULL != node2remove->children[which_child])
    {
        node2remove->children[which_child]->parent = node2remove->parent;
    }

    memset(node2remove, 0, sizeof(bst_node_t));
    
    free(node2remove); 
    node2remove = NULL;
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
    bst_iter_t runner;

    assert(NULL != tree);

    runner = BSTBegin(tree);
    while(runner != BSTEnd(tree) )
    {
        ++counter;
        runner = BSTNext(runner);
        
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


bst_iter_t BSTFind(const bst_t *tree, void *data_to_find)
{
    bst_iter_t runner = BSTBegin(tree);

    assert(NULL != tree);
    assert(NULL != data_to_find);

    while(runner != BSTEnd(tree) && !BSTIterIsEqual(runner->data,data_to_find))
    {
        runner = BSTNext(runner);
    }
    return runner;
}



int BSTForEach(bst_iter_t from, bst_iter_t to,
    bst_action_func_t action_func, void *param)
{
    int status = CONTINUE;
   
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != param);

    while(!BSTIterIsEqual(from, to) && (CONTINUE == status))
    {
        status = action_func(BSTGetData(from), param);
        from = BSTNext(from);
    }

    return status;

}


static void InitNode(bst_iter_t parent, bst_iter_t *new_node, void *data)
{
    *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    
    if (new_node == NULL)
    {
        return;
    }
    assert(NULL != data);
    assert(parent->data != data);

    (*new_node)->data = data;
    (*new_node)->parent = parent;
    (*new_node)->children[LEFT] = NULL;
    (*new_node)->children[RIGHT] = NULL;
    
}


static bst_iter_t GetLeft(bst_iter_t iter)
{
   return iter->children[LEFT];
}

static bst_iter_t GetRight(bst_iter_t node)
{
    return node->children[RIGHT];
}

static bst_iter_t GetParent(bst_iter_t node)
{
    return node->parent;
}


static int HasChild(bst_iter_t node, int side)
{
    return (node->children[side] != NULL);
}

static int HasParent(bst_iter_t node)
{
    return (node->parent != NULL);
}

static int LonelyLeaf(bst_iter_t node)
{
    return ( (!HasChild(node,LEFT)) && (!HasChild(node,RIGHT)) );
}

static int FamilyNode(bst_iter_t node)
{
    return ( (HasChild(node,LEFT)) && (HasChild(node,RIGHT)) );
}






