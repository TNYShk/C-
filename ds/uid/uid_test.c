/**********************************************
 * UID - Source Code                          *
 * Developer: Tanya                   		  *
 * 2021-12-22                        		  *
 *                                            *
 *                     					 	  *
**********************************************/
#include <stddef.h> /* NULL declerations */
#include <sys/types.h> /* size_t, time_t, pid_t */
#include <unistd.h> /* size_t, pid_t */
#include <time.h> /*  time_t */
#include <stdio.h> /* print*/

#include "uid.h"

int main(void)
{
	ilrd_uid_t new = UIDCreate();
	ilrd_uid_t new1= UIDCreate();
	printf("new pid %u\n", new.p_id);
	printf("new1 pid %u \n", new.p_id);
	printf("new uid %ld\n", new.u_id);
	printf("new uid %ld\n", new.u_id);
	printf("new time %ld\n", new.t_id);
	printf("new1 time in seconds since 1970 %ld\n", new1.t_id/3600);
	printf("new1 uid %ld\n", new1.u_id);

	printf("is the same? %d\n",UIDIsSame(new,new1));
	printf("is the same? %d\n",UIDIsSame(new,new));
	return 0;
}
