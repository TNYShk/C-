/***********************************
 * Consumer&Producer - Source File *
 * Developer: Tanya                *
 *          Feb 25, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/
#include <pthread.h> /* thread*/
#include <stdio.h> /* fgets, perror*/
#include <stdlib.h> /* NULL */
#include <string.h> /* memset*/
#include <unistd.h> /* perror*/

#include <errno.h>    /* errno */
#define MAXLEN (4096)
#define FAIL (-1)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0) /*error handling macro */

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

int main(void)
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
        