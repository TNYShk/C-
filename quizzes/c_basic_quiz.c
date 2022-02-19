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
#include <string.h>

int IsBits2_6_On(unsigned char cc);
int Is_2AND6_On(unsigned char cc);
int Is_2_or_6_On(unsigned char cc);
int Is_2or6_On(unsigned char cc);
void Swap3_5(unsigned char *cc);
void Swap3AND5(unsigned char *cc);
void SwapInt(int *a, int *b);
void SwapIntPtr(int **a, int **b);
void VoidSwap(void **p1, void **p2);

int *CreateArray(size_t length);
void ResetArray(int *array, size_t length);


int main(void)
{

    int *test = NULL;
    int *ptr = NULL;
    unsigned char threefour = 34;
    unsigned char threeseven = 4;
   
    test = CreateArray(6);
    assert(NULL != test);
    ptr = test;

    (*(int *)&ptr[1]) = 26;
    printf("created array, 2nd elem is %d\n", (*(int *)&test[1]));

    ResetArray(test, 6);
    printf("reseted array, 2nd elem is %d\n", test[1]);
   
    printf("v1: before swap its %d\n",threeseven);
    Swap3_5(&threeseven);
    printf("v2: after swap its %d\n", threeseven);

    printf("v2: before swap its %d\n",threeseven);
    Swap3AND5(&threeseven);
    printf("v2: after swap its %d\n", threeseven);

    (Is_2AND6_On(threefour) == 1)? printf("\nv1: in #%d, bits 2 && 6 are ON!\n",threefour): 
                                                    printf("v1: in #%d, bits 2 && 6 are OFF!\n",threefour);

    (IsBits2_6_On(threefour) == 1)? printf("v2: in #%d, bits 2 && 6 are ON!\n",threefour): 
                                                    printf("v2: in #%d, bits 2 && 6 are OFF!\n",threefour);


    (Is_2_or_6_On(threeseven) == 1)? printf("v1: in #%d, bits 2 OR 6 are ON!\n",threeseven): 
                                                    printf("v1: in #%d, bits 2 OR 6 are OFF!\n",threeseven);

    (Is_2or6_On(threeseven) == 1)? printf("v2: in #%d, bits 2 OR 6 are ON!\n",threeseven): 
                                                    printf("v2: in #%d, bits 2 OR 6 are OFF!\n",threeseven);                                                
    

    return 0;
}



int IsBits2_6_On(unsigned char cc)
{
    return ( (cc >> 1) & (cc >> 5)) & 1;
}
int Is_2AND6_On(unsigned char cc)
{
    return  (34 == (cc & 34));
}

int Is_2_or_6_On(unsigned char cc)
{
     return ( (cc >> 1) | (cc >> 5)) & 1;
}

int Is_2or6_On(unsigned char cc)
{
    return ( (2 == (cc & 2)) || (32 == (cc & 32)) );
}


void Swap3_5(unsigned char *cc)
{
    unsigned char temp = ((*cc >> 2)^(*cc >> 4))&1;
    *cc ^=  (temp << 2) | (temp << 4);
}

void Swap3AND5(unsigned char *cc)
{
    char d = (*cc & 20);
    switch(d)
    {
        case(20):
            break;
        case(4):
        case(16):
            *cc^=20;
    }
    
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

int *CreateArray(size_t length)
{
    int *temp  = NULL;
    int *array = (int *)calloc(length, sizeof(int));
    if (NULL == array)
        return NULL;

    temp = array;
   
    free(temp);
    return array; 

}

void ResetArray(int *array, size_t length)
{
    memset(array, 0, length * sizeof(int) );

}

