/***********************************
 * ex4. Ping Pong - Source File    *
 * Developer: Tanya                *
 *          Feb 21, 2022           *
 *                                 *
 * Reviewer:  Ofer                 *
************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define STOP (100000)

void *thread_func(void *);
void PrintArr(void);
void CheckArr();
int counter_g = 0;
int thread_arr[STOP] = {0};

int main (void)
{
    pthread_t thread_id[STOP];
    int i = 0;

    for (;i< STOP; ++i)
    {
        pthread_create(&thread_id[i], NULL, thread_func, NULL );
        pthread_join(thread_id[i], NULL );
    }
 
  

    printf("final counter value: %d\n", counter_g);
  
    CheckArr();
    return 0;
}

void *thread_func(void *dummyPtr)
{
    /*printf("Thread number %ld\n", pthread_self());*/
    thread_arr[counter_g] = counter_g;
    ++counter_g;
 
}

void PrintArr(void)
{
    /*int i = 0;
    for(; i< STOP; ++i)
    {
        printf("%d ,",thread_arr[i] );
    }*/
    
}

void CheckArr()
{
    int i = 0;
    for(; i< STOP; ++i)
    {
        assert(thread_arr[i] == i);
    }
}