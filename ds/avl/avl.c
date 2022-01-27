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
    tree->root = NULL;
    
    return tree;
}


void AVLDestroy(avl_t *tree)
{
    
    
    
    assert(NULL != tree);
    
    if (tree->root != NULL)
    {
        avl_node_t *runner = tree->root;
        printf("root data is %d\n", *(int *)runner->data);
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
/*
static int WhichChild(avl_node_t *parent, avl_node_t *child)
{
    return (child == parent->children[RIGHT])
}


static int HasChild(avl_node_t *parent, int child)
{
    return (NULL != parent->children[child])
}

static void DestroyNode(avl_node_t *todestroy)
{
   avl_node_t *runner = NULL;

   if (runner == NULL)
   {
    free(runner);
   }

   
   runner = todestroy->children[HasChild(todestroy,RIGHT)];
   runner = todestroy->children[HasChild(todestroy,LEFT)];
   DestroyNode(runner);

}
*/

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



int AVLInsert(avl_t *tree, void *n_data)
{  
    avl_node_t *newnode = NULL;
    int where = 0;

    if(NULL == tree->root)
    {
      tree->root = (avl_node_t*)calloc(1, sizeof(avl_node_t));
      if(tree->root == NULL)
      {
        return FAILURE;
      }
        
      tree->root->data = n_data;
      tree->root->height += 1;

      return SUCCESS;
    }
    else
    {
        avl_node_t *runner = tree->root;
        where = tree->cmp_func(tree->root->data, n_data);


    }
    return SUCCESS;
}









