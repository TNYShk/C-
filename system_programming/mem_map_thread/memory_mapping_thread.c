#include <stdio.h> 	/* printf */
#include <stdlib.h>	/* malloc, free */
#include <pthread.h> /* pthread_create */
#include <unistd.h>  /* sleep */
__thread int tls0 = 0;
__thread int tls1 = 1;
int global0 = 0;
int global1 = 1;
static volatile int volti = 26;

void *Ex2(void *arg)
{
	int local0 = 0;
	int local1 = 1;
	static int static_local0 = 0;
	static int static_local1 = 1;
	int *heap0 = malloc(10); /* ? */
	int *heap1 = malloc(10);

	printf("----------------THREAD 2-----------------------\n");
	printf("thread local0 %p\n", (void *)&local0);
	printf("thread local1 %p\n", (void *)&local1);
	printf("thread tls0 %p\n", (void *)&tls0);
	printf("thread tls1 %p\n", (void *)&tls1);
	printf("static thread local0 %p\n", (void *)&static_local0);
	printf("static thread local1 %p\n", (void *)&static_local1);
	printf("regular global0 %p\n", (void *)&global0);
	printf("regular global1 %p\n", (void *)&global1);
	printf("thread heap0 %p\n", (void *)heap0);
	printf("thread heap1 %p\n", (void *)heap1);

	free(heap0);
	free(heap1);

	return arg;
}

void *Ex(void *arg)
{
	pthread_t t2 = {0};
	int local0 = 0;
	int local1 = 1;
	static int static_local0 = 0;
	static int static_local1 = 1;
	int *heap0 = malloc(10); /* ? */
	int *heap1 = malloc(10);

	printf("----------------THREAD 1-----------------------\n");
	printf("thread local0 %p\n", (void *)&local0);
	printf("thread local1 %p\n", (void *)&local1);
	printf("thread tls0 %p\n", (void *)&tls0);
	printf("thread tls1 %p\n", (void *)&tls1);
	printf("static thread local0 %p\n", (void *)&static_local0);
	printf("static thread local1 %p\n", (void *)&static_local1);
	printf("regular global0 %p\n", (void *)&global0);
	printf("regular global1 %p\n", (void *)&global1);
	printf("thread heap0 %p\n", (void *)heap0);
	printf("thread heap1 %p\n", (void *)heap1);
	
	pthread_create(&t2, NULL, Ex2, NULL);
	pthread_join(t2, NULL);

	free(heap0);
	free(heap1);

	return arg;
}


int main()
{
	pthread_t t1 = {0};
	int *heap0 = malloc(10);
	int *heap1 = malloc(10);
	int local0 = 0;
	int local1 = 0;

	pthread_create(&t1, NULL, Ex, NULL);
	sleep(6);
	pthread_join(t1, NULL);
	printf("statoc volatile int %p\n", (void *)&volti );
	printf("\n---------------MAIN THREAD (REGULAR)--------------\n");
	printf("heap0 %p\n", (void *)heap0);
	printf("heap1 %p\n", (void *)heap1);
	printf("local0 %p\n", (void *)&local0);
	printf("local1 %p\n", (void *)&local1);

	free(heap0);
	free(heap1);
	return 0;
}

