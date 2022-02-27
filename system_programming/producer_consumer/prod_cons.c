/***********************************
 * Consumer&Producer - Source File *
 * Developer: Tanya                *
 *          Feb 25, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLEN (4096)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)
typedef enum locks
{
    PRODUCER = 0,
    DIRECTOR
}locks_t;

static int spinlock = PRODUCER;
static int *p_lock = &spinlock;
static char buffer[MAXLEN] = {0};

void *Producer(void *arg);
void *Consumer(void *arg);

int main(void )
{
    pthread_t prod_thr = 0, cons_thr = 0;

    int prod_id = pthread_create(&prod_thr, NULL, &Producer, NULL);
    int cons_id = pthread_create(&cons_thr, NULL, &Consumer, NULL);
    
    pthread_join(prod_thr, NULL);
    pthread_join(cons_thr, NULL);

    return 0;
}


void *Producer(void *arg)
{
    (void)arg;
    while(1)
    {
        if(PRODUCER == spinlock)
        {
            fgets(buffer, MAXLEN, stdin);
            buffer[sizeof(buffer)] = '\0';
            atomic_compare_and_swap(p_lock, PRODUCER, DIRECTOR);
            spinlock = DIRECTOR;
        } 
    }
    

}

void *Consumer(void *arg)
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
    }
}
        