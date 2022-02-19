/* 06/02/2022 quiz
create a function: size_t GetNonRepeatingRandom()

1. each times the function is called, it returns a RANDOM number between 0-99.
2. the numbers would NEVER REPEAT themselves for the first 100 function calls.
3. after the function has been called 100 times, it is "reset" and a new cycle of non repeating random numbers start.

4. you should use the C rand() function. you may read the man to learn how to use it if you don't.

*/



#include <assert.h>
#include <stddef.h> /* size_t*/
#include <stdio.h> /*print */
#include <time.h>
#include <string.h>
#include <stdlib.h> /* rand(), srand*/


#define RANGE (10)

size_t Random();
static void InitLut(size_t *array);
static void Swap(size_t *a, size_t *b);
size_t GetRandomNonRepeatNums();

int main(void)
{
    size_t i = 0;
    size_t LUT[RANGE] = {0};
    InitLut(LUT);

    for(; i < RANGE; ++i)
    {
        printf("%ld ", LUT[i]);
        if((i != 0) && (i %10 == 0))
            printf("\n");
    }

    printf("\n\n");
     printf("ver 1:\n");
    for(i = 1; i <= 100; ++i)
    {
         printf("%ld ", Random());
         if(i %10 == 0)
            printf("\n");
    }
    printf("\n\n\n");
    printf("ver 2:\n");
    for(i = 1; i <= 100; ++i)
    {
         printf("%ld ", GetRandomNonRepeatNums());
         if(i %10 == 0)
            printf("\n");
    }
    printf("\n\n\n");



    return 0;
}


size_t Random()
{
    static int LUT[RANGE] = {0};
    static size_t counter = 1;
    
    if (counter % RANGE == 0)
    {
        counter = 1;
        memset(LUT, 0, sizeof(int) * RANGE);
        srand(time(0));
    }
    else
    {
        size_t ans = rand() % RANGE;
        if(LUT[ans] != 1)
        {
            ++counter;
            LUT[ans] = 1;
            
            return ans;
        }
    }
    return Random();
}

size_t GetRandomNonRepeatNums()
{
    static size_t random[RANGE] = {0};
    static size_t count = 0;
    size_t ans = 0;
    size_t idx = 0;

    if (count == 0)
    {
        count = RANGE;
        InitLut(random);
        
    }
    
    idx = rand() % count;
    ans = random[idx];
     --count;
    Swap(&random[idx], &random[count]);
   
        
    return ans;
}
    


    




static void InitLut(size_t *array)
{
    size_t idx = 0;
    for(; idx < RANGE; ++idx)
    {
        *(array + idx) = idx;
    }
}

static void Swap(size_t *a, size_t *b)
{
    size_t temp = *b;
    *b = *a;
    *a = temp;

}