/********************************************
 * KICKDOG - Source Code                    *
 * Developer: Tanya                   		*
 * Mar 8, 2022                   	     	*
 *                                          *
 *      Reviewed by        	 	  	 		*
*********************************************/
#define _XOPEN_SOURCE (700)
#define _POSIX_C_SOURCE 199309L

#include <assert.h>      /* assert    */
#include <pthread.h>     /* thread_t  */
#include <signal.h>      /* sigaction */
#include <sys/types.h>   /* pid_t     */
#include <unistd.h>      /* fork      */
#include <stdio.h>       /* printf    */
#include <stdlib.h>      /* atoi */
#include <errno.h>       /* errno */
#include <string.h>      /*strcmp */

#include "watchdog.h"    /* watchdog API         */
#include "semaphore_sys_v.h"      /* sys_v sempahore API  */
#include "scheduler.h"      /* scheduler API        */
        
#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)
#define SUCCESS (0)
#define FAIL (-1)
#define ARGZ (256)
#define DATHNAME ("/watchdog_test")

#define atomic_sync_or_and_fetch(destptr, flag) __sync_or_and_fetch(destptr, flag)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)

#ifdef DEBUG
	#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#else
	#define errExit(msg) do { perror(msg); return(errno); } while (0)
#endif



scheduler_t *new_sched;
static pid_t another_pid = 0;
static int sched_flag = 0;
static int alive_g = 0;
static int sem_id;


static int TaskPingAlive(void *args);
static int TaskCheckAlive(void *args);
static int TaskStopSched(void *pid);

static void SomeFailDie(scheduler_t *sched);
static int Revive(char *argv[]);
static int SchedInit(char *argv[]);

static void SigHandlerKill(int sig, siginfo_t *info, void *ucontext);
static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext);





int main(int argc, char *argv[])
{
    struct sigaction sa = {0};
	struct sigaction ka = {0};
	(void)argc;
	sem_id = atoi(argv[1]);
	/* printf("semid %d\n",sem_id); */
	
	ka.sa_sigaction = &SigHandlerKill;
	sa.sa_sigaction = &SigHandlerAlive;
    sa.sa_flags |= SA_SIGINFO;
    ka.sa_flags |= SA_SIGINFO;
   
    if (SUCCESS != sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 handler");
    }

    if (SUCCESS != sigaction(SIGUSR2, &ka, NULL))
    {
        errExit("Failed to set SIGUSR2 handler");
    }
	
	printf("in KICKDOG: ppid is %d, and pid is %d\n", getppid(), getpid());

	assert(SUCCESS == SchedInit(argv));

	SemIncrement(sem_id,1);
    SchedRun(new_sched);

    return 0;
}




static int TaskPingAlive(void *args)
{
	(void)args;

	if(0 != another_pid)
	{
		kill(another_pid, SIGUSR1);
	}

	return PING_EVERY;
}

static int TaskCheckAlive(void *args)
{
	if(!atomic_compare_and_swap(&alive_g, 1, 0))
	{
		printf("in kickdog, trying to revive\n");
		Revive((char **)args);
		
		return 0;
	}
	
	return CHECK_ALIVE_EVERY;
}

static int Revive(char *argv[])
{
	errno = 0;
	printf("set env? %d\n",putenv("REVDOG=666"));
	if(errno != 0)
	{
		printf("errno? %d\n", errno);
	}

	another_pid = fork();
	if(0 > another_pid)
	{
		errExit("baby fork fail");
	}
	if(0 == another_pid)
	{
		char path[ARGZ] = {0};
		getcwd(path, ARGZ);
		
		strcat(path,DATHNAME);
		/* printf("REVIVE kickdog %d: %s\n",__LINE__,path); */
	
		SemDecrement(sem_id,1);
		if(FAIL == execv(path,argv))
		{
			errExit("OMFG ALL BROKEN REVIVE execv fail");
		}

	}
	return SUCCESS;
}

static int TaskStopSched(void *pid)
{
	(void)pid;

	if(1 == sched_flag)
	{
		SchedStop(new_sched);
		
		/* printf("kickdogsem val is %d\n", SemGetVal(sem_id) );
		write(STDOUT_FILENO, "kickdog:line 117 SIGUSR2\n", strlen("kickdog:line 117 SIGUSR2 ")); */
		kill(another_pid, SIGUSR2);
	}
	return PING_EVERY;
}



static int SchedInit(char *argv[])
{
	new_sched = SchedCreate();
	if(NULL == new_sched)
	{
		errExit("SchedCreate failed");
	}

	if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskPingAlive, NULL, 
    					NULL, NULL, time(0) + PING_EVERY)))
    {
    	SomeFailDie(new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    	
    }
    if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskCheckAlive, (void *)argv, 
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
	return SUCCESS;
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
	write(STDOUT_FILENO, "Dog fed\n", strlen("Dog fed  "));
	atomic_sync_or_and_fetch(&alive_g, 1);
	another_pid = info->si_pid;
	
}

static void SigHandlerKill(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;	
	(void)info;
	if (NULL != new_sched)
	{
		write(STDOUT_FILENO, "kickdog SGUSR2!\n", strlen("kickdog SGUSR2! "));
		atomic_compare_and_swap(&sched_flag,0 , 1);
	}
	
}

