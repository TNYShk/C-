/**********************************
 * Heap - Source Code          	  *
 * Developer: Tanya               *
 * Feb 8, 2022                    *
 *                                *
 *      reviewed by   Zohar       *
***********************************/
#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memset                      */
#include <assert.h>    /* assert                      */ 

#include "heap.h" /* lib api */
#include "dynamic_vector.h" /* lib api */


#define VCAP (16)
#define ELEM_S (sizeof(size_t))
#define HEAPROOT (0)



struct heap
{
    heap_cmp_func_t cmp_func;
    vector_t *vec;
};


static void HeapifyDown(heap_t *heap,size_t idx);
static void HeapifyUp(heap_t *heap, size_t idx);

static void PSwap(void **left, void **right);
static void GenericSwap(char *left, char *right, size_t size);
static void PrintHeap(heap_t *heap);



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
        heap = NULL;
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
    size_t cur = 0;

    assert(NULL != heap);
    assert (NULL != data);

    cur = HeapSize(heap);

    VectorPushBack(heap->vec, &data);
    HeapifyUp(heap, HeapSize(heap) - 1);
    
 #ifdef DEBUG
     PrintHeap(heap);
#endif

    return (cur == HeapSize(heap));
}


void HeapPop(heap_t *heap)
{
    void **last = NULL;
    void **root = NULL;

    assert(NULL != heap);
    
    last = VectorGetAccessToElement(heap->vec, HeapSize(heap) -1);
    root = VectorGetAccessToElement(heap->vec, HEAPROOT);
   
    PSwap(root, last);
    VectorPopBack(heap->vec);
    HeapifyDown(heap, HEAPROOT);    
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

    return *(void **)VectorGetAccessToElement(heap->vec,HEAPROOT);
}


void *HeapRemove(heap_t *heap, heap_is_match_func_t match_func, void *param)
{
    size_t idx = 0;
    void **last = NULL;
    void *removed_data = NULL;

    assert(0 != HeapSize(heap));

    last = VectorGetAccessToElement(heap->vec, HeapSize(heap) -1);
    
    while(!match_func(*(void **)VectorGetAccessToElement(heap->vec, idx), param) && (idx < HeapSize(heap)))
    {
       ++idx;
    }
    if (match_func(*(void **)VectorGetAccessToElement(heap->vec, idx), param))
    {
        PSwap(VectorGetAccessToElement(heap->vec, idx), last);

        removed_data = *(void **)VectorGetAccessToElement(heap->vec, (HeapSize(heap) - 1));
        
        VectorPopBack(heap->vec);
        HeapifyUp(heap,idx);
        HeapifyDown(heap,idx);
    }

#ifdef DEBUG
     PrintHeap(heap);
#endif
   
    return removed_data;
}



static void HeapifyUp(heap_t *heap, size_t new_idx)
{
    size_t parent_idx = ((new_idx - 1) >> 1);

    void **parent_data = NULL;
    void **data = NULL;
    
    if(0 == new_idx)
    {
        return;
    }

    data = VectorGetAccessToElement(heap->vec, new_idx);
    parent_data = VectorGetAccessToElement(heap->vec, parent_idx);

    if ( 0 > heap->cmp_func(*data, *parent_data) )
    {
        PSwap(VectorGetAccessToElement(heap->vec, new_idx), parent_data);
        HeapifyUp(heap, parent_idx);
    }
}

static void HeapifyDown(heap_t *heap, size_t idx)
{
    void **left_child = NULL, **right_child = NULL, **data = NULL;

    size_t left = (idx << 1) + 1;
    size_t right = (idx << 1) + 2;
    size_t length = HeapSize(heap) ;
    size_t nex_idx = idx;

    assert(NULL != heap);

    left_child = VectorGetAccessToElement(heap->vec, left);
    right_child = VectorGetAccessToElement(heap->vec, right);
    data =         VectorGetAccessToElement(heap->vec, idx);
    
    if(left < length && heap->cmp_func(*left_child, *data ) < 0)
    {
        nex_idx = left;
    }
    if(right < length && heap->cmp_func(*right_child, *data ) < 0)
    {
        if (heap->cmp_func(*right_child, *left_child ) < 0)
            nex_idx = right;
    }
    
    if (nex_idx != idx)
    {
        PSwap(data,VectorGetAccessToElement(heap->vec, nex_idx)); 
        HeapifyDown(heap, nex_idx);
    }
    
}

static void PSwap(void **left, void **right)
{
    void *holder = *left;
    *left = *right;
    *right = holder;
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

static void PrintHeap(heap_t *heap)
{
    size_t i = 0;
    printf("\n");
    for (; i < HeapSize(heap); ++i)
    {
        printf("%ld, ", **(int **)VectorGetAccessToElement(heap->vec, i));
    }
}



