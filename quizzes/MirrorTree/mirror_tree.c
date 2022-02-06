/**********************************\
* AVL  MirrorTree                  *
* Developer:   Tanya               *
* Written: 2021-1-30               *
*                                  *
* Reviewer:                        *
\**********************************/
#include <stdio.h>    /* printf */
#include <assert.h> /* assert */

#include <stdlib.h> /*memory allocation & free */
#include <string.h> /* testing strlen, strcmp, strstr*/

#include "../../ds/include/avl.h"


typedef struct avl_node avl_node_t;

enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

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


void Swap(avl_node_t **left, avl_node_t **right);
void MirrorTree(avl_node_t* root);
int PrintNodes(void *data, void *param);
int CompareData(const void *left, const void *right);

int main(void)
{

    avl_t *avl = NULL;
    int num = 6;
    int num2 = 18;
    int num3 = 5;
    int num4 = 4;
    int num5 = 11;
    int num6 = 110;
    int num7 = 111;

    avl = AVLCreate(CompareData);

    assert(1 == AVLIsEmpty(avl));
    (0 == AVLInsert(avl, &num)? printf("inserted data into tree!\n"): printf("Failed!\n") );
    assert(0 == AVLInsert(avl, &num2));
    assert(0 == AVLIsEmpty(avl));
    /*assert(0 != AVLInsert(avl, &num2)); WORKS, assert same number */
    assert(0 == AVLInsert(avl, &num3));
   
    assert(0 == AVLInsert(avl, &num4));
    assert(0 == AVLInsert(avl, &num5));
    assert(0 == AVLInsert(avl, &num6));
    assert(6 == AVLSize(avl));
    assert(0 == AVLForEach(avl, PrintNodes, &num, IN_ORDER));
    
    MirrorTree(avl->root);
    printf("\n Mirrored Tree! here:\n");
    assert(0 == AVLForEach(avl, PrintNodes, &num, IN_ORDER));
    printf("\n");
    AVLDestroy(avl);

    return 0;
}


void MirrorTree(avl_node_t *root)
{
    if(NULL == root)
        return;

    Swap(&root->children[LEFT], &root->children[RIGHT]);
    MirrorTree(root->children[LEFT]);
    MirrorTree(root->children[RIGHT]);

}

void Swap(avl_node_t **left, avl_node_t **right)
{
    avl_node_t *temp = *left;
    *left = *right;
    *right = temp;
}

int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}

int PrintNodes(void *data, void *param)
{
    printf("Node: %d ", (*(int*)data));

    (void)param;

     return 0;
}
