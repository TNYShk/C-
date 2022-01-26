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

#include "../include/bst.h" /* program header*/

#define ROOT(tree) (tree->root_stub.children[LEFT])
#define WHOSE_CHILD(iter) (iter == GetRight(GetParent(iter)))
#define HAS_RIGHT(node) (NULL != GetRight(node))



/**************  Service Funcs  *******************/
static int CreateIniteNode(bst_iter_t parent, bst_iter_t *new, void *data);
static int HasChild(bst_iter_t iter, int side);
static int HasParent(bst_iter_t iter);
static bst_iter_t GetLeft(bst_iter_t iter);
static bst_iter_t GetRight(bst_iter_t node);
static bst_iter_t GetParent(bst_iter_t node);
static int IsLonelyLeaf(bst_iter_t node);
static int IsFamilyNode(bst_iter_t node);
static bst_iter_t ZigZag(bst_iter_t runner, int side );
/* ********************************************** */


enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

enum status
{
    FAIL = -1,
    SUCCESS
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
  
    assert(NULL != cmp_func);

    start = (bst_t *)calloc(2,sizeof(bst_t));
    if(NULL == start)
    {
        return NULL;
    }

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
        if (IsLonelyLeaf(current))
        {
            bst_iter_t terminator = GetParent(current);

            which_child = WHOSE_CHILD(current); /*perhaps another func to nulify child */

            terminator->children[which_child] = NULL;
           
            free(current);
            current = terminator;       
        }
        else
        {
            current = current->children[HAS_RIGHT(current)];
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
    
    if (NULL == ROOT(tree))
    {
        if(SUCCESS == CreateIniteNode(&tree->root_stub, &new_n, data))
        {
            tree->root_stub.children[LEFT] = new_n;
        }

       return new_n; 
    } 
    
    while (NULL != runner)
    {
        where = tree->CmpFunc(data,runner->data);
        assert(0 != where);

        parent = runner;
        runner = runner->children[0 < where];
    }

    if(SUCCESS == CreateIniteNode(parent, &new_n, data))
    {
        parent->children[0 < where] = new_n;
    }

 return new_n;

}



bst_iter_t BSTBegin(const bst_t *tree)
{
    bst_iter_t runner = NULL;

    assert(NULL != tree);

    runner = tree->root_stub.children[LEFT];
    
    while (NULL != runner->children[LEFT])
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
    
   return ZigZag(runner,RIGHT);
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
        while(HasParent(runner) && !WHOSE_CHILD(runner))
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

    if (IsFamilyNode(node2remove))
    {
        bst_iter_t next_node = BSTNext(node2remove);
        node2remove->data = BSTGetData(next_node);
        node2remove = next_node;
    }

    which_child = WHOSE_CHILD(node2remove);
    node2remove->parent->children[HAS_RIGHT(node2remove)] = node2remove->children[WHOSE_CHILD(node2remove)];

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

    return (NULL == tree->root_stub.children[LEFT]);
}


bst_iter_t BSTFind(const bst_t *tree, void *data_to_find)
{
    bst_iter_t runner = BSTBegin(tree);

    assert(NULL != tree);
    assert(NULL != data_to_find);

    while(runner != BSTEnd(tree) && (tree->CmpFunc(runner->data,data_to_find)))
    {
        runner = BSTNext(runner);
    }

    return runner;
}


int BSTForEach(bst_iter_t from, bst_iter_t to,
    bst_action_func_t action_func, void *param)
{
    int status = SUCCESS;
   
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != param);

    while(!BSTIterIsEqual(from, to) && (SUCCESS == status))
    {
        status = action_func(BSTGetData(from), param);
        from = BSTNext(from);
    }

    return status;

}


static int CreateIniteNode(bst_iter_t parent, bst_iter_t *new_node, void *data)
{
    *new_node = (bst_node_t *)calloc(1,sizeof(bst_node_t));
    if (NULL == new_node)
    {
        return FAIL;
    }

    assert(NULL != data);
    assert(parent->data != data);

    (*new_node)->data = data;
    (*new_node)->parent = parent;
    
    return SUCCESS;
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

static int IsLonelyLeaf(bst_iter_t node)
{
    return ( (!HasChild(node,LEFT)) && (!HasChild(node,RIGHT)) );
}

static int IsFamilyNode(bst_iter_t node)
{
    return ( (HasChild(node,LEFT)) && (HasChild(node,RIGHT)) );
}

static bst_iter_t ZigZag(bst_iter_t runner, int side )
{
    if(HasChild(runner,side))
    {   
        runner = runner->children[side];
        
        while (HasChild(runner, !side))
        {
            runner = runner->children[!side];
        }
    }
    else
    {
        while( (HasParent(runner)) && (runner == GetRight(GetParent(runner)) ) )
        {
            runner = runner->parent;        
        }

        runner = runner->parent;     
    }

    return runner;  
}




