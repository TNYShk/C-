/**********************************************
 * UID - Source Code                          *
 * Developer: Tanya                   		  *
 * 2021-12-22                        		  *
 *                                            *
 *      Reviewed by David       	 	  	  *
**********************************************/
#include <sys/types.h> /* size_t, time_t, pid_t */
#include <unistd.h> /* size_t, pid_t */
#include <time.h> /*  time_t */
#include <stdio.h> /* print*/

#include "uid.h"

void TestUIDUID(ilrd_uid_t uid);
void TestUIDTime(ilrd_uid_t uid);
void TestUIDPID(ilrd_uid_t uid);
void CompareUIDs(ilrd_uid_t uid, ilrd_uid_t uid1);
void ComparetoBadUID(ilrd_uid_t uid);

int main(void)
{
	ilrd_uid_t new = UIDCreate();
	ilrd_uid_t new1 = UIDCreate();
	ilrd_uid_t new2 = UIDCreate();
	printf("\n\t----------------GET UID-------------\n");
	TestUIDUID(new);
	TestUIDUID(new1);
	TestUIDUID(new2);
	
	printf("\n\t----------------GET PID-------------\n");
	TestUIDPID(new);
	TestUIDPID(new1);
	TestUIDPID(new2);
	
	printf("\n\t----------------Compare to other UID-------------\n");
	CompareUIDs(new, new2);
	CompareUIDs(new, new1);
	printf("\n\t----------------TIME of UID-------------\n");
	TestUIDTime(new);
	TestUIDTime(new1);
	TestUIDTime(new2);

	
	printf("\n\t----------------Compare to BADUID-------------\n");
	ComparetoBadUID(new);
	ComparetoBadUID(new1);
	ComparetoBadUID(new2);
	printf("\n\t---------------- BADUID-------------\n");
	TestUIDUID(UIDBadUID);
	TestUIDPID(UIDBadUID);
	TestUIDTime(UIDBadUID);

	return 0;
}


void TestUIDPID(ilrd_uid_t uid)
{
	printf("UID PID is %u\n", uid.p_id);
}


void TestUIDTime(ilrd_uid_t uid)
{
	printf("UID time is %ld\n", uid.t_id);
}

void CompareUIDs(ilrd_uid_t uid, ilrd_uid_t uid1)
{
	printf("UID vs UID is the same? %d\n",UIDIsSame(uid,uid1));
}

void TestUIDUID(ilrd_uid_t uid)
{
	printf("UID is %lu\n", uid.u_id);
}

void ComparetoBadUID(ilrd_uid_t uid)
{
	CompareUIDs(uid, UIDBadUID);
}


