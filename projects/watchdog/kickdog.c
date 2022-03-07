#define _XOPEN_SOURCE (700)
#define _POSIX_C_SOURCE 199309L
#include <time.h> /*time_t */
#include <assert.h>      /* assert    */
#include <pthread.h>     /* thread_t  */
#include <signal.h>      /* sigaction */
#include <sys/types.h>   /* pid_t     */
#include <unistd.h>      /* fork      */
#include <stdio.h>       /* printf    */
#include <fcntl.h>  /* O_* const.*/
#include <sys/stat.h> /* mode const. */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <string.h> /*strcmp */

#include "../include/watchdog.h"       /* watchdog API         */
#include "../include/semaphore_sys_v.h"      /* sys_v sempahore API  */
#include "../include/scheduler.h"      /* scheduler API        */
#include "../include/uid.h"
#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)
#define SUCCESS (0)
#define FAIL (-1)
#define ARGZ (256)



#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define atomic_sync_fetch_or(destptr, flag) __sync_fetch_and_or(destptr, flag)
#define atomic_sync_or_and_fetch(destptr, flag) __sync_or_and_fetch(destptr, flag)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)
#define atomic_sync_add_fetch(destptr, incrby) __sync_add_and_fetch(destptr, incrby)

static int TaskPingAlive(void *args);
static int TaskCheckAlive(void *args);
static int TaskStopSched(void *pid);
static int PingAlive2(void *args);


scheduler_t *new_sched;
pid_t pid_child;

static int sched_flag = 0;
static int alive_g = 0;
static int sem_id;

static void SomeFailDie(scheduler_t *sched);
static int TaskPingAlive(void *args);
static int TaskCheckAlive(void *args);
static int TaskStopSched(void *pid);

static void SigHandlerKill(int sig, siginfo_t *info, void *ucontext);
static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext);



static int TaskPingAlive(void *args)
{
	(void)args;

	if(0 != pid_child)
	{
		kill(pid_child, SIGUSR1);
	}

	return PING_EVERY;
}

static int TaskCheckAlive(void *args)
{
	(void)args;
	if(!atomic_compare_and_swap(&alive_g, 1, 0))
	{
		
		/*SchedDestroy(new_sched);*/
		
		/* REVIVE*/
	
	}
	
	return CHECK_ALIVE_EVERY;
}

static int TaskStopSched(void *pid)
{
	if(1 == sched_flag)
	{
		/*SchedStop(new_sched);*/
	}
	return PING_EVERY;
}


int main(int argc, const char *argv[])
{
    struct sigaction sa = {0};
	struct sigaction ka = {0};
	
	sem_id = atoi(argv[1]);
	printf("semid %d\n",sem_id);

	ka.sa_sigaction = &SigHandlerKill;
	sa.sa_sigaction = &SigHandlerAlive;
    sa.sa_flags |= SA_SIGINFO;
    ka.sa_flags |= SA_SIGINFO;
   
    if (SUCCESS != sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR2 handler");
    }

    if (SUCCESS != sigaction(SIGUSR2, &ka, NULL))
    {
        errExit("Failed to set SIGUSR2 handler");
    }
	

	new_sched = SchedCreate();

	if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskPingAlive, NULL, 
    							NULL, NULL, time(0) + PING_EVERY)))
    {
    	SomeFailDie(new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    	
    }
    if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskCheckAlive, NULL, 
    					NULL, NULL, time(0) + CHECK_ALIVE_EVERY)))
    {
    	SomeFailDie(new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    }

     if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskStopSched, NULL, 
    					NULL, NULL, time(0) + CHECK_ALIVE_EVERY)))
    {
    	SomeFailDie(new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    }
    SemIncrement(sem_id, 1);
    if(1 == SemGetVal(sem_id))
    {
    	SchedRun(new_sched);
    }
  

    return 0;
}


static void SomeFailDie(scheduler_t *sched)
{
    SchedDestroy(sched);
    sched = NULL;
    SemRemove(sem_id);
   
}

static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;	
	write(STDOUT_FILENO, "Dog Kicked\n", strlen("Dog Kicked  "));
	atomic_sync_or_and_fetch(&alive_g, 1);
	pid_child = info->si_pid;
	
}

static void SigHandlerKill(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;	
	(void)info;
	if (NULL != new_sched)
	{
		atomic_compare_and_swap(&sched_flag,0 , 1);
	}
	printf("signalhandlerkill!\n");
}

static int TaskSIGUSR2(void *args)
{
	(void)args;
	
	if(0 == pid_child)
	{
		kill(getppid(), SIGUSR2);
	}

	return SUCCESS;
}