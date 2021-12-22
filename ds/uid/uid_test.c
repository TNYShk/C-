#include <sys/types.h> 
#include <unistd.h>
#include <stdio.h>

#include "uid.h"

int main(void)
{
	ilrd_uid_t new;
	ilrd_uid_t new1;
	printf("new pid %d\n", new.p_id);
	printf("new1 pid %d\n", new.p_id);
	printf("new uid %ld\n", new.u_id);
	printf("new uid %ld\n", new.u_id);
	printf("new time %ld\n", new.t_id);
	printf("new1 time %ld\n", new1.t_id);
	printf("new1 uid %ld\n", new1.u_id);
	return 0;
}