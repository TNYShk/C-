/********************************************
 * WATCHDOG - Source Code                   *
 * Developer: Tanya                   		*
 * Mar 8, 2022                   	     	*
 *                                          *
 *      Reviewed by Ephraim	 	  	 		*
*********************************************/
#define _XOPEN_SOURCE (700)     /* getenv*/
#define _POSIX_C_SOURCE 200112L /*setenv */
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

#define PRINT(msg)  do {write(STDOUT_FILENO, (msg), strlen(msg)); } while (0)
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
#define PATHNAME ("/kickdog")


static void *WrapperSchedSem(void *something);
static void Terminate(scheduler_t *sched);
static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext);
static void SigHandlerKill(int sig);

static int TaskPingAlive(void *args);
static int TaskCheckAlive(void *args);
static int TaskStopSched(void *pid);

static int InitSched(void);
static int InitHandlers(void);
static int InitProcess(char *argv[], int semid);
static int Revive(void);

typedef struct revive
{
	char buffer[BUFSIZ];
	char *full_path;
	pid_t pid_child;
	int semid;
}revive_t;

static scheduler_t *new_sched = NULL;
static pthread_t watchdog_t_g = {0};

static volatile int alive_g = 0;
static volatile int sched_flag = 0;


static revive_t revive_g;



int WDStart(int argc, char *argv[])
{
	(void)argc;
	errno = 0;

	if(SUCCESS != InitHandlers())
	{
		#ifdef DEBUG
			printf("InitHandler Error %s, %d\n", __FILE__, __LINE__);
    	#endif
		return FAIL;
	}
	
    revive_g.semid = InitSem(0);
    if(0 >  revive_g.semid)
    {
    	errExit("Init_sem");
    }
	
	if(SUCCESS != InitSched())
	{
		#ifdef DEBUG
			printf("SchedInit Error %s, %d\n", __FILE__, __LINE__);
		#endif
		return FAIL;
	}

	if(SUCCESS != pthread_create(&watchdog_t_g, NULL, &WrapperSchedSem, new_sched))
	{
		Terminate(new_sched);
		kill(revive_g.pid_child, SIGUSR2);
		errExit("pthread_create");
	}
	

    if(NULL == getenv("REVDOG"))
	{
		if (SUCCESS != InitProcess(argv,  revive_g.semid) || 
			SUCCESS != SemDecrement(revive_g.semid, 1))
		{
			Terminate(new_sched);
			return FAIL;
		}
		
	}
	else 
	{
		if(SUCCESS != unsetenv("REVDOG"))
		{
			errExit("unsetenv fail");
		}
	}

	return errno;
}

int WDStop(void)
{
	#ifdef DEBUG
		PRINT("WDStop\n");
	#endif
	kill(revive_g.pid_child, SIGUSR2);
	
	pthread_join(watchdog_t_g, NULL);
	Terminate(new_sched);

	return SUCCESS;
}

static int InitHandlers(void)
{
	struct sigaction sa = {0};
	struct sigaction ka = {0};
	errno = 0;

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
	return errno;
}


static int InitProcess(char *argv[], int semid)
{
	char semchar[ARGZ] = {'\0'};
	char cwd[BUFSIZ] = {'\0'};
	errno = 0;

	if(NULL == getcwd(cwd, BUFSIZ))
	{
		errExit("getcwd fail");
	}
	assert(0 <= sprintf(semchar,"%d", semid));

	if(SUCCESS != setenv("SEMCHAR", semchar, 1))
	{
		errExit("setenv fail");
	}

	revive_g.pid_child = fork();
		
	if(0 > revive_g.pid_child)
	{
		errExit("fork fail");
	}
	if (0 == revive_g.pid_child) /* in watchdog process */
	{
		strcat(cwd, PATHNAME);
		
		if(FAIL == execv(cwd,argv))
		{
			errExit("Failed execv");
		}
	}

    memcpy(revive_g.buffer, argv[0], strlen(argv[0]));
    revive_g.full_path = revive_g.buffer + strlen(revive_g.buffer) + 1;
 	strcat(revive_g.full_path, semchar);

	return errno;
}



static int InitSched(void)
{
	errno = 0;
	new_sched = SchedCreate();
	if(NULL == new_sched)
	{
		SemRemove( revive_g.semid); 
		#ifdef DEBUG
			printf("Task Sched Error %s, %d\n", __FILE__, __LINE__);
		#endif
    	return FAIL;
	}

	if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskPingAlive, NULL, 
    							NULL, NULL, time(0) + PING_EVERY)))
    {
    	Terminate(new_sched);
		#ifdef DEBUG
    		printf("Task Sched Error %s, %d\n", __FILE__, __LINE__);
		#endif	
    	return FAIL;
    	
    }
    if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskCheckAlive, NULL, 
    					NULL, NULL, time(0) + CHECK_ALIVE_EVERY)))
    {
    	Terminate(new_sched);
		#ifdef DEBUG
			printf("Task Sched Error %s, %d\n", __FILE__, __LINE__);
    	#endif
		return FAIL;
    }

    if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskStopSched, NULL, 
    					NULL, NULL, time(0) + CHECK_ALIVE_EVERY)))
    {
    	Terminate(new_sched);
		#ifdef DEBUG
    		printf("Task Sched Error %s, %d\n", __FILE__, __LINE__);
    	#endif
		return FAIL;
    }
	#ifdef DEBUG
		printf("in WATCHDOG ppid is %d, and pid is %d\n", getppid(), getpid()); 
	#endif
	return errno;
}




static void Terminate(scheduler_t *sched)
{
	SchedDestroy(sched);
    sched = NULL;
   	SemRemove( revive_g.semid); 
}

static void *WrapperSchedSem(void *something)
{
	SchedRun((scheduler_t *)something);
	return NULL;
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
		#ifdef DEBUG
			PRINT("REVIVE PLEASE\n");
		#endif
		return Revive();
	}
	
	return CHECK_ALIVE_EVERY;
}

static int Revive(void)
{
	char revive[BUFSIZ] = {0};
	errno = 0;

	getcwd(revive, ARGZ);
	strcat(revive, PATHNAME);
	
	if(SUCCESS != setenv("SEMCHAR",revive_g.full_path, 1))
	{
		errExit("setenv fail");
	}
	revive_g.pid_child = fork();
	if(0 > revive_g.pid_child)
	{
		errExit("WD Revive fork fail");
	}

	if(0 == revive_g.pid_child)
	{
		if(FAIL == execl(revive,revive, revive_g.full_path, NULL))
    	{
        	errExit("WD Revive fail execl");
    	}
	}
	return SUCCESS;
}


static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;	
	#ifndef DEBUG
		PRINT("Hungry Barking DOG\n");
	#endif
	atomic_sync_or_and_fetch(&alive_g, 1);
	revive_g.pid_child = info->si_pid;
}

static void SigHandlerKill(int sig)
{
	(void)sig;
	atomic_compare_and_swap(&sched_flag,0 , 1);
}

static int TaskStopSched(void *pid)
{
	(void)pid;
	if (1 == sched_flag)
	{
		SchedStop(new_sched);
	}
	return PING_EVERY;
}

