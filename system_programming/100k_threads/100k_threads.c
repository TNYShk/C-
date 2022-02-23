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
#define STOP (100000)

void Ex1_2();
void Ex3();
void *thread_func(void *);
void PrintArr(void);
void CheckArr();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter_g = 0;
int thread_arr[STOP] = {0};

int main (void)
{
   Ex1_2();
    Ex3();
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
    for(; i< STOP; ++i)
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

    for (;i< STOP; ++i)
    {
        while(0 != pthread_create(&thread_id[i], NULL, thread_func, NULL ));
        pthread_join(thread_id[i], NULL );
    }
 
  

    printf("ex1_2 final counter value: %d\n", counter_g);
    /*sleep(10);*/
    CheckArr(); 
}
void Ex3(void)
{
    int i = 0;
    pthread_t thread_id[STOP];
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