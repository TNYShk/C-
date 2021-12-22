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


#include "uid.h"


const ilrd_uid_t UIDBadUID ={0,0,0};


ilrd_uid_t UIDCreate(void)
{
	 static size_t uid = 0;

	 ilrd_uid_t ucontainer = {0};


	 ucontainer.u_id = ++uid;
	 ucontainer.t_id = time(NULL);
	 ucontainer.p_id = getpid();


	 if( ((time_t)ucontainer.t_id == -1) || ((time_t)ucontainer.p_id == -1) )
	 {
	 	ucontainer = UIDBadUID;
	 }

	 return ucontainer;
}


int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	return ( (uid1.u_id == uid2.u_id) && (uid1.p_id == uid2.p_id) && (uid1.t_id == uid2.t_id));
}

