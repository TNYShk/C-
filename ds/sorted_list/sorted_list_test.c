/***********************************
 * Sorted Linked List WS		   *
 *           	                   *
 * by Tanya					       *
 *   		Dec 22, 2021	       *
 *                                 *
 * Reviewer: Amit                  *
 ***********************************/

#include <stdio.h>  /* printf, size_t      */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert()          */
#include <string.h> /* printf           */

#include "dll.h"
#include "sorted_list.h"



int CompareData(const void *left, const void *right);
int AddNum(void *data, void *param);
int MatchNums(const void *data, void *param);
static void PrintSListForward(const sort_list_t *slist);
int PrintListData(void *data, void *param);

void TestOne();
void TestTwo();




static void PrintSListForward(const sort_list_t *slist)
{
    sort_list_iter_t runner;
    
    assert(NULL != slist);
    
    runner = SortListBegin(slist);
    
    printf("\n-------List is:------\n");
    
    while (!SortListIterIsEqual(runner, SortListEnd(slist)))
    {
        printf("%d ", *(int *)SortListGetData(runner));
        runner = SortListNext(runner);
    }
    printf("\n\nSize of list is: %lu. List %s.\n", SortListSize(slist), SortListIsEmpty(slist) ? "is empty" : "is not empty");
    printf("-------list ends------\n");
}


int main (void)
{
    
    TestOne();
    TestTwo();
    return 0;
}

void TestOne()
{
    size_t x = 6;
    size_t y = 8;
    size_t one = 1;
    size_t s = 7;
    size_t ans = 0;
    void *ptr = NULL;
    sort_list_t *test = NULL;

    sort_list_iter_t iter1;
    
    test = SortListCreate(CompareData);
  
    printf("\n\t***********************-Test-1-*********************************\n\n");
    printf("\t****create sorted list, insert and pop front and back***********\n");
     
    iter1 = SortListInsert(test, &one);
    iter1 = SortListInsert(test, &y);
    iter1 = SortListInsert(test, &y);
    iter1 = SortListInsert(test, &s);
    iter1 = SortListInsert(test, &one);
    iter1 = SortListInsert(test, &x);
    
    
    PrintSListForward(test);
   
   (SortListSize(test) > 0)? printf("size is %ld\n",SortListSize(test)) : printf("empty list\n");
  
   (SortListIsEmpty(test) == 1) ? printf("IsEmpty -empty list\n") : printf("Not empty list\n");
   ptr = SortListPopFront(test);
   printf("pop front data is %ld\n",*(size_t*)ptr);
   ptr = SortListPopBack(test);
   printf("pop back data is %ld\n",*(size_t*)ptr);
   
    (SortListSize(test) > 0)? printf("size is %ld\n",SortListSize(test)) : printf("empty list\n");
    PrintSListForward(test);
    printf("\t**************insert and remove node********************************\n");
    ans = y * s;
    iter1 = SortListInsert(test, &ans);
    PrintSListForward(test);
    SortListRemove(iter1);
    PrintSListForward(test);
    
    SortListDestroy(test);
}

void TestTwo()
{
    size_t x = 60;
    size_t y = -88;
    size_t one = 11;
    size_t s = 77;
    size_t ans = 0;
    size_t uno = 1;
    void *ptr = NULL;
    sort_list_t *test = NULL;
    sort_list_t *test2 = NULL;
    sort_list_iter_t iter1, iter2, iter3, iter4;
    test = SortListCreate(CompareData);
    test2 = SortListCreate(CompareData);
  
    printf("\n\t***********************-Test-2-*********************************\n\n");
    printf("\t****create 2 sorted lists, insert in them ***********\n");
     
    iter1 = SortListInsert(test, &one);
    iter1 = SortListInsert(test, &y);
    iter1 = SortListInsert(test, &y);
    iter1 = SortListInsert(test, &ans);
   
    iter2 = SortListInsert(test2, &s);
    iter2 = SortListInsert(test2, &ans);
    iter2 = SortListInsert(test2, &x);

   
    
    printf("\n\t**************Before Merge********************************\n");

    printf("\t**************list1 src********************************\n");
    PrintSListForward(test);
    printf("\t**************list2 dest********************************\n");
    PrintSListForward(test2);
     
    printf("\t**************Post Merge********************************\n");
    SortListMerge(test2, test);
    
   
    printf("\t**************list1 src********************************\n");
    PrintSListForward(test);
    printf("\t**************list2 dest********************************\n");
    PrintSListForward(test2);
    
    printf("\t****insert to list1 src ***********\n");
    iter1 = SortListInsert(test, &y);
    iter3 = SortListInsert(test, &y);

    PrintSListForward(test);
    printf("\t****insert to list2 dest ***********\n");
    iter2 = SortListInsert(test2, &x);
    PrintSListForward(test2);
    printf("\n\t**************  List1 Before SortListForEach test********************************\n");
    PrintSListForward(test);
    printf("\n\t**************  List1 Post SortListForEach, add 1********************************\n");
    SortListForEach(iter3, iter1, &AddNum, &uno);
    PrintSListForward(test);
    
    printf("\n\t************** List1 SortListFindIf, search for zero********************************\n");
    iter2 = SortListFindIf(iter3, iter1,&MatchNums, &ans);
    (SortListGetData(iter2) == SortListGetData(iter1))? printf("Zero wasnt found\n"): printf("fount zero");

    printf("\n\t************** List2 SortListFind, search for 60 otherwise return last node********************************\n");
    iter4 = SortListFind(test2, SortListBegin(test2),SortListEnd(test2),&x);
    ptr = SortListGetData(iter4);
    printf("here's the data in the node returned: %ld\n", *(size_t*)ptr);
    PrintSListForward(test2);

    printf("\n\t************** List2 SortListFind, search for 1 otherwise return last node********************************\n");
    iter4 = SortListFind(test2, SortListBegin(test2),SortListEnd(test2),&uno);
    ptr = SortListGetData(iter4);
    printf("here's the data in the node returned: %ld\n", *(size_t*)ptr);


    SortListDestroy(test);
    SortListDestroy(test2);

}
/**** Action, Match Funcs ****/
int PrintListData(void *data, void *param)
{
    (void) param;
    printf("Value: %ld\n", *(size_t *)data);
    
    return 0;
}

int AddNum(void *data, void *param)
{
    *(size_t *)data += *(size_t *)param;
    
    return 0;
}

int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}


int MatchNums(const void *data, void *param)
{   
    return (*(size_t *)data == *(size_t *)param);
}
