/**********************************
 * Heap - Source Code          	  *
 * Developer: Tanya               *
 * Feb 10, 2022                   *
 *                                *
 *      reviewed by               *
***********************************/
#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memset                      */
#include <assert.h>    /* assert                      */ 

#include "dynamic_vector.h"
#include "heap.h"

#define VCAP (10)
#define ELEM_S (sizeof(void *))



struct heap
{
    heap_cmp_func_t cmp_func;
    vector_t *vec;
};



static void HeapifyDown(vector_t *vec,size_t idx, heap_cmp_func_t cmp_fun);
static void HeapifyUp(vector_t *vec,size_t new_idx, heap_cmp_func_t cmp_fun);
static void *GetRightChild(vector_t *vec, size_t idx);
static void *GetLeftChild(vector_t *vec, size_t idx);
static void *GetParent(vector_t *vec, size_t idx);
static void GenericSwap(char *left, char *right, size_t size);




heap_t *HeapCreate(heap_cmp_func_t cmp_fun)
{
    heap_t *heap = NULL;

    assert(NULL != cmp_fun);

    heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->vec = VectorCreate(ELEM_S, VCAP);
    if (NULL == heap->vec)
    {
        free(heap);
        return NULL;
    }

    heap->cmp_func = cmp_fun;

    return heap;

}

void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    VectorDestroy(heap->vec);

    memset(heap,0, sizeof(heap_t));
    free(heap);
    heap = NULL;
}


int HeapPush(heap_t *heap, void *data)
{
    int status = 0;
   status =  VectorPushBack(heap->vec, data);
   HeapifyUp(heap->vec, VectorSize(heap->vec), heap->cmp_func);
}


int HeapIsEmpty(const heap_t *heap)
{
    assert (NULL != heap);
    return !VectorSize(heap->vec);
}

size_t HeapSize(const heap_t *heap)
{
    return (heap == NULL)? 0: VectorSize(heap->vec);
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorGetAccessToElement(heap->vec, 1);

}

static void GenericSwap(char *left, char *right, size_t size)
{
    while(0 < size)
    {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        ++right;
        --size;
    }
}


static void HeapifyUp(vector_t *vec,size_t new_idx, heap_cmp_func_t cmp_fun)
{
    if (cmp_fun(VectorGetAccessToElement(vec, new_idx),GetParent(vec,new_idx)) < 0 )
    {
        GenericSwap(VectorGetAccessToElement(vec, new_idx),GetParent(vec,new_idx), ELEM_S);
        HeapifyUp(vec, ((new_idx -1)>>1), cmp_fun);
    }
}

static void HeapifyDown(vector_t *vec,size_t idx, heap_cmp_func_t cmp_fun)
{
    void *left_child = NULL, *right_child = NULL;

    left_child = GetLeftChild(vec, idx);
    right_child = GetRightChild(vec,idx);
    
    if(0 ==  cmp_fun(left_child, right_child))
        return ;

    if(0 < cmp_fun(left_child, right_child))
    {
      GenericSwap(VectorGetAccessToElement(vec, idx),GetRightChild(vec,idx), ELEM_S); 
      HeapifyDown(vec,((idx * 2) + 2), cmp_fun); 
    }
    else
    {
        GenericSwap( VectorGetAccessToElement(vec, idx),GetLeftChild(vec,idx), ELEM_S);
        HeapifyDown(vec,((idx * 2) + 1), cmp_fun);   
    }

    

}

static void *GetParent(vector_t *vec, size_t idx)
{
    assert(0 <= idx);
    return VectorGetAccessToElement(vec, ((idx - 1)>>1));
}

static void *GetLeftChild(vector_t *vec, size_t idx)
{
    return VectorGetAccessToElement(vec, ((idx * 2) + 1));
}

static void *GetRightChild(vector_t *vec, size_t idx)
{
    return VectorGetAccessToElement(vec, ((idx * 2) + 2));
}