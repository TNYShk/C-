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



static void HeapifyDown(heap_t *heap,size_t idx);
static void HeapifyUp(heap_t *heap, size_t new_idx);
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
    HeapifyUp(heap, VectorSize(heap->vec) );

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

    return VectorGetAccessToElement(heap->vec,0);

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


static void HeapifyUp(heap_t *heap, size_t new_idx)
{
    size_t parent_idx = ((new_idx - 1) >> 1);
    void *parent_data = GetParent(heap->vec, parent_idx);
   
    if ( heap->cmp_func(VectorGetAccessToElement(heap->vec, new_idx), parent_data) < 0 )
    {
        GenericSwap(VectorGetAccessToElement(heap->vec, new_idx), parent_data, ELEM_S);
        HeapifyUp(heap, parent_idx);
    }

}

static void HeapifyDown(heap_t *heap, size_t idx)
{
    void *left_child = NULL, *right_child = NULL;
    size_t left_idx = (idx * 2) + 1;
    size_t right_idx = (idx * 2) + 2;

    left_child = GetLeftChild(heap->vec, idx);
    right_child = GetRightChild(heap->vec,idx);
    
    if(0 ==  heap->cmp_func(left_child, right_child))
        return ;

    if(0 < heap->cmp_func(left_child, right_child))
    {
      GenericSwap(VectorGetAccessToElement(heap->vec, idx),right_child, ELEM_S); 
      HeapifyDown(heap,right_idx); 
    }
    else
    {
        GenericSwap( VectorGetAccessToElement(heap->vec, idx),left_child, ELEM_S);
        HeapifyDown(heap,left_idx);   
    }

    

}

static void *GetParent(vector_t *vec, size_t idx)
{

    if(0 < idx)
    {
        size_t parent_idx = ((idx - 1) >> 1) & -sizeof(size_t);
        return VectorGetAccessToElement(vec, parent_idx);
    }
    return VectorGetAccessToElement(vec, (idx + 1));
}

static void *GetLeftChild(vector_t *vec, size_t idx)
{
    return VectorGetAccessToElement(vec, ((idx * 2) + 1));
}

static void *GetRightChild(vector_t *vec, size_t idx)
{
    return VectorGetAccessToElement(vec, ((idx * 2) + 2));
}