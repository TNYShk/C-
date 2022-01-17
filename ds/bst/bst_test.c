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

int main(void)
{
    bst_t *tree = BSTCreate(CompareData);
   int data = 5;
   int data1 = 6;
    bst_iter_t root = BSTInsert(tree, &data);
    bst_iter_t node = BSTInsert(tree, &data1);
    assert(node == BSTNext(root));
    printf("empty? %d\n", BSTIsEmpty(tree));
    printf("size? %ld\n", BSTSize(tree));


    free(node);
    free(root);
    free(tree);
    tree = NULL;
    return 0;
}







int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}