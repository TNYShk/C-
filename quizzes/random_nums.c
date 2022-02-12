
#include <stddef.h> /* size_t*/
#include <stdio.h> /*print */
#include <time.h>
#include <string.h>


#define RANGE (100)

size_t Random();


int main(void)
{
    int i = 0;
    for(i=0; i < 200; ++i)
    {
         printf(" %ld, ", Random());
         if(i %10 == 0)
            printf("\n");
    }
   printf("\n");
    return 0;
}


size_t Random()
{
    static int LUT[RANGE] = {0};
    static size_t counter = 0;
    size_t ans = rand() % RANGE;
    
    if (counter == RANGE)
    {
        counter = 0;
        memset(LUT,0,sizeof(int)* RANGE);
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

    ra


}

static int *InitLut(int *, size_t len)
{

}