/********************************************
 * WATCHDOG - Source Code                   *
 * Developer: Tanya                   		*
 * Mar 8, 2022                   	     	*
 *                                          *
 *      Reviewed by        	 	  	 		*
*********************************************/
#define _XOPEN_SOURCE (700)
#define _POSIX_C_SOURCE 200112L 
#include <time.h>        /* time_t      */
#include <assert.h>      /* assert      */
#include <pthread.h>     /* thread_t    */
#include <signal.h>      /* sigaction   */
#include <sys/types.h>   /* pid_t       */
#include <unistd.h>      /* fork        */
#include <stdio.h>       /* printf      */
#include <stdlib.h>      /* atoi        */
#include <errno.h>       /* errno       */
#include <string.h>      /* strlen      */
#include "scheduler.h"		  /* scheduler API        */
#include "semaphore_sys_v.h"  /* sys_v sempahore API  */
#include "watchdog.h"         /* watchdog API         */

#ifdef DEBUG
	#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#else
	#define errExit(msg) do { perror(msg); return(errno); } while (0)
#endif

#define atomic_sync_or_and_fetch(destptr, flag) __sync_or_and_fetch(destptr, flag)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)


	
#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)
#define SUCCESS (0)
#define FAIL (-1)
#define ARGZ (256)
#define PATHNAME ("./kickdog")


static void *WrapperSchedSem(void *something);
static void SomeFailDie(scheduler_t *sched);
static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext);
static void SigHandlerKill(int sig);
static int TaskPingAlive(void *args);
static int TaskCheckAlive(void *args);
static int TaskStopSched(void *pid);
static void SetPIDPath(void);
static int InitSched(void);
static int InitProcess(char *argv[]);
static int InitSigHandler(void);
static int InitSemaphore(char *argv[]);
static void WDRun(void);
static int Revive(char *argv[]);


typedef struct revive
{

	int sem_id;
	char semchar[ARGZ];
	char buffer[ARGZ];
	char path_to_revive[BUFSIZ];
	char *whole;
	char **args;
	pid_t pid_child;
}revive_t;

volatile int watchdog_am_i = 0;

static scheduler_t *new_sched;
static int alive_g = 0;
static int sched_flag = 0;

static pthread_t watchdog_t_g = {0};

static int semid = 0;

revive_t revive_g;




int WDStart(int argc, char *argv[])
{
	int who_am_i = (NULL == getenv("WHO"));
	
	assert(1 <= argc);
	revive_g.args = argv;

	InitSigHandler();

	assert(SUCCESS == InitSemaphore(argv));
	

	if(who_am_i)
	{
		putenv("WHO=1");
		Revive(argv);
	}
	else
	{
		revive_g.pid_child = getppid();
	}
	
    if(watchdog_am_i)
	{
		WDRun();
	}	

	if(SUCCESS != pthread_create(&watchdog_t_g, NULL, &WrapperSchedSem, new_sched))
	{
			SomeFailDie(new_sched);
			write(STDOUT_FILENO, "pthread create watchdog SIGUSR2\n", 25);
			kill(revive_g.pid_child, SIGUSR2);
			errExit("pthread_create");
	}
	
	return SUCCESS;
}

static void WDRun(void)
{
	assert(SUCCESS == InitSched());

	getppid() == revive_g.pid_child ? 
	 SemIncrement(revive_g.sem_id,1):SemDecrement(revive_g.sem_id,1);

	 SchedRun(new_sched);

	 if(watchdog_am_i)
	 {
		SomeFailDie(new_sched);
		write(STDOUT_FILENO, "pthread create watchdog SIGUSR2\n", 25);
		kill(revive_g.pid_child, SIGUSR2);
		printf("%s, %d\n",__FILE__, __LINE__);
	 }

}

static int InitSigHandler(void)
{
	struct sigaction sa = {0};
	struct sigaction ka = {0};
	
	sa.sa_sigaction = &SigHandlerAlive;
	ka.sa_handler = &SigHandlerKill;
    sa.sa_flags |= SA_SIGINFO;
	
    if (SUCCESS != sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 handler");
    }

    if (SUCCESS != sigaction(SIGUSR2, &ka, NULL))
    {
        errExit("Failed to set SIGUSR2 handler");
    }
	return SUCCESS;
}

static int InitSemaphore(char *argv[])
{
	char *name_sem = NULL;
	
	if(NULL != (name_sem = getenv("SEMV")))
	{
		revive_g.sem_id = atoi(name_sem);
		return revive_g.pid_child;
	}
	else
	{
		revive_g.sem_id = InitSem(0);
			if(0 > revive_g.sem_id)
			{
				errExit("Init_sem");
			}
		sprintf(revive_g.semchar,"%d", revive_g.sem_id);
		setenv("SEMV",revive_g.semchar,1);
	}
	semid = revive_g.sem_id;

	return SUCCESS;
}



int WDStop(void)
{
	
		write(STDOUT_FILENO, "WDStop\n", strlen("WDStop "));
		kill(revive_g.pid_child, SIGUSR2);
		/* kill(getppid(), SIGUSR2); */
		pthread_join(watchdog_t_g, NULL);
		SemRemove(revive_g.sem_id); 
		unsetenv("SEMV");

	
	 SchedStop(new_sched); 
	SchedDestroy(new_sched);
    new_sched = NULL;
   return SUCCESS;
}


static int Revive(char *argv[])
{
	
	return InitProcess(argv);
}

static int InitProcess(char *argv[])
{
	
	revive_g.pid_child = fork();
		
	if(0 > revive_g.pid_child)
	{
		errExit("fork fail");
	}
	if (0 == revive_g.pid_child) /* in watchdog process */
	{
		if( execvp((watchdog_am_i == 0)? PATHNAME : *argv ,argv))
		{
			errExit("Failed execvp");
		}
	}

    memcpy(revive_g.buffer, argv[0], strlen(argv[0]));
    revive_g.whole = revive_g.buffer + strlen(revive_g.buffer) + 1;
 	strcat(revive_g.whole, revive_g.semchar);

	return SUCCESS;
}

static int InitSched(void)
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

	printf("in WATCHDOG ppid is %d, and pid is %d\n", getppid(), getpid()); 
	return SUCCESS;
}




static void SomeFailDie(scheduler_t *sched)
{
    SchedDestroy(sched);
    sched = NULL;
   	SemRemove(revive_g.sem_id); 
}

static void *WrapperSchedSem(void *something)
{
	WDRun();
	return something;
}


static int TaskPingAlive(void *args)
{
	(void)args;

	if(0 != revive_g.pid_child)
	{
		kill(revive_g.pid_child, SIGUSR1);
	}

	return PING_EVERY;
}

static int TaskCheckAlive(void *args)
{
	(void)args;
	if(!__sync_bool_compare_and_swap(&alive_g, 1, 0))
	{
		write(STDOUT_FILENO, "REVIVE PLEASE\n", strlen("REVIVE PLEASE "));
		Revive(args);
	}
	
	return CHECK_ALIVE_EVERY;
}



static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;	
	write(STDOUT_FILENO, "Hungry Barking DOG\n", strlen("Hungry Barking DOG  "));
	atomic_sync_or_and_fetch(&alive_g, 1);
	revive_g.pid_child = info->si_pid;
}

static void SigHandlerKill(int sig)
{
	(void)sig;
	
	atomic_compare_and_swap(&sched_flag, 0 , 1);
}

int TaskStopSched(void *pid)
{
	(void)pid;
	if (1 == sched_flag)
	{
		SchedStop(new_sched);
	}
	return PING_EVERY;
}

