/***********************************
 * 100k threads - Source File      *
 * Developer: Tanya                *
 *          Feb 23, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/
#include <stdio.h> /* printf*/
#include <stdlib.h>
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <time.h> /* time*/

#define STOP (32660)
#define TH_ARR_SIZE (100000)
#define NEW_STOP (10000)
#define HUGE_NUM (1111111111ul)
#define SUCCESS (0)

int counter_g = 0;
size_t thread_arr[TH_ARR_SIZE] = {0};
pthread_mutex_t mutexi = PTHREAD_MUTEX_INITIALIZER;



void Ex1_2(void);
void Ex3(void);
void Ex4(void);
static void *ThreadDivFunc(void *);
static void *ThreadFunc(void *);

void CheckArr(size_t);
void SumOfDivs(void);

void *_div_func(void *val);





int main(void)
{
  
    Ex1_2();
    Ex3();
    Ex4();

  SumOfDivs();
   
    return 0;
}

static void *ThreadFunc(void *dummyPtr)
{
    pthread_mutex_lock(&mutexi);
    thread_arr[counter_g] = counter_g;
    ++counter_g;
    pthread_mutex_unlock(&mutexi);
    
    return dummyPtr;
}


void Ex1_2(void)
{
    pthread_t thread_id[STOP] = {0};
    clock_t start = clock();
    size_t idx = 0;

    for (idx = 0; idx < STOP; ++idx)
    {
        while(SUCCESS != pthread_create(&thread_id[idx], NULL, &ThreadFunc, NULL ));
        
    }

    for (idx = 0; idx < STOP; ++idx)
    {
        
        pthread_join(thread_id[idx], NULL );
    }
    
    printf("ex1_2 final counter value: %d\n", counter_g);
   
    
    printf("The process took %ld clocks\n", (clock() - start)/CLOCKS_PER_SEC);
    CheckArr(STOP);
    
}
void Ex3(void)
{
    int idx = 0;
    pthread_t thread_id[TH_ARR_SIZE] = {0};
    clock_t start = clock();
    counter_g = 0;

    for (;idx < TH_ARR_SIZE; ++idx)
    {
        while(SUCCESS != pthread_create(&thread_id[idx], NULL, ThreadFunc, NULL ));
        pthread_detach(thread_id[idx]);
    }

    printf("\nex3: final counter value: %d\n", counter_g);
    printf("The process took %ld clocks\n", (clock() - start)/CLOCKS_PER_SEC);
    CheckArr(TH_ARR_SIZE); 
  
}


static void *ThreadDivFunc(void *val)
{
    size_t num = (size_t)val;
    size_t idx = 0;
    size_t range = HUGE_NUM / NEW_STOP;
    size_t sum_of_divs = 0;

    for (idx = num; idx < (num + range); ++idx)
    {   
        if (0 == (HUGE_NUM % idx))
        {
            sum_of_divs += idx;
            printf("divisor of %ld is %ld\n",HUGE_NUM, idx);
        }

    }
    pthread_exit((void *)sum_of_divs);
}


void Ex4(void)
{
    size_t idx = 0;
    clock_t start = clock();
    size_t num = 1;
    size_t sum_of_divisors = 0;
    pthread_t thread_id[NEW_STOP] = {0};
    size_t range = HUGE_NUM / NEW_STOP + 1; 

    for (idx = 0; idx < NEW_STOP; ++idx)
    {
        while(SUCCESS != pthread_create(&thread_id[idx], NULL, &ThreadDivFunc, (void *)num));
        num += range;
    }

    for (idx = 0; idx < NEW_STOP; ++idx)
    {
        pthread_join(thread_id[idx], (void *)&num);
        sum_of_divisors += num;
    }
   
    printf("\nex4, sum of divisors: %ld\n", sum_of_divisors);
    printf("The process took %ld clocks\n", (clock() - start)/CLOCKS_PER_SEC);
    
}





/*single thread sum of all dividors */
void SumOfDivs(void)
{
    clock_t start = clock();
    size_t idx = 0;
    size_t sum_of_divs = 0;
    for (idx = 1; idx <= HUGE_NUM; ++idx)
    {
        if(0 == HUGE_NUM % idx)
        {
            sum_of_divs += idx;
            /*printf("divisor of %ld is %ld\n",HUGE_NUM, idx);*/
        }
    }
    
    printf("\nex4 single thread: %ld \n", sum_of_divs);
    printf("The process took %ld clocks\n", (clock() - start)/CLOCKS_PER_SEC);
}





void CheckArr(size_t length)
{
    size_t i = 0;
    for(; i < length; ++i)
    {
        assert(thread_arr[i] == i);
    }
}


void *_div_func(void *val)
{
    int sum_of_divs = 0;

    if(HUGE_NUM % counter_g  == 0)
    {
        sum_of_divs += counter_g;
        
    }
    ++counter_g;
 
    return val;

}