#include <sys/types.h> 
#include <unistd.h>
#include <time.h>
#include <assert.h>

#include "uid.h"


const ilrd_uid_t UIDBadUID ={0,0,0};





ilrd_uid_t UIDCreate(void)
{
	 static size_t uid = 0;
	 ilrd_uid_t ucontainer = {0};

	 time_t times = time(NULL);
	 pid_t pid = getpid();

	 ucontainer.u_id = ++uid;
	 ucontainer.t_id = times;
	 ucontainer.p_id = pid;

	 if( (ucontainer.t_id == -1) || (ucontainer.p_id == -1) )
	 {
	 	ucontainer = UIDBadUID;
	 }
	

	 return ucontainer;
}

int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	return ( (uid1.u_id == uid2.u_id) && (uid1.p_id == uid2.p_id) && (uid1.t_id == uid2.t_id));
}

