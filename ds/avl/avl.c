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
#include <stdio.h>

#include "avl.h"

#define MAX(a,b) ((a > b)? (a) : (b))


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


struct avl
{
    avl_node_t *root;
    avl_cmp_func_t cmp_func;
};


static void Destroy(avl_node_t *runner);
static size_t CountNodes(avl_node_t *runner);

static avl_node_t *CreateNode(void *data);
static int InsertNode(avl_node_t *new, void *n_data, avl_cmp_func_t CmpFunc);
static int GetChildHeight(avl_node_t *node, int child);
static avl_node_t *RecFindNode(avl_node_t *runner, const void *data, avl_cmp_func_t CmpFunc);
static void *RecFind(avl_node_t *runner, const void *data, avl_cmp_func_t CmpFunc);


avl_t *AVLCreate(avl_cmp_func_t CmpFunc)
{
    avl_t *tree = NULL;

    assert(NULL != CmpFunc);

    tree = (avl_t *)calloc(1,sizeof(avl_t));
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
    
    if (tree->root != NULL)
    {
        avl_node_t *runner = tree->root;
        Destroy(runner);
    }

    free(tree);
    
}

static void Destroy(avl_node_t *runner)
{
    if (runner == NULL)
    {
        return;
    }
    
    Destroy(runner->children[RIGHT]);
    Destroy(runner->children[LEFT]);
    
    printf("deleted node with data %d\n", *(int *)runner->data);
    

    free(runner);
}

static size_t CountNodes(avl_node_t *runner)
{
    if (runner == NULL)
    {
        return 0;
    }
    
    return (CountNodes(runner->children[RIGHT]) + 1 + (CountNodes(runner->children[LEFT])));

}

size_t AVLSize(const avl_t *avl)
{
    size_t counter = 0;
    assert(NULL != avl);
    
    if (avl->root != NULL)
    {
        avl_node_t *runner = avl->root;
        return CountNodes(runner);
    }
    return counter;
}


size_t AVLHeight(const avl_t *tree)
{
    assert(NULL != tree);

    return (0 == AVLIsEmpty(tree)? tree->root->height : 0 );
}




int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);

    return (NULL == tree->root);
}

void AVLRemove(avl_t *avl, const void *data)
{
    avl_node_t *runner = avl->root;
    assert(NULL != avl);

    
}




static avl_node_t *CreateNode(void *data)
{
    avl_node_t *node = (avl_node_t *)calloc(1,sizeof(avl_node_t));
    if (NULL == node)
    {
        return NULL;
    }
    
    node->data = data;
    node->height = 1;
   
    return node;
}

static int InsertNode(avl_node_t *new, void *n_data, avl_cmp_func_t CmpFunc)
{
    int where = CmpFunc(n_data, new->data);

    int status = FAILURE;

    assert(where != 0);

    if (NULL == new->children[0 < where])
    {
        new->children[0 < where] = CreateNode(n_data);
        if (new->children[0 < where] != NULL)
        {
            status =  SUCCESS;
        }
    }
    else
    {
        
        status = InsertNode(new->children[0 < where],n_data, CmpFunc);
    }

    new->height = 1 + MAX(GetChildHeight(new,LEFT), GetChildHeight(new,RIGHT));

    return status;
}

static int GetChildHeight(avl_node_t *node, int child)
{
   return ( (node->children[child] == NULL) ? 0 : node->children[child]->height);
}

int AVLInsert(avl_t *tree, void *n_data)
{  
   
    if(NULL == tree->root)
    {
      tree->root = (avl_node_t*)calloc(1, sizeof(avl_node_t));
      if(tree->root == NULL)
      {
        return FAILURE;
      }
        
      tree->root->data = n_data;
      tree->root->height = 1;

      return SUCCESS;
    }
    else
    {
        avl_node_t *runner = tree->root;

       return InsertNode(runner,n_data, tree->cmp_func);

    }
}



void *AVLFind(const avl_t *avl, const void *data)
{
   
    assert(NULL != avl);

    if (avl->root == NULL)
    {
        return NULL;
    }

    return RecFind(avl->root, data, avl->cmp_func);
}


static void *RecFind(avl_node_t *runner, const void *data, avl_cmp_func_t CmpFunc)
{
    int where = CmpFunc(data, runner->data);  

    if((0 == where) || (runner->children[0 < where] == NULL))
    {
        return ((!where) ? (runner->data) : NULL);
    }

    
    return RecFind(runner->children[(0 < where)], data, CmpFunc);

}




/*
void *AVLFind(const avl_t *avl, const void *data)
{
    avl_node_t *where = NULL;

    assert(NULL != avl);
    assert(NULL != data);

    if (avl->root == NULL)
    {
        return NULL;
    }

    where = RecFindNode(avl->root, data, avl->cmp_func);

    return (NULL == where) ? NULL : where->data;
}

static avl_node_t *RecFindNode(avl_node_t *runner, const void *data, avl_cmp_func_t CmpFunc)
{
    int where = CmpFunc(data, runner->data);  

    if((0 == where) || (runner->children[0 < where] == NULL))
    {
        return ((!where) ? (runner) : NULL);
    }

    
    return RecFindNode(runner->children[(0 < where)], data, CmpFunc);

}

*/

















