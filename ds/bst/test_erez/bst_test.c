#include <assert.h>   /* assert */
#include <stdio.h>    /* printf */
#include <stdlib.h>   /* srand, rand, qsort*/
#include <time.h>     /*time*/
#include <sys/time.h> /* timeval */

#include "bst.h"


#define SIZE (50)
#define RANDOM_LIMITER (1000)

enum sort_status
{
    NOT_SORTED = -1,
    SORTED = 1
};

enum success
{
    FAIL = -1,
    SUCCESS
};


static void PopulateArray(int *arr, size_t arr_size)
{
    size_t i = 0;

    srand(time(NULL));

    for (i = 0; i < arr_size; ++i)
    {
        arr[i] = rand() / (RAND_MAX / RANDOM_LIMITER + 1);
    }
}

int ValidateTreeOrderedLeftToRight(bst_t *tree)
{
    int flag = SORTED;

    bst_iter_t iter = NULL;
    bst_iter_t iter_next = NULL;

    assert(NULL != tree);

    iter = BSTBegin(tree);
    iter_next = BSTNext(iter);
    while (BSTEnd(tree) != iter_next)
    {
        if (*(int *)BSTGetData(iter) > *(int *)BSTGetData(iter_next))
        {
            flag = NOT_SORTED;
        }
        iter = iter_next;
        iter_next = BSTNext(iter_next);
    }

    return flag;
}

int ValidateTreeOrderedRightToLeft(const bst_t *tree)
{
    int flag = SORTED;

    bst_iter_t iter = NULL;
    bst_iter_t iter_prev = NULL;

    assert(NULL != tree);

    iter = BSTEnd(tree);
    iter = BSTPrev(iter);
    iter_prev = BSTPrev(iter);

    while (BSTBegin(tree) != iter_prev)
    {
        if (*(int *)BSTGetData(iter) < *(int *)BSTGetData(iter_prev))
        {
            flag = NOT_SORTED;
        }

        iter = iter_prev;
        iter_prev = BSTPrev(iter_prev);
    }

    return flag;
}


int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}


int TestBSTCreateInsertIteratorsGetDataFindDataRemoveDestroy(void)
{

   
    bst_t *tree = NULL;
    bst_iter_t iter = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t number_of_removes = 0;
    size_t random_node_index = 0;
    size_t number_of_removes_actual = 0;
    int failure_flag = SUCCESS;
    size_t actual_insertions = 0;

    int arr[SIZE] = {0};

    size_t arr_size = SIZE;

    PopulateArray(arr, arr_size);

    printf("Creating tree with %ld nodes (discarding duplicates) of random values up to %d\n", arr_size, RANDOM_LIMITER);

    tree = BSTCreate(CompareData);
    printf("where?\n");
    for (i = 0; i < arr_size; ++i)
    {
        
            BSTInsert(tree, &arr[i]);
            ++actual_insertions;
        
    }
/*    PrintBST(tree); */
    number_of_removes = rand() / (RAND_MAX / SIZE + 1);

    number_of_removes_actual = 0;
    for (i = 0; i < number_of_removes; ++i)
    {
        random_node_index = rand() / (RAND_MAX / SIZE + 1);

        if (random_node_index < BSTSize(tree) - 1)
        {
            iter = BSTBegin(tree);
            for (j = 0; j < random_node_index; ++j)
            {
                iter = BSTNext(iter);
            }
                if (NULL != iter)
                {
                    BSTRemove(iter);
                    ++number_of_removes_actual;
                }
        }
    }


    printf("Removed %ld nodes from %ld insertions\n", number_of_removes_actual, actual_insertions);
    printf("Size of tree %ld\n", BSTSize(tree));
    assert(actual_insertions - number_of_removes_actual == BSTSize(tree));
/*    PrintBST(tree);
    printf("\n");
    PrintBSTReverse(tree); */

    assert (SORTED == ValidateTreeOrderedLeftToRight(tree));

    assert (SORTED == ValidateTreeOrderedRightToLeft(tree));

    if (SORTED != ValidateTreeOrderedLeftToRight(tree) ||
        SORTED != ValidateTreeOrderedRightToLeft(tree) ||
        (actual_insertions - number_of_removes_actual) != BSTSize(tree))
    {
        failure_flag = FAIL;
    }

    BSTDestroy(tree);

    return failure_flag;

}

int main()
{
    
    int failures = 0;


    if(FAIL == TestBSTCreateInsertIteratorsGetDataFindDataRemoveDestroy())
    {
        --failures;
    }

    if (0 > failures)
    {
        printf("Failed!\n");
    }
    else
    {
        printf("Passed!\n");
    }


        return 0;
}


/*


    iter = BSTBegin(tree);
    printf("Begin is %d\n", *(int *)BSTGetData(iter));
    printf("Removing\n");
    BSTRemove(iter);
        iter = BSTBegin(tree);
    iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));

    iter = BSTBegin(tree);
    printf("Begin is %d\n", *(int *)BSTGetData(iter));
    iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));
    iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));
    iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));
    iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));
    printf("Removing\n");
    BSTRemove(iter);
    printf("size is %ld\n", BSTSize(tree));
   iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));
    iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));
    iter = BSTNext(iter);
    printf("next is %d\n", *(int *)BSTGetData(iter));

    printf("iterating reverse\n");
    iter = BSTEnd(tree);
    iter = BSTPrev(iter);
    printf("End is %d\n", *(int *)BSTGetData(iter));
    iter = BSTPrev(iter);
    printf("Prev is %d\n", *(int *)BSTGetData(iter));
    iter = BSTPrev(iter);
    printf("Prev is %d\n", *(int *)BSTGetData(iter));
    iter = BSTPrev(iter);
    printf("Prev is %d\n", *(int *)BSTGetData(iter));
    iter = BSTPrev(iter);
    printf("Prev is %d\n", *(int *)BSTGetData(iter));
    iter = BSTPrev(iter);
    printf("Prev is %d\n", *(int *)BSTGetData(iter));
    iter = BSTPrev(iter);
    printf("Prev is %d\n", *(int *)BSTGetData(iter));
    iter = BSTPrev(iter);
    printf("Prev is %d\n", *(int *)BSTGetData(iter));



    PrintBST(tree);
   PrintBSTReverse(tree);
*/
