#define _XOPEN_SOURCE (700)

#include <assert.h>      /* assert    */
#include <pthread.h>     /* thread_t  */
#include <signal.h>      /* sigaction */
#include <sys/types.h>   /* pid_t     */
#include <unistd.h>      /* fork      */
#include <stdio.h>       /* printf    */
#include <fcntl.h>  /* O_* const.*/
#include <sys/stat.h> /* mode const. */
#include <semaphore.h> /*semaphore */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <string.h> /*strcmp */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define atomic_sync_fetch_or(destptr, flag) __sync_fetch_and_or(destptr, flag)


#include "scheduler.h"
#include "semaphore_posix.h"
#include "watchdog.h"

#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)


int WDStart(int argc, char *argv[])
{
	create global scheduler

	return 0;
}

static void *WatchdogThread(void *something)
{
    create semaphore
}