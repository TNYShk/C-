/*******************************************************************************
 HEAP EXERCISE
 Date: 6/2/2021
 Version: 1.0
 Written by: Ofer
 Reviewed by: Tanya
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "utils.h"  /* utils library */
#include "heap.h"   /* heap API */

static void Test1(void);
static void Test2(void);
static void Test3(void);
static void Test4(void);
static void Test5(void);
static void Test6(void);
static void Test7(void);
static int IntCmpFunc(const void *key1, const void *key2);
int MatchFunc(const void *element, const void *param);

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5(); 
    Test6();
    Test7();
    return 0;
}

static void Test1()
{
    heap_t *heap = HeapCreate(&IntCmpFunc);

    assert(NULL != heap);

    HeapDestroy(heap);

    printf("Test1 - Create, Destory - success\n\n");
}

static void Test2()
{
    heap_t *heap = HeapCreate(&IntCmpFunc);

    assert(NULL != heap);

    CONDITION_TEST(TRUE, HeapIsEmpty(heap));
    CONDITION_TEST(0, HeapSize(heap));

    HeapDestroy(heap);

    printf("Test2 - IsEmpty, Size - success\n");
}

static void Test3()
{
    heap_t *heap = HeapCreate(&IntCmpFunc);
    int num1 = 13;
    int num2 = 89;

    assert(NULL != heap);

    CONDITION_TEST(SUCCESS, HeapPush(heap, &num2));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num1));

    CONDITION_TEST(13, *(int *)HeapPeek(heap));

    HeapDestroy(heap);

    printf("Test3 - Insert, HeapifyUp, Peek - success\n\n");
}

static void Test4()
{
    heap_t *heap = HeapCreate(&IntCmpFunc);
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    int num6 = 6;
    int num7 = 7;
    int num8 = 8;
    int num9 = 9;
    int num10 = 10;

    assert(NULL != heap);

    CONDITION_TEST(SUCCESS, HeapPush(heap, &num1));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num2));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num3));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num4));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num5));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num6));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num7));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num8));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num9));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num10));

    CONDITION_TEST(1, *(int *)HeapPeek(heap));

    HeapPop(heap);

    CONDITION_TEST(2, *(int *)HeapPeek(heap));
    CONDITION_TEST(HeapSize(heap), 9)

    HeapDestroy(heap);

    printf("Test4 - Multiple inserts, Peek, Pop - success\n\n");
}

static void Test5()
{
    heap_t *heap = HeapCreate(&IntCmpFunc);
    int num1 = 1;
    int num2 = 8;
    int num3 = 7;
    int num4 = 11;
    int num5 = 17;
    int num6 = 35;
    int num7 = 9;
    int num8 = 18;
    int num9 = 25;
    
    assert(NULL != heap);

    CONDITION_TEST(SUCCESS, HeapPush(heap, &num1));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num2));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num3));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num4));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num5));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num6));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num7));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num8));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num9));

    CONDITION_TEST(1, *(int *)HeapPeek(heap));

    HeapPop(heap);

    CONDITION_TEST(7, *(int *)HeapPeek(heap));

    HeapDestroy(heap);
    
    printf("Test5 - Peek, Pop, HeapifyDown - success\n\n");
}

static void Test6(void)
{
    heap_t *heap = HeapCreate(&IntCmpFunc);
    int num1 = 1;
    int num2 = 8;
    int num3 = 7;
    int num4 = 11;
    int num5 = 17;
    int num6 = 35;
    int num7 = 9;
    int num8 = 18;
    int num9 = 25;
    
    assert(NULL != heap);

    CONDITION_TEST(SUCCESS, HeapPush(heap, &num1));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num2));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num3));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num4));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num5));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num6));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num7));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num8));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num9));

    CONDITION_TEST(1, *(int *)HeapPeek(heap));

    CONDITION_TEST(7 , *(int *)HeapRemove(heap, &MatchFunc, &num3));

    CONDITION_TEST(HeapSize(heap), 8);

    HeapPeek(heap);

    HeapDestroy(heap);
 
    printf("Test6 - Remove - success\n\n");
}

static void Test7()
{
    heap_t *heap = HeapCreate(&IntCmpFunc);
    int num1 = 13;
    int num2 = 53;
    int num3 = 4;

    assert(NULL != heap);

    CONDITION_TEST(SUCCESS, HeapPush(heap, &num1));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num2));
    CONDITION_TEST(SUCCESS, HeapPush(heap, &num3));

    HeapPop(heap);

    HeapPeek(heap);

    HeapPop(heap);


    HeapDestroy(heap);

    printf("Test7 - success\n");
}


static int IntCmpFunc(const void *key1, const void *key2)
{
    return *(int *)key1 - *(int *)key2;
}

int MatchFunc(const void *element, const void *param)
{
    return (*(int *)element == *(int *)param);
}