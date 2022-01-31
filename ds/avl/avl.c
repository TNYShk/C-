/**********************************************
 * AVL - Source File                          *
 * Developer: Tanya			                  *
 *          Jan 26, 2022                      *
 *                                            *
 * Reviewer:         	                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc, free */
#include <string.h> /* memset */
#include <math.h> /* abs */

#include "../include/avl.h" /* programs header*/

#define MAX(a,b) ((a > b)? (a) : (b))
#define DIRECTION(a) (0 < a)


typedef enum status
{
    FAILURE = -1,
    SUCCESS = 0,
    ALLOC_ERROR = -2
    
}status_e;

enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct avl_node avl_node_t;
typedef int (*forEachFunc)(avl_node_t *tree, avl_action_func_t action, void *param);

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


static avl_node_t *CreateNode(void *data);
static avl_node_t *InsertNode(avl_node_t *new, void *n_data, avl_cmp_func_t CmpFunc, int*);

static void Destroy(avl_node_t *runner);
static avl_node_t *DeleteNode(avl_node_t *runner, void *data_to_remove, avl_cmp_func_t CmpFunc);

static size_t CountNodes(avl_node_t *runner);
static status_e ActionCounter(void *data, void *param);
static int GetChildHeight(avl_node_t *node, int child);

static avl_node_t *RecFindNode(avl_node_t *runner, const void *data, avl_cmp_func_t CmpFunc);
static void *RecFind(avl_node_t *runner, const void *data, avl_cmp_func_t CmpFunc);

static int ForEachPreOrder(avl_node_t *node, avl_action_func_t action_func, void *param);
static int ForEachInOrder(avl_node_t *node, avl_action_func_t action_func, void *param);
static int ForEachPostOrder(avl_node_t *node, avl_action_func_t action_func, void *param);

static avl_node_t *MinNodeTree(avl_t *tree);
static avl_node_t *GetMinValSubTree(avl_node_t *runner);

static int GetBalanceFactor(avl_node_t *subtree);

static avl_node_t *RotateNode(avl_node_t *node, int side);
static avl_node_t *RotateLeft(avl_node_t *node);
static avl_node_t *RotateRight(avl_node_t *node);
static avl_node_t *BalanceTree(avl_node_t *new, void *n_data, avl_cmp_func_t CmpFunc);





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

    Destroy(tree->root);
    
    memset(tree,0,sizeof(avl_t));
    free(tree);
    tree = NULL;
}




