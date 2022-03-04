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

#include "dll.h" /* ds for ex 2-3 */
#include "cir_buffer.h" /* ds for ex 4-5 */



typedef enum locks
{
    PRODUCER = 0,
    CONSUMER
}locks_t;

/* ex1 */
volatile int spinlock = PRODUCER;
static char buffer[MAXLEN] = {0};

/* ex2 -3*/
pthread_mutex_t mutexi = PTHREAD_MUTEX_INITIALIZER;
size_t idx_g = 0;
static sem_t ex3_sem = {0};
static dlist_t *dll_ex2_3 = NULL;
int isEOF_g = 0;

/*ex 4-5 */
pthread_mutex_t mutexii = PTHREAD_MUTEX_INITIALIZER;
static sem_t prod_ex4_5 = {0};
static sem_t consm_ex4_5 = {0};
static cbuffer_t *cbuffy = NULL;


/* ex6*/
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;
static sem_t semy_ex6 = {0};
static int message = 0;
static size_t received = 0;
static int is_consumed = 0;
int count_g = 0;


void Ex1();
static void *Producer(void *arg);
static void *Consumer(void *arg);

void Ex2();
static void *ThreadProd2(void *something);
static void *ThreadCons2(void *something);

void Ex3();
static void *ThreadProd3(void *something);
static void *ThreadCons3(void *something);

void Ex4();
static void *ThreadProd4(void *something);
static void *ThreadCons4(void *something);

void Ex5();
static void *ThreadProd5(void *something);
static void *ThreadCons5(void *something);

void Ex6();
static void *Producer_Ex6(void *something);
static void *Consumers_Ex6(void *something);
static void DoSomething(int something);



int main(void)
{
    /*
    Ex1();
    Ex2();
    Ex3();
    Ex4();
    Ex5();
    */
    /*Choose your poison: */
    printf("ex4:\n");
    Ex4();
    printf("ex5:\n");
    Ex5();
    return 0;
}


