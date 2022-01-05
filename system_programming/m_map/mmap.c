/**********************************************
 * MMAP  - Test File                          *
 * Developer:  Tanya                          *
 * Written:   04/01/2022                      *
 * Reviewer: __________                       *
 *                                            *
 **********************************************/
#include <stdlib.h> /* size_t  */
#include <assert.h> /* asserts */
#include <stdio.h> /* printf */
#include <limits.h> /* for LONG_MAX, LONG_MIN */


#define NUMBER (666)

int glob_num = 666;
const int why = 42;
static int glob_stat;



static int Multiply(int x, int y)
{
       return (x * y);
}

extern void PrintSome(int num, int another)
{
    static int counter = 0;
    
    printf("answer is %d\n", Multiply(num, another));
    ++counter;
     printf("static counter %p\n",&counter);
}

int main(int argc, char const *argv[], char **envp)
{

    int local = 0;
    int *heap_space = (int*)malloc(sizeof(int) * 100);
    char *str_literal = "literlly";

    *heap_space = NUMBER;
    local = *heap_space * why;

    
    printf("heap_space %d\n",*heap_space);
    free(heap_space);
   
    PrintSome(local, NUMBER);
    glob_stat = *argv[1];
   

    printf("\n ----------print all---------\n");
    printf("static int glob_stat %p\n",&glob_stat);
    printf("const int why %p\n", &why);
    printf("int glob_num %p\n",&glob_num);
    printf("local is why * heap %p\n",&local);
    printf("heap_space %p\n",&heap_space);
    printf("glob_stat %p\n",&glob_stat);
    printf("envp is %p\n", &envp[1]);
    printf("str_literal %p\n", &str_literal);
    printf("PrintSome Func %p\n", PrintSome);
   


    return 0;
}