size_t AVLSize(const avl_t *avl)
{
    size_t counter = 0;

    assert(NULL != avl);
    
    if (NULL != avl->root)
    {
        AVLForEach((avl_t *)avl, ActionCounter, &counter, IN_ORDER);
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


void AVLRemove(avl_t *tree, const void *data)
{
    avl_node_t *find_node = NULL;
    assert(NULL != tree);

    find_node = RecFindNode(tree->root, data, tree->cmp_func);
    if (NULL != find_node)
    {
       tree->root = DeleteNode(tree->root, (void *)data, tree->cmp_func);
    } 
}




int AVLInsert(avl_t *tree, void *n_data)
{  
    int status = SUCCESS;

    if(NULL == tree->root)
    {
      tree->root = CreateNode(n_data);
      if(NULL == tree->root)
      {
        return ALLOC_ERROR;
      }

      status =  SUCCESS;
    }
    else
    {
        tree->root = InsertNode(tree->root, n_data, tree->cmp_func, &status);
    }
   return status;
}



void *AVLFind(const avl_t *avl, const void *data)
{
    assert(NULL != avl);

    if (NULL == avl->root)
    {
        return NULL;
    }

    return RecFind(avl->root, data, avl->cmp_func);
}

int AVLForEach(avl_t *avl, avl_action_func_t action_func, void *param, order_t order)
{
   static const forEachFunc forEachLut[] = {ForEachPreOrder, ForEachInOrder, ForEachPostOrder};

    assert(NULL != avl);
    assert(NULL != action_func);
    assert(NUM_OF_ORDERS > order);

    return forEachLut[order](avl->root, action_func, param);
}



/****************************Service Recursive Functions **************************/

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

static avl_node_t *InsertNode(avl_node_t *new, void *n_data, avl_cmp_func_t CmpFunc, int *status)
{
    int where2go = CmpFunc(n_data, new->data);
    int balance = 0;
   
    assert(0 != where2go);

    if (NULL == new->children[DIRECTION(where2go)])
    {
        new->children[DIRECTION(where2go)] = CreateNode(n_data);
        if (NULL == new->children[DIRECTION(where2go)])
        {
            return NULL;
        }
        *status = (NULL == new->children[DIRECTION(where2go)]);
    }
    else
    {
        new->children[DIRECTION(where2go)] = InsertNode(new->children[DIRECTION(where2go)],n_data, CmpFunc, status);
    }
    
     new->height = ( 1 + MAX(GetChildHeight(new,LEFT), GetChildHeight(new,RIGHT)));
   
   return BalanceTree(new, n_data, CmpFunc);
}


static avl_node_t *BalanceTree(avl_node_t *new, void *n_data, avl_cmp_func_t CmpFunc)
{
    int balance = GetBalanceFactor(new); 
    
    if( 1 < abs(balance) )
    {
        printf("balance factor is: %d\nbalancing tree\n", balance);
        if (balance == -2)
        {
            if(0 > CmpFunc(n_data,new->children[DIRECTION(balance)]))
            {
                new = RotateNode(new,RIGHT);
                printf("rotated data %d\n", *(int *)new->data);
            }
            else  
            {
                new->children[DIRECTION(balance)] = RotateNode(new->children[DIRECTION(balance)],LEFT);
                new = RotateNode(new,RIGHT);
                printf("rotated data %d\n", *(int *)new->data);
            }     
        }
        else if(balance == 2)
        {
            if(0 < CmpFunc(n_data, new->children[DIRECTION(balance)]))
            {
                new = RotateNode(new,LEFT);
                printf("rotated data %d\n", *(int *)new->data);
            }
            else
            {
               new->children[DIRECTION(balance)] = RotateNode(new->children[DIRECTION(balance)],RIGHT);
               new = RotateNode(new,LEFT);
               printf("rotated data %d\n", *(int *)new->data);
            }
        }
    }

    return new;

}

static avl_node_t *RotateNode(avl_node_t *node, int side)
{
    
    avl_node_t *rotator = node->children[!side];
    
    node->children[!side] = rotator->children[side];
    rotator->children[side] = node;
    
  
    node->height = ( 1 + MAX(GetChildHeight(node,LEFT), GetChildHeight(node,RIGHT)));
    rotator->height = ( 1 + MAX(GetChildHeight(rotator,LEFT), GetChildHeight(rotator,RIGHT)));
   
    return rotator;
}


static void Destroy(avl_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    Destroy(node->children[LEFT]);
    Destroy(node->children[RIGHT]);
    
    /*printf("deleted node with data %d\n", *(int *)node->data);*/
    
    free(node);
    node = NULL;
}


static avl_node_t *DeleteNode(avl_node_t *root, void *data2remove, avl_cmp_func_t CmpFunc)
{
    int where = CmpFunc(data2remove, root->data);
   
    if(where != 0)
    {
        root->children[DIRECTION(where)] = DeleteNode(root->children[DIRECTION(where)], data2remove, CmpFunc);
    }
    
    else
    {
        /* node-to-remove has 0-1 children*/
        if( (NULL == root->children[LEFT]) || (NULL == root->children[RIGHT]))
        {
            avl_node_t *temp_node = root->children[LEFT]? root->children[LEFT] : root->children[RIGHT];

            if(NULL == temp_node)
            {
                temp_node = root;
                root = NULL;
            }
            else
            {
                root->data = temp_node->data; 
            }

            free(temp_node);
            temp_node = NULL;
        }
        else
        {
            avl_node_t *temp_node = GetMinValSubTree(root->children[RIGHT]);

            root->data = temp_node->data;

            root->children[RIGHT] = DeleteNode(root->children[RIGHT],temp_node->data, CmpFunc);
        }
    }

    if (NULL == root)
    {
        return root;
    }

    root->height = ( 1 + MAX(GetChildHeight(root,LEFT), GetChildHeight(root,RIGHT)));
    
    return BalanceTree(root, data2remove, CmpFunc);
}


static int GetChildHeight(avl_node_t *node, int child)
{
    if(node != NULL)
    {
        return ( (node->children[child] == NULL) ? 0 : node->children[child]->height);
    }
    return 0;
   }
   


static void *RecFind(avl_node_t *node, const void *data, avl_cmp_func_t CmpFunc)
{
    int where = CmpFunc(data, node->data);  

    if ( (0 == where) || (NULL == node->children[DIRECTION(where)]) )
    {   
        return ((!where) ? (node->data) : NULL);
    }       /* where == 0*/

    return RecFind(node->children[DIRECTION(where)], data, CmpFunc);
}

static int ForEachPreOrder(avl_node_t *node, avl_action_func_t action_func, void *param)
{
    int status = SUCCESS;

    if (NULL == node)
    {
        return status;
    }
   (void)(status || (status  += action_func(node->data, param)));
    return (status || (ForEachPreOrder(node->children[LEFT], action_func, param) +
            ForEachPreOrder(node->children[RIGHT], action_func, param)));
}

static int ForEachInOrder(avl_node_t *node, avl_action_func_t action_func, void *param)
{
    int status = SUCCESS;

    if (NULL == node)  
    {
        return status;
    }
    (void)(status != 0  || (status += ForEachInOrder(node->children[LEFT], action_func, param)));
    (void)(status != 0 || (status  += action_func(node->data, param)));
    (void)(status !=0 || (status += ForEachInOrder(node->children[RIGHT], action_func, param)));

    return (status != 0); 
}

static int ForEachPostOrder(avl_node_t *node, avl_action_func_t action_func, void *param)
{
    int status = SUCCESS;

    if (NULL == node) 
    {
        return status;
    }
    (void)(status ||(status += (ForEachPostOrder(node->children[LEFT], action_func, param) + 
                                ForEachPostOrder(node->children[RIGHT], action_func, param))));
    (void)(status ||(status  += action_func(node->data, param)));

    return (status != 0); 
}


static avl_node_t *RecFindNode(avl_node_t *runner, const void *data, avl_cmp_func_t CmpFunc)
{
    int where = CmpFunc(data, runner->data);  

    if((0 == where) || (NULL == runner->children[DIRECTION(where)]))
    {
        return ((!where) ? (runner) : NULL);
    }

    return RecFindNode(runner->children[DIRECTION(where)], data, CmpFunc);
}



static avl_node_t *MinNodeTree(avl_t *tree)
{
    avl_node_t *runner = NULL;

    assert(NULL != tree);
    assert(NULL != tree->root);

    runner = tree->root;

    if(!AVLIsEmpty(tree))
    {
        return GetMinValSubTree(runner);
    }

    return runner;
}

static avl_node_t *GetMinValSubTree(avl_node_t *runner)
{
    while(NULL != runner->children[LEFT])
    {
        runner = runner->children[LEFT];
    }

    return runner;
}

static size_t CountNodes(avl_node_t *runner)
{
    if (NULL == runner)
    {
        return 0;
    }
    
    return (CountNodes(runner->children[RIGHT]) + 1 + (CountNodes(runner->children[LEFT])));
}

static status_e ActionCounter(void *data, void *param)
{
    ++(*(size_t *)param);
    (void)data;

    return SUCCESS;
}



static int GetBalanceFactor(avl_node_t *subtree)
{
    if (NULL == subtree)
        return 0;

    return (GetChildHeight(subtree,RIGHT) - GetChildHeight(subtree,LEFT) );
}



static avl_node_t *RotateRight(avl_node_t *node)
{
    
    avl_node_t *rotator = node->children[LEFT];
    avl_node_t *temp = rotator->children[RIGHT];
    printf("rotating RIGHT node is: %d\n", *(int *)node->data);
    rotator->children[RIGHT] = node;
    node->children[LEFT] = temp;

    node->height = ( 1 + MAX(GetChildHeight(node,LEFT), GetChildHeight(node,RIGHT)));
    rotator->height = ( 1 + MAX(GetChildHeight(rotator,LEFT), GetChildHeight(rotator,RIGHT)));
    printf("RIGHTrotated node is: %d\n", *(int *)rotator->data);
    return rotator; 
}

static avl_node_t *RotateLeft(avl_node_t *node)
{
    avl_node_t *rotator = node->children[RIGHT];
    avl_node_t *temp = rotator->children[LEFT];
    printf("LEFT rotating node is: %d\n", *(int *)node->data);
    rotator->children[LEFT] = node;
    node->children[RIGHT] = temp;

    

    node->height = ( 1 + MAX(GetChildHeight(node,LEFT), GetChildHeight(node,RIGHT)));
    rotator->height = ( 1 + MAX(GetChildHeight(rotator,LEFT), GetChildHeight(rotator,RIGHT)));
    printf("LEFT rotated node is: %d\n", *(int *)rotator->data);
    return rotator; 
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
/*
static int InsertNode(avl_node_t *new, void *n_data, avl_cmp_func_t CmpFunc)
{
    int where2go = CmpFunc(n_data, new->data);
    int balance = 0;
    int status = SUCCESS;

    assert(0 != where2go);

    if (NULL == new->children[DIRECTION(where2go)])
    {
        new->children[DIRECTION(where2go)] = CreateNode(n_data);
        if (NULL == new->children[DIRECTION(where2go)])
        {
            return FAILURE;
        }
    }
    else
    {
        status = InsertNode(new->children[DIRECTION(where2go)],n_data, CmpFunc);
    }
    
    balance = GetBalanceFactor(new); 
    printf("balance factor is: %d\n", balance);


   if( 1 < abs(balance) )
    {
        if (balance <= -1)
        {
            if(0 > CmpFunc(n_data,new->children[LEFT]))
            {
                new = RotateRight(new);
            }
            else
            {
                new->children[LEFT] = RotateLeft(new->children[LEFT]);
                new = RotateRight(new);
            }     
        }
        else if(balance >= 1)
        {
            if(0 < CmpFunc(n_data, new->children[RIGHT]))
            {
                new = RotateLeft(new);
            }
            else
            {
               new->children[RIGHT] = RotateRight(new->children[RIGHT]);
               new = RotateLeft(new);
            }
        }
    }

    new->height = ( 1 + MAX(GetChildHeight(new,LEFT), GetChildHeight(new,RIGHT)));
   
    return status;
}
*/