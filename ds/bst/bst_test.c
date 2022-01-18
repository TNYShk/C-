/**********************************************
 * Binary Search Tree Test - Source File      *
 * Developer: Tanya			                  *
 *          Jan 16, 2022                      *
 *                                            *
 * Reviewer:    		                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc */
#include <string.h> /* memcpy */
#include <stddef.h> /* size_t*/
#include <stdio.h> /*printf */
#include "bst.h" /* program header*/

int CompareData(const void *left, const void *right);
int PrinterFunc(void *data, void *param);
int main(void)
{
    bst_t *tree = BSTCreate(CompareData);
    int data = 5;
    int data1 = 6;
    int data2 = 2;
    void *getdata = NULL;
    bst_iter_t root = BSTInsert(tree, &data);
    bst_iter_t node = BSTInsert(tree, &data1);
    bst_iter_t node1 = BSTInsert(tree, &data2);
    bst_iter_t find;

    assert(node == BSTNext(root));
    assert(root == BSTPrev(node));
    printf("empty? %d\n", BSTIsEmpty(tree));
    printf("size? %ld\n", BSTSize(tree));
    getdata = BSTGetData(root);
    printf("root data: %d\n",*(int *)getdata);
    
    find = BSTFind(tree, &data1);
    getdata = BSTGetData(find);
    printf("found? data: %d\n",*(int *)getdata);
    getdata = BSTGetData(BSTBegin(tree));
    printf("BST begin data: %d\n",*(int *)getdata);
   
    BSTForEach(BSTBegin(tree),BSTEnd(tree),PrinterFunc, &data );
    /*
    should fail assert find = BSTInsert(tree, &data);*/

    BSTDestroy(tree);
    

    /*free(node1);
    free(node);
    free(root);
    free(tree);
    tree = NULL;*/
    return 0;
}







int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}

int PrinterFunc(void *data, void *param)
{
   
    printf("BST Root %d ", (*(int*)param));
    printf("Node: %d\n", (*(int*)data));
    
   
    return 0;
}
