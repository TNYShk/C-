/**********************************
 * C Basic Quiz - C File          *
 * Developer: Tanya               *
 * Written:   17/02/2022          *
 *                                *
 * Reviewer:              *
 **********************************/
#include <stdint.h> /* uint32_t*/
#include <stdlib.h> /*qsort */
#include <assert.h> /* assert() */
#include <stdio.h>


int IsBits2_6_On(unsigned char cc);
int Is_2AND6_On(unsigned char cc);
int Is_2_or_6_On(unsigned char cc);
int Is_2or6_On(unsigned char cc);
void Swap3_5(unsigned char *cc);
void SwapInt(int *a, int *b);
void SwapIntPtr(int **a, int **b);
void VoidSwap(void **p1, void **p2);
int *OneDArr(int *, size_t size);



int main(void)
{

    int *test = NULL;
    size_t size = 6;
    unsigned char threefour = 34;
    unsigned char threeseven = 0;
    test = OneDArr(test, size);
    assert (NULL != test);
   
    (IsBits2_6_On(threefour) == 1)? printf("in #%d, bits 2 && 6 are ON!\n",threefour): 
                                                    printf("in #%d, bits 2 && 6 are OFF!\n",threefour);
    

  

    return 0;
}

int IsBits2_6_On(unsigned char cc)
{
    return ( (cc >> 1) & (cc >> 5)) & 1;
}

int Is_2_or_6_On(unsigned char cc)
{
     return ( (cc >> 1) | (cc >> 5)) & 1;
}

int Is_2or6_On(unsigned char cc)
{
    return ( (2 == (cc & 2)) || (32 == (cc & 32)) );
}

int Is_2AND6_On(unsigned char cc)
{
    return ( (34 == (cc & 34))  );
}


void Swap3_5(unsigned char *cc)
{
    unsigned char temp = ((*cc >> 2)^(*cc >> 4)) &1;
    *cc ^= ( (temp << 2) | (temp << 4));
}


void SwapInt(int *a, int *b)
{
    assert(NULL != a);
    assert(NULL != b);
    assert (a != b);

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void SwapIntPtr(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}

void VoidSwap(void **p1, void **p2)
{
    void *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int *OneDArr(int *ar, size_t size)
{
    int *arr = NULL;
    size_t idx = size;
    ar = (int *)malloc(size * sizeof(int));
    if (NULL == ar)
        return NULL;
    
    arr = ar;

    for(idx = 0; idx < size; ++idx)
    {
        arr[idx] = idx * size;
        printf("%d ",arr[idx]);
    }
    printf("\n");
    free(arr);
    arr = NULL;
    return ar;
}

