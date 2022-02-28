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
volatile int *p_lock = &spinlock;
static char buffer[MAXLEN] = {0};
/* ex2 -3*/
pthread_mutex_t mutexi = PTHREAD_MUTEX_INITIALIZER;
static size_t idx_g = 0;
static sem_t ex3_sem = {0};
slist_t *sll_prod_cons = NULL;


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
    
    Ex1();
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
    pthread_t producer[5] = {0}, consumer[5] = {0};
    sll_prod_cons = SListCreate();

    pthread_mutex_init(&mutexi, NULL);
   

    for(idx_g = 0; idx_g < 5; ++idx_g )
    {
        while(SUCCESS != pthread_create(&producer[idx_g], NULL, &ThreadProd2, sll_prod_cons )); 
        while(SUCCESS != pthread_create(&consumer[idx_g], NULL, &ThreadCons2, sll_prod_cons ));  
    }
    for(idx_g = 0; idx_g < 5; ++idx_g )
    {
        pthread_join(producer[idx_g], NULL);
        pthread_join(consumer[idx_g], NULL);
    }

    pthread_mutex_destroy(&mutexi);
   
    SListDestroy(sll_prod_cons);
}

static void *ThreadProd2(void *something)
{
    pthread_mutex_lock(&mutexi);
        fgets(buffer, MAXLEN, stdin);
        SListInsertBefore(SListEnd((slist_t*)something), &buffer);
    pthread_mutex_unlock(&mutexi);

    return NULL;
}

static void *ThreadCons2(void *something)
{
    pthread_mutex_lock(&mutexi);
    memset(buffer, 0 ,MAXLEN);
    SListRemove(SListBegin((slist_t *)something));

    pthread_mutex_unlock(&mutexi);

    return NULL;
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
            
            atomic_compare_and_swap(p_lock, PRODUCER, DIRECTOR);
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
            atomic_compare_and_swap(p_lock, DIRECTOR, PRODUCER);
        }
        else
        {
            sleep(0);
        }
    }
}
        