/***********************************
 * Thread_sync quiz - Source File *
 * Developer: Tanya                *
 *          Mar 01, 2022           *
 *                                 *
 * Reviewer:                  *
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
#include <assert.h>

#define SUCCESS (0)
pthread_mutex_t mutexi = PTHREAD_MUTEX_INITIALIZER;

void *get_stuff(void *);

int main(void)
{
	pthread_t quiz = 0, quiz2 = 0;
	void *ptr = NULL;
	
	
		while (SUCCESS != pthread_create(&quiz, NULL, &get_stuff, ptr));	
		while (SUCCESS != pthread_create(&quiz2, NULL, &get_stuff, ptr));	
	
	pthread_join(quiz,&ptr);
	pthread_join(quiz2,&ptr);
	
	assert(NULL != ptr);
	if(NULL != ptr)
	{
		free(ptr);
	}
	

	pthread_mutex_destroy(&mutexi);

	return 0;
}


void *get_stuff(void *s)
{
	static void *ptr = NULL;

	if(NULL == ptr)
	{
		write(STDOUT_FILENO, "there!\n", strlen("there!  "));
		pthread_mutex_lock(&mutexi);

		if (NULL == ptr)
		{
			ptr = (void *)malloc(sizeof(void *));
			write(STDOUT_FILENO, "here??\n", strlen("here??  "));
		}
		pthread_mutex_unlock(&mutexi);
	}
	
	return ptr;
}

