/**********************************
 * Heap - Source Code          	  *
 * Developer: Tanya               *
 * Feb 10, 2022                   *
 *                                *
 *      reviewed by               *
***********************************/
#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memmove                      */
#include <assert.h>    /* assert                      */ 

#include "dynamic_vector.h"
#include "heap.h"

#define VCAP (10)
#define ELEM_S (sizeof(size_t))



struct heap
{
    heap_cmp_func_t cmp_func;
    vector_t *vec;
};



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



