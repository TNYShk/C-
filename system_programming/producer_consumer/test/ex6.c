/***********************************
 * Consumer&Producer - Source File *
 * Developer: Tanya                *
 *          Feb 28, 2022           *
 *                                 *
 * Reviewer: Zohar                 *
************************************/
#include <pthread.h> /* threads */
#include <stdio.h>   /* fgets, perror */
#include <stdlib.h>  /* size_t, NULL */
#include <string.h>  /* memset */
#include <unistd.h>  /* perror */
#include <errno.h>   /* errno */
#include <semaphore.h> /* semaphore */
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */

#define WORD_SIZE (sizeof(size_t))
#define MAXLEN (4096)
#define FAIL (-1)
#define SUCCESS (0)
#define THREADS (8)
#define ON (1)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)
#define atomic_sync_fetch_and(destptr, flag) __sync_fetch_and_and(destptr, flag)
#define atomic_sync_fetch_or(destptr, flag) __sync_fetch_and_or(destptr, flag)
#define atomic_sync_fetch_xor(destptr, flag) __sync_fetch_and_xor(destptr, flag)
#define atomic_sync_add_fetch(destptr, incrby) __sync_add_and_fetch(destptr, incrby)

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0) /*error handling macro */

#include "dll.h"
#include "cir_buffer.h"


typedef struct sync_mech
{
    pthread_mutex_t mutex;
    pthread_mutex_t cond_mutex;
    pthread_cond_t cond;
    sem_t *prod_sem;
    sem_t *cons_sem;
    int flag;

}sync_mech_t;


typedef enum locks
{
    PRODUCER = 0,
    DIRECTOR
}locks_t;

sync_mech_t syncro = {0};


void Ex6();
static void *Producer_Ex6(void *something);
static void *Consumers_Ex6(void *something);
static void DoSomething(int something);



int main(void)
{
  
    Ex6();
    return 0;
}


void Ex6(void)
{
    size_t idx6 = 0;
    pthread_t producer,consumer[THREADS] = {0};
    
    syncro.mutex = PTHREAD_MUTEX_INITIALIZER;

    if(FAIL == sem_init(syncro->prod_sem, 0, 1))
    {
        errExit("sem_init");
    }
    

    while(SUCCESS != pthread_create(&producer, NULL, &Producer_Ex6, NULL));
    for(; idx6 < THREADS; ++idx6)
    {
        while(SUCCESS != pthread_create(&consumer[idx6], NULL, &Consumers_Ex6, NULL));
    }
  
    pthread_join(producer, NULL);
    for(idx6 = 0; idx6 < THREADS; ++ idx6)
    {
        pthread_join(consumer[idx6], NULL);
    }
    
    sem_destroy(syncro->prod_sem);
  
    pthread_mutex_destroy(&syncro.mutex);
}


static void DoSomething(int something)
{
    sem_wait(&semy_ex6);
    pthread_mutex_lock(&condition_mutex);
        message = something;
        atomic_sync_fetch_or(&is_consumed, 1);  /* is_consumed = 1;*/
        pthread_cond_broadcast(&condition_cond);
    pthread_mutex_unlock(&condition_mutex);
}



static void *Producer_Ex6(void *something)
{
    (void)something;
    while(count_g < THREADS)
    {
        sem_wait(&semy_ex6);
        pthread_mutex_lock(&condition_mutex);
        atomic_sync_add_fetch(&count_g, 1ul); /*++count_g */
              is_consumed = 1;                /*  atomic_sync_fetch_or(&is_consumed, 1);*/
            pthread_cond_signal(&condition_cond);
        pthread_mutex_unlock(&condition_mutex);

        sleep(0);
    }
    DoSomething(FAIL);

    return NULL;
}

static void *Consumers_Ex6(void *something)
{
   
   while(count_g)
   {
      pthread_mutex_lock(&condition_mutex);
        
        while(!is_consumed)
        {
            pthread_cond_wait( &condition_cond, &condition_mutex);
        }
         atomic_sync_add_fetch(&received, 1ul); /*++received; */

        if (message == FAIL)
        {
            pthread_mutex_unlock(&condition_mutex); 
            return NULL;
        }
        printf("consumers: %d\n", count_g);
        if(THREADS == received)
        {
            received = 0;
            is_consumed = 0;
            sem_post(&semy_ex6);
        }
        pthread_mutex_unlock(&condition_mutex);
        sleep(0);
    }
    if(count_g == THREADS)
    {
        return NULL;
    }  
    return something;  
}