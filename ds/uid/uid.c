#include <sys/types.h> 
#include <unistd.h>
#include <time.h>
#include <assert.h>

#include "uid.h"


const ilrd_uid_t UIDBadUID ={0,0,0};





ilrd_uid_t UIDCreate(void)
{
	 static size_t uid = 0;
	 ilrd_uid_t test = {0};
	 time_t time = time(NULL);
	 pid_t pid = getpid();

	 test.u_id = ++uid;
	 test.t_id = time;
	 test.p_id = pid;

	 if( (test.t_id == -1) || (test.p_id == -1) )
	 {
	 	test = UIDBadUID;
	 }
	

	 return test;
}

