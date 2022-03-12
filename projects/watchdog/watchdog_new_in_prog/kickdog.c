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
#include <string.h>      /*strlen */

#include "watchdog.h"    /* watchdog API         */
#include "semaphore_sys_v.h"      /* sys_v sempahore API  */
#include "scheduler.h"      /* scheduler API        */
       
#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)
#define SUCCESS (0)
#define FAIL (-1)
#define ARGZ (256)


#define atomic_sync_or_and_fetch(destptr, flag) __sync_or_and_fetch(destptr, flag)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)

#ifdef DEBUG
	#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#else
	#define errExit(msg) do { perror(msg); return(errno); } while (0)
#endif

extern volatile int watchdog_am_i;





int main(int argc, char *argv[])
{
    
	watchdog_am_i = 1;
	
	WDStart(argc, argv);
	
    return 0;
}