void Ex6(void)
{
    size_t idx6 = 0;
    pthread_t producer,consumer[THREADS] = {0};
    
    if(FAIL == sem_init(&semy_ex6, 0, 1))
    {
        errExit("sem_init");
    }

    while(SUCCESS != pthread_create(&producer, NULL, &Producer_Ex6, NULL));
    for(; idx6 < THREADS; ++idx6)
    {
        while(SUCCESS != pthread_create(&consumer[idx6], NULL, &Consumers_Ex6, NULL));
    }
  
    pthread_join( producer, NULL);
    for(idx6 = 0; idx6 < THREADS; ++ idx6)
    {
        pthread_join(consumer[idx6], NULL);
    }
    
    sem_destroy(&semy_ex6);
    pthread_mutex_destroy(&condition_mutex);
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

    return something;
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



void Ex5(void)
{
    pthread_t producer[THREADS] = {0}, consumer[THREADS] = {0};
    size_t idx5 = 0;

    if(FAIL == sem_init(&prod_ex4_5, 0, THREADS))
    {
        errExit("prod_sem_init");
    }
    if(FAIL == sem_init(&consm_ex4_5, 0, 0))
    {
        errExit("sem_init");
    }

    cbuffy = CBuffCreate(WORD_SIZE * THREADS);

    for(idx5 = 0; idx5 < THREADS; ++idx5 )
    {
        while(SUCCESS != pthread_create(&producer[idx5], NULL, &ThreadProd5, (void *)idx5)); 
    }
    for(idx5 = 0; idx5 < THREADS; ++idx5 )
    {
        while(SUCCESS != pthread_create(&consumer[idx5], NULL, &ThreadCons5, (void *)idx5));  
    }

    for(idx5 = 0; idx5 < THREADS; ++idx5 )
    {
        pthread_join(producer[idx5], NULL);
    }
    for(idx5 = 0; idx5 < THREADS; ++idx5 )
    {
        pthread_join(consumer[idx5], NULL);
    }

    pthread_mutex_destroy(&mutexi);
    pthread_mutex_destroy(&mutexii);
    sem_destroy(&prod_ex4_5);
    sem_destroy(&consm_ex4_5);
    CBuffDestroy(cbuffy);
}

static void *ThreadProd5(void *something)
{
    sem_wait(&prod_ex4_5);

    pthread_mutex_lock(&mutexi);

    CBuffWrite(cbuffy, &something, WORD_SIZE);
    
    pthread_mutex_unlock(&mutexi);
    
    sem_post(&consm_ex4_5);
    
    return something;

}
static void *ThreadCons5(void *something)
{ 
    size_t read_num = 0;

    sem_wait(&consm_ex4_5);

    pthread_mutex_lock(&mutexii);
    
    CBuffRead(cbuffy, &read_num, WORD_SIZE);
    printf("read : %ld\n", read_num);
    
    pthread_mutex_unlock(&mutexii);
    
    sem_post(&prod_ex4_5);
    
    return something;
}





void Ex4(void)
{
    pthread_t producer[THREADS] = {0};
    pthread_t consumer[THREADS] = {0};
    size_t idx4 = 0;
   
    if(FAIL == sem_init(&prod_ex4_5, 0, THREADS))
    {
        errExit("sem_init");
    }
    if(FAIL == sem_init(&consm_ex4_5, 0, 0))
    {
        errExit("sem_init");
    }

    cbuffy = CBuffCreate(WORD_SIZE * THREADS);

    for(idx4 = 0; idx4 < THREADS; ++idx4 )
    {
        while(SUCCESS != pthread_create(&producer[idx4], NULL, &ThreadProd4, (void *)idx4)); 
    }
    for(idx4 = 0; idx4 < THREADS; ++idx4 )
    {
        while(SUCCESS != pthread_create(&consumer[idx4], NULL, &ThreadCons4, (void *)idx4));  
    }

    for(idx4 = 0; idx4 < THREADS; ++idx4 )
    {
        pthread_join(producer[idx4], NULL);
        pthread_join(consumer[idx4], NULL);
    }
   
    pthread_mutex_destroy(&mutexi);
    sem_destroy(&prod_ex4_5);
    sem_destroy(&consm_ex4_5);
    CBuffDestroy(cbuffy);
    cbuffy = NULL;
}

static void *ThreadProd4(void *something)
{
    sem_wait(&prod_ex4_5);

    pthread_mutex_lock(&mutexi);
    CBuffWrite(cbuffy, &something, WORD_SIZE);
    pthread_mutex_unlock(&mutexi);
    
    sem_post(&consm_ex4_5);

    return NULL;

}
static void *ThreadCons4(void *something)
{ 
    size_t read_num = 0;

    sem_wait(&consm_ex4_5);

    pthread_mutex_lock(&mutexi);
    CBuffRead(cbuffy, &read_num, WORD_SIZE);
    printf("read : %ld\n", read_num);
    
    pthread_mutex_unlock(&mutexi);
    sem_post(&prod_ex4_5);
    return something;
}


void Ex3(void)
{
    pthread_t producer[THREADS] = {0}; 
    pthread_t consumer[THREADS] = {0};
    size_t idx3 = 0;

    if(FAIL == sem_init(&ex3_sem, 0, 0))
    {
        errExit("prod_sem_init");
    }

    dll_ex2_3 = DListCreate();

    for(idx3 = 0; idx3 < THREADS; ++idx3 )
    {
        while(SUCCESS != pthread_create(&producer[idx3], NULL, &ThreadProd3, NULL )); 
    }
    for(idx3 = 0; idx3 < THREADS; ++idx3 )
    {
        while(SUCCESS != pthread_create(&consumer[idx3], NULL, &ThreadCons3, NULL));  
    }

    for(idx3 = 0; idx3 < THREADS; ++idx3 )
    {
        pthread_join(producer[idx3], NULL);
        pthread_join(consumer[idx3], NULL);
    }

    DListDestroy(dll_ex2_3);
    pthread_mutex_destroy(&mutexi);
    sem_destroy(&ex3_sem);
    
}


static void *ThreadProd3(void *something)
{
    char *link_node = NULL; 
    char buffer_l[MAXLEN] = {'\0'};
    
    while (!isEOF_g)
    {
        pthread_mutex_lock(&mutexi);
        memset(buffer_l, 0 ,MAXLEN);
        if (NULL == fgets(buffer_l, MAXLEN, stdin)) 
        {
               isEOF_g = ON; /*atomic_sync_fetch_or(&isEOF_g, 1);*/
            
            pthread_mutex_unlock(&mutexi);
            sem_post(&ex3_sem);
            
            return NULL;
        }

        link_node = (char *)malloc(sizeof(buffer_l));
        if (NULL == link_node)
        {
            pthread_mutex_unlock(&mutexi);
            errExit("malloc error");
        }

        strcpy(link_node, buffer_l); 
        DListPushBack(dll_ex2_3, link_node);
        sem_post(&ex3_sem);
        pthread_mutex_unlock(&mutexi);

        sleep(0); 
    }

    return something;

}
static void *ThreadCons3(void *something)
{
    
    while (1)
    {
        char *releaser = NULL; 
        sem_wait(&ex3_sem);
        if(isEOF_g)
        {
            return NULL;
        }

        pthread_mutex_lock(&mutexi);
            releaser = (char *)DListPopFront(dll_ex2_3);
            write(STDOUT_FILENO, "consumer read: \n", strlen("consumer read  "));
            write(STDOUT_FILENO, releaser, strlen(releaser));
        pthread_mutex_unlock(&mutexi);
        
        free(releaser);
        releaser = NULL;

        sleep(0);
    }

    return something;
}



void Ex2(void)
{
    pthread_t producer[THREADS] = {0}; 
    pthread_t consumer[THREADS] = {0};
    size_t idx2 = 0;
    dll_ex2_3 = DListCreate();
   
    for(idx2 = 0; idx2 < THREADS; ++idx2 )
    {
        while(SUCCESS != pthread_create(&producer[idx2], NULL, &ThreadProd2, NULL )); 
    }
    for(idx2 = 0; idx2 < THREADS; ++idx2 )
    {
        while(SUCCESS != pthread_create(&consumer[idx2], NULL, &ThreadCons2, NULL));  
    }

    for(idx2 = 0; idx2 < THREADS; ++idx2 )
    {
        pthread_join(producer[idx2], NULL);
        pthread_join(consumer[idx2], NULL);
    }

    DListDestroy(dll_ex2_3);
    pthread_mutex_destroy(&mutexi);
}


static void *ThreadProd2(void *something)
{
   char *link_node = NULL; 
    char buffer_l[MAXLEN] = {'\0'};
    
    while (!isEOF_g)
    {
        memset(buffer_l, 0 ,MAXLEN);
        pthread_mutex_lock(&mutexi);
        if (NULL == fgets(buffer_l, MAXLEN, stdin)) 
        {
            isEOF_g = 1; /*atomic_compare_and_swap(&isEOF_g, PRODUCER, CONSUMER);*/
            pthread_mutex_unlock(&mutexi);
            return NULL;
        }
        
        link_node = (char *)malloc(sizeof(buffer_l));
        if (NULL == link_node)
        {
            pthread_mutex_unlock(&mutexi);
            errExit("malloc error");
        }
        strcpy(link_node, buffer_l); 
        DListPushBack(dll_ex2_3, link_node);
        pthread_mutex_unlock(&mutexi);
        
        sleep(0); 
    }

    return something;

}
static void *ThreadCons2(void *something)
{
    while(1)
    {
        char *releaser = NULL; 

        pthread_mutex_lock(&mutexi);
        if (!DListIsEmpty(dll_ex2_3))
        {
            releaser = DListPopFront(dll_ex2_3);
            write(STDOUT_FILENO, "consumer read: \n", strlen("consumer read  "));
            write(STDOUT_FILENO, releaser, strlen(releaser));
        }
        pthread_mutex_unlock(&mutexi);
        
        if (!releaser && isEOF_g) 
        {
            return NULL;
        }

        free(releaser);
        releaser = NULL;

        sleep(0);
    }

    return something;
}


void Ex1(void)
{
    pthread_t prod_thr = 0, cons_thr = 0;
    int prod_id = 0,cons_id = 0;

    prod_id = pthread_create(&prod_thr, NULL, &Producer, NULL);
    if(FAIL == prod_id)
    {
        errExit("pthread_create");
    }

    cons_id = pthread_create(&cons_thr, NULL, &Consumer, NULL);
    if(FAIL == cons_id)
    {
        errExit("pthread_create");
    }
    
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
            
            atomic_compare_and_swap(&spinlock, PRODUCER, CONSUMER);
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
        if(CONSUMER == spinlock)
        {
            write(STDOUT_FILENO, "string is:\n", 10);
            write(STDOUT_FILENO, buffer, MAXLEN);
            memset(buffer, 0 ,MAXLEN);
            atomic_compare_and_swap(&spinlock, CONSUMER, PRODUCER);
        }
        else
        {
            sleep(0);
        }
    }
}
        