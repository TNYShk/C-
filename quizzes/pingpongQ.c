/***********************************
 * Ping Pong quiz - Source File      *
 * Developer: Tanya                *
 *          Feb 23, 2022           *
 *                                 *
 * Reviewer: Zohar                 *
************************************/
#include <stdio.h> /* printf*/
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <time.h> /* time*/
#include <omp.h> /* pragma openMP */

pthread_mutex_t mutexi = PTHREAD_MUTEX_INITIALIZER;
int flag_g = 1;
pthread_t threads[2] = {0};




static void *ThreadFunc(void *dummyPtr);
void DoPong(void);
void DoPing(void);





static void *ThreadFunc(void *dummyPtr)
{
    pthread_mutex_lock(&mutexi);
    flag_g = 0;
    pthread_mutex_unlock(&mutexi);
    return dummyPtr;
}

void DoPing(void)
{
    
   while(flag_g)
   {
        printf("PING!\n");
        while(0 != pthread_create(&threads[!flag_g], NULL, &ThreadFunc, NULL )); 
        pthread_join(threads[!flag_g], NULL );

   }
}

void DoPong(void)
{
    flag_g = 1;
    while(flag_g)
    {
        printf("PONG!\n");
        while(0 != pthread_create(&threads[flag_g], NULL, &ThreadFunc, NULL ));  
        pthread_join(threads[flag_g], NULL );
    }
}


int main(void)
{
    DoPing();
    DoPong();
    return 0;
}