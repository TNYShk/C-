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
#define STOP (32000)
#define NEW_STOP (10000)
#define HUGE_NUM (1111111111)



void Ex1_2();
void Ex3();
void *thread_func(void *);
void PrintArr(void);
void CheckArr();
void Ex4(void);
static void *thread_div_func(void *);
void Sum_of(void);
void *_div_func(void *val);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter_g = 0;
int thread_arr[STOP] = {0};
int divisors[STOP] = {0};


int main (void)
{
  
 Ex4();
  Sum_of();
   /*
   Sum_of();
    
    Ex3();
    
      Ex1_2();
     
    */
    return 0;
}

void *thread_func(void *dummyPtr)
{
    /*printf("Thread number %ld\n", pthread_self());*/
    /*pthread_mutex_lock( &mutex1 );*/
    thread_arr[counter_g] = counter_g;
    ++counter_g;

    /*pthread_mutex_unlock( &mutex1 );
*/
    return dummyPtr;

}

void PrintArr(void)
{
    int i = 0;
    for(; i < 36; ++i)
    {
        printf("%d ,",thread_arr[i] );
    }
    
}

void CheckArr()
{
    int i = 0;
    for(; i < STOP; ++i)
    {
        assert(thread_arr[i] == i);
    }
}
void Ex1_2(void)
{
   pthread_t thread_id[STOP];
    int i = 0;

    for (;i < STOP; ++i)
    {
        while(0 != pthread_create(&thread_id[i], NULL, thread_func, NULL ));
        pthread_join(thread_id[i], NULL );
    }
    
 

    printf("ex1_2 final counter value: %d\n", counter_g);
    /*sleep(10);*/
    
}
void Ex3(void)
{
    int i = 0;
    pthread_t thread_id[STOP] = {0};
    counter_g = 0;

    for (;i < STOP; ++i)
    {
        while(0 != pthread_create(&thread_id[i], NULL, thread_func, NULL ));

        pthread_detach(thread_id[i]);
    }
    printf("ex3: final counter value: %d\n", counter_g);
 
    /*CheckArr(); 
  */
}


static void *thread_div_func(void *val)
{
    size_t num = (size_t )val;
    size_t i = 0;
    size_t range = HUGE_NUM / NEW_STOP;
    size_t sum_of_divs = 0;

    for (i = num; i < (num + range); ++i)
    {   
        if (0 == (HUGE_NUM % i))
        {
            sum_of_divs += i;
        }
    }
    pthread_exit((void *)sum_of_divs);
}


void Ex4(void)
{
    int i = 0;
    size_t num = 1;
    size_t sum_of_divisors = 0;
    pthread_t thread_id[NEW_STOP] = {0};
    size_t range = HUGE_NUM / NEW_STOP + 1; 

    for (i = 0; i < NEW_STOP; ++i)
    {
        while(0 != pthread_create(&thread_id[i], NULL, &thread_div_func, (void *)num));
        num += range;
    }

    for (i = 0; i < NEW_STOP; ++i)
    {
        pthread_join(thread_id[i], (void *)&num);
        sum_of_divisors += num;
    }
    printf("ex4: %ld\n", sum_of_divisors);

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

void Sum_of(void)
{
    size_t i = 0;
    size_t sum_of_divs = 0;
    for (i = 1; i <= HUGE_NUM; ++i)
    {
        if(0 == HUGE_NUM % i)
        {
            sum_of_divs += i;
        }
    }
    
    printf("ex4 non threaded: %ld\n", sum_of_divs);
  
}