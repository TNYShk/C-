/***********************************
 * Ping Pong quiz - Source File    *
 * Developer: Tanya                *
 *          Feb 27, 2022           *
 *                                 *                     
************************************/
#include <stdio.h> /* printf*/
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <fcntl.h>  /* O_* const.*/
#include <sys/stat.h> /* mode const. */
#include <semaphore.h> /* sem_t*/

#define SUCCESS (0)

pthread_t pingpong[2] = {0};
sem_t pingS;
sem_t pongS;


void *DoPong(void *);
void *DoPing(void *);


int main(void)
{
        size_t timer = 100;
        sem_init(&pingS, 0 ,1);
        sem_init(&pongS, 0, 0);

        while(SUCCESS != pthread_create(&pingpong[SUCCESS], NULL, &DoPing, NULL));
        while(SUCCESS != pthread_create(&pingpong[!SUCCESS], NULL, &DoPong, NULL));

        while(--timer)
        {
            sleep(0);
            pthread_detach(pingpong[SUCCESS]);
            pthread_detach(pingpong[!SUCCESS]);
        }
    
  
    return 0;
}



void *DoPing(void *something)
{
    
   while(1)
   {
        sem_wait(&pingS);
        printf("PING!\n");
        sem_post(&pongS);
   }
   return something;
}

void *DoPong(void *something)
{
    
    while(1)
    {
        sem_wait(&pongS);
        printf("PONG!\n");
        sem_post(&pingS);
        
    }
    return something;
}
