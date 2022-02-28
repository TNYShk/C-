/***********************************
 * Consumer&Producer - Source File *
 * Developer: Tanya                *
 *          Feb 25, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/
#include <pthread.h> /* thread */
#include <stdio.h>  /* fgets, perror */
#include <stdlib.h> /* size_t, NULL */
#include <string.h> /* memset */
#include <unistd.h> /* perror */
#include <errno.h>  /* errno */
#include <semaphore.h> 
#include <fcntl.h>  /* For O_* constants */
#include <sys/stat.h> /* For mode constants */


#define MAXLEN (4096)
#define FAIL (-1)
#define SUCCESS (0)
#define THREADS (5)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)
#define atomic_sync_fetch_and(destptr, flag) __sync_fetch_and_and(destptr, flag)
#define atomic_sync_fetch_or(destptr, flag) __sync_fetch_and_or(destptr, flag)
#define atomic_sync_fetch_xor(destptr, flag) __sync_fetch_and_xor(destptr, flag)
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0) /*error handling macro */

#include "sll.h"
#include "cir_buffer.h"

typedef enum locks
{
    PRODUCER = 0,
    DIRECTOR
}locks_t;

/* ex1 */
volatile int spinlock = PRODUCER;


static char buffer[MAXLEN] = {0};
/* ex2 -3*/
pthread_mutex_t mutexi = PTHREAD_MUTEX_INITIALIZER;
 size_t idx_g = 0;
static sem_t ex3_sem = {0};
static slist_t *sll_prod_cons = NULL;

static int isEOF_g = 0;

void Ex1();
static void *Producer(void *arg);
static void *Consumer(void *arg);

void Ex2();
static void *ThreadProd2(void *something);
static void *ThreadCons2(void *something);

void Ex3();
static void *ThreadProd(void *something);
static void *ThreadCons(void *something);


int main(void)
{
    
    Ex2();
    return 0;
}


void Ex3(void)
{
    pthread_t producer[5] = {0}, consumer[5] = {0};
    sll_prod_cons = SListCreate();

    pthread_mutex_init(&mutexi, NULL);
    sem_init(&ex3_sem, 0, 0);

    for(idx_g = 0; idx_g < 5; ++idx_g )
    {
        while(SUCCESS != pthread_create(&producer[idx_g], NULL, &ThreadProd, sll_prod_cons )); 
        while(SUCCESS != pthread_create(&consumer[idx_g], NULL, &ThreadCons, sll_prod_cons ));  
    }
    for(idx_g = 0; idx_g < 5; ++idx_g )
    {
        pthread_join(producer[idx_g], NULL);
        pthread_join(consumer[idx_g], NULL);
    }

    pthread_mutex_destroy(&mutexi);
    sem_destroy(&ex3_sem);
    SListDestroy(sll_prod_cons);
}


static void *ThreadProd(void *something)
{
    return NULL;
}
static void *ThreadCons(void *something)
{
    return NULL;
}


void Ex2(void)
{
    pthread_t producer[THREADS] = {0}, consumer[5] = {0};
    size_t idx = 0;
    sll_prod_cons = SListCreate();

    pthread_mutex_init(&mutexi, NULL);
   

    for(idx = 0; idx < THREADS; ++idx )
    {
        while(SUCCESS != pthread_create(&producer[idx], NULL, &ThreadProd2, &idx_g )); 
       
    }
    for(idx = 0; idx < THREADS; ++idx )
    {
       
        while(SUCCESS != pthread_create(&consumer[idx], NULL, &ThreadCons2, NULL ));  
    }
    for(idx = 0; idx < THREADS; ++idx )
    {
        pthread_join(producer[idx], NULL);
        pthread_join(consumer[idx], NULL);
    }
   
    SListDestroy(sll_prod_cons);
    pthread_mutex_destroy(&mutexi);
}

static void *ThreadProd2(void *something)
{
    pthread_mutex_lock(&mutexi);
        SListInsertBefore(SListEnd(sll_prod_cons), &something);
        ++idx_g;
    pthread_mutex_unlock(&mutexi);

    return something;
}

static void *ThreadCons2(void *something)
{
    void *reader = NULL;
    while(!SListIsEmpty(sll_prod_cons))
    {
        pthread_mutex_lock(&mutexi);
        reader = SListGetData((slist_iter_t)sll_prod_cons);
        if(NULL == reader)
        {
            sleep(0);
            return;
        }
        printf("read: %ld\n", *(size_t *)reader);
        SListRemove(SListBegin(sll_prod_cons));
        pthread_mutex_unlock(&mutexi);
     }

    return something;
}



void Ex1(void)
{
    pthread_t prod_thr = 0, cons_thr = 0;
    int prod_id = 0,cons_id = 0;

    prod_id = pthread_create(&prod_thr, NULL, &Producer, NULL);
    if(FAIL == prod_id)
        errExit("pthread_create");

    cons_id = pthread_create(&cons_thr, NULL, &Consumer, NULL);
    if(FAIL == cons_id)
        errExit("pthread_create");
    
    pthread_join(prod_thr, NULL);
    pthread_join(cons_thr, NULL);
}

static void *Producer(void *arg)
{
    (void)arg;
    while(1)
    {
        if(PRODUCER == spinlock)
        {
            fgets(buffer, MAXLEN, stdin);
            
            atomic_compare_and_swap(&spinlock, PRODUCER, DIRECTOR);
        } 
        else
        {
            sleep(0);
        }
    }
}

static void *Consumer(void *arg)
{
    (void)arg;
    while(1)
    {
        if(DIRECTOR == spinlock)
        {
            write(STDOUT_FILENO, "string is:\n", 10);
            write(STDOUT_FILENO, buffer, MAXLEN);
            memset(buffer, 0 ,MAXLEN);
            atomic_compare_and_swap(&spinlock, DIRECTOR, PRODUCER);
        }
        else
        {
            sleep(0);
        }
    }
}
        