
#include <stddef.h> /* size_t*/
#include <stdio.h> /*print */
#include <time.h>
#include <string.h>

#define ASCI (256)
#define RANGE (100)


size_t Random()
{
    static int LUT[RANGE] = {0};
    static size_t counter = 0;
    size_t ans = rand()%100;
    
    if (counter == 100)
    {
        counter = 0;
        memset(LUT,0,sizeof(int)* RANGE);
        srand(time(0));
    }
    else
    {
        size_t ans = rand()%100;
        if(LUT[ans]!= 1)
        {
            ++counter;
            LUT[ans] = 1;
            return ans;
        }
    }
    return Random();
}

int main(void)
{
    int i = 0;
    for(i=0; i<200; ++i)
    {
         printf("randon num: %ld\n", Random());
         if(i == 100)
            printf("\n");

    }
   
    return 0;
}


