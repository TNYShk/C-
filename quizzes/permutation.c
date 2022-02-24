/**********************************************
 * permutation quiz- C File                               *
 * Developer: Tanya                            *
 * Written:   15/02/2022                       *
 *                                             *
 * Reviewer:                       *
 **********************************************/
#include <stdlib.h> /* malloc() calloc() free() */  /*******/
#include <string.h> /* memset() */
#include <stdio.h>
#include <stdint.h>
#include <limits.h> /*for LONG_MAX */
#include <assert.h> /* assert() */

void Permutation(char *string);
static void RecPermutation(char *string, size_t left, size_t right);
static void GenericSwap(char *left, char *right);
void Permutation1(char *string, size_t idx);

int main (void)
{
    char string[10] = "ABC";
    char another[10]= "ABC";
    Permutation(string);
    printf("\n");
    Permutation1(another,0);
    printf("\n");
    return 0;

}


void Permutation(char *string)
{

    RecPermutation(string, 0, strlen(string) -1);
}

void Permutation1(char *string, size_t idx)
{
    size_t i = 0;
    if (idx == strlen(string))
    {
        printf("%s ,",string);
        return;
    }

    for(i = idx; i < strlen(string); ++i)
    {
        if (0 != strcmp(string + idx, string + i))
                GenericSwap(string + idx, string + i);
        Permutation1(string, idx +1);
        GenericSwap(string + idx, string + i);
    }
}


static void RecPermutation(char *string, size_t left, size_t right)
{
    size_t idx = 0;
    
    if (left == right)
    {
        printf(" %s\n", string);
        return;
    }

    for(idx = left; idx <= right; ++idx)
    {
        GenericSwap((string + left), (string + idx));
        RecPermutation(string, left + 1, right);
        GenericSwap((string + left), (string + idx));
    }
}




static void GenericSwap(char *left, char *right)
{
    char temp = 0;
    temp = *left;
    *left = *right;
    *right = temp; 
}