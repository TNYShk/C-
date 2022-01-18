/**********************************************
 * Binary Search Tree Test - Source File      *
 * Developer: Tanya			                  *
 *          Jan 16, 2022                      *
 *                                            *
 * Reviewer:    		                      *
 **********************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc */
#include <time.h> /*time_t */
#include <string.h> /* memcpy */
#include <stddef.h> /* size_t*/
#include <stdio.h> /*printf */
#include "bst.h" /* program header*/

#define RANGE (100)


int CompareData(const void *left, const void *right);
int PrinterFunc(void *data, void *param);
static void PopulateTree();


int main(void)
{

    bst_t *tree = BSTCreate(CompareData);
    bst_iter_t node1;
    bst_iter_t find;
    int data = 14;
    int data1 = 8;
    int data2 = 11;
    int data3 = 18;
    int data4 = 15;
    int data5 = 23;
    int data6 = 21;
    int data7 = 24;
    int data8 = 26;
    int data9 = 25;
    void *getdata = NULL;
    bst_iter_t root = BSTInsert(tree, &data);
    bst_iter_t node = BSTInsert(tree, &data1);
    BSTInsert(tree, &data2);
   
    BSTInsert(tree, &data3);
   
    BSTInsert(tree, &data4);
 
    node1 = BSTInsert(tree, &data5);
    BSTInsert(tree, &data6);
    BSTInsert(tree, &data7);
    BSTInsert(tree, &data8);
    BSTInsert(tree, &data9);
  
    printf("empty? %d\n", BSTIsEmpty(tree));
    printf("size? %ld\n", BSTSize(tree));
    
    printf("first node is: %d\n",*(int *)BSTGetData(BSTBegin(tree)));
    
    find = BSTFind(tree, &data1);
    getdata = BSTGetData(find);
    printf("found? data: %d\n",*(int *)getdata);
    getdata = BSTGetData(BSTBegin(tree));
    printf("BST begin data: %d\n",*(int *)getdata);
   
    BSTForEach(BSTBegin(tree),BSTEnd(tree),PrinterFunc, &data );
    BSTRemove(node1);

    printf("\npost removal of node:\n");
    BSTForEach(BSTBegin(tree),BSTEnd(tree),PrinterFunc, &data );
    printf("size? %ld\n", BSTSize(tree));
    BSTRemove(root);
    printf("\npost removal of root node:\n");
 
    BSTForEach(BSTBegin(tree),BSTEnd(tree),PrinterFunc, &data );
    printf("size? %ld\n", BSTSize(tree));
    printf("\n\n");
    
   

    BSTDestroy(tree);

     PopulateTree();
    return 0;
}

static void PopulateTree()
{
    bst_t *tree = BSTCreate(CompareData);
    bst_iter_t root;
    bst_iter_t node;
    bst_iter_t node1;
    bst_iter_t find;
    void *getdata = NULL;
    int data = 14;
    int data1 = 200;
    int data2 = 205;
    int data3 = 26;
    int data4 = 2;
    printf("Populate Tree test\n\n");
    (BSTIsEmpty(tree) == 1 ? printf("tree is empty\n") : printf("tree is not empty\n"));
   
    
    root = BSTInsert(tree, &data);
    node = BSTInsert(tree, &data1);
    node1 = BSTInsert(tree, &data2);
    BSTInsert(tree, &data3);
    BSTInsert(tree, &data4);
    find = BSTPrev(node1);
    printf("BST Prev data: %d\n",*(int *)BSTGetData(find));
    getdata = BSTGetData(BSTBegin(tree));
    printf("BST begin data: %d\n",*(int *)getdata);

    BSTForEach(BSTBegin(tree),BSTEnd(tree),PrinterFunc, &data );
   
    printf("size? %ld\n", BSTSize(tree));
    BSTDestroy(tree);
    printf("Test end\n\n");
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
