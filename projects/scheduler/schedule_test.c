#include <time.h> /*time_t */
#include <stdio.h> /*printf */
#include <assert.h> /* assert() */
#include <stdlib.h>

#include "task.h"
#include "scheduler.h" 
#include "priority_queue.h"

void TestOne();
void TestTwo();
void TestThree();


int Action(void *task_args)
{
	void *ptr = task_args;
	printf("Zero Action %d\n", *(int *)ptr);
	
	return 0;
}

int FAction(void *task_args)
{
	void *ptr = task_args;
	printf("Failed action, %d\n", *(int *)ptr);
	return -1;
}

int RAction(void *task_args)
{
	static int status = -1;
	return ++status;
}

void CleanT(void *cleanup_args)
{
	void *ptr = cleanup_args;
	printf("CleanupPrint, %d\n", *(int *)ptr);

}



int main(void)
{
	/*TestOne();
	TestTwo();*/
	TestThree();

	

	

	return 0;
}

void TestOne()
{
	int x = 100;
	int y = 6;

	ilrd_uid_t test_uid;
	ilrd_uid_t test2_uid;

	scheduler_t *new_sched = SchedCreate();
	assert (NULL != new_sched);
	assert(1 == SchedIsEmpty(new_sched));
	printf("\n\t------------------------------Test1---------------------------\n");
	printf("created sched, size is %ld\n", SchedSize(new_sched));

	test_uid = SchedAddTask(new_sched, &Action, &x, &CleanT, &x, time(NULL));
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));
	
	assert(0 == UIDIsSame(test_uid, UIDBadUID));

	assert(0 == SchedIsEmpty(new_sched));


	test2_uid = SchedAddTask(new_sched, &Action, &y, &CleanT, &y, time(NULL) - 601);
	
	printf("added another task to sched, size is %ld\n", SchedSize(new_sched));
	assert(0 == UIDIsSame(test2_uid, UIDBadUID));
	assert(0 == UIDIsSame(test_uid, test2_uid));
	

	SchedRemoveTask(new_sched, test2_uid);
	printf("removed task, size is now %ld\n", SchedSize(new_sched));
	
	printf("Destroying Scheduler\n");
	SchedDestroy(new_sched);
}

void TestTwo()
{
	int x = 2000;
	int y = 26;

	ilrd_uid_t test_uid;
	ilrd_uid_t test2_uid;
	ilrd_uid_t test3_uid;
	scheduler_t *new_sched = SchedCreate();
	assert (NULL != new_sched);
	assert(1 == SchedIsEmpty(new_sched));
	printf("\n\t------------------------------Test2---------------------------\n");
	printf("created Scheduler, size is %ld\n", SchedSize(new_sched));

	test_uid = SchedAddTask(new_sched, &Action, &x, &CleanT, &x, time(NULL));
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));
	
	assert(0 == UIDIsSame(test_uid, UIDBadUID));

	assert(0 == SchedIsEmpty(new_sched));

	test2_uid = SchedAddTask(new_sched, &Action, &y, NULL, NULL, time(NULL) + 6001);
	SchedAddTask(new_sched, &Action, &y, &CleanT, &x, time(NULL) + 601);
	SchedAddTask(new_sched, &Action, &y, &CleanT, NULL, time(NULL) + 601);

	printf("added more tasks to sched, size now  is %ld\n", SchedSize(new_sched));

	assert(0 == UIDIsSame(test2_uid, UIDBadUID));
	assert(0 == UIDIsSame(test_uid, test2_uid));
	
	SchedClear(new_sched);
	printf("scheduler clear test, size is %ld\n", SchedSize(new_sched));
	assert(0 == UIDIsSame(test_uid, test2_uid));

	test3_uid = SchedAddTask(new_sched, &Action, &y, &CleanT, &x, time(NULL) + 6001);
	printf("added task to cleared sched, size is %ld\n", SchedSize(new_sched));
	assert(0 == UIDIsSame(test2_uid, test3_uid));

	SchedDestroy(new_sched);
}

void TestThree()
{
	int x = 3000;
	int y = 160;
	ilrd_uid_t test_uid;
	

	scheduler_t *new_sched = SchedCreate();
	assert (NULL != new_sched);
	assert(1 == SchedIsEmpty(new_sched));

	printf("\n\t------------------------------Test3---------------------------\n");
	SchedAddTask(new_sched, &Action, &x, NULL, NULL, time(NULL));
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));
	SchedAddTask(new_sched, &FAction, &y, NULL, NULL, time(NULL) + 10);
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));
	test_uid = SchedAddTask(new_sched, &RAction, &y, NULL, NULL, time(NULL) +1);
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));

	SchedRun(new_sched);
	printf("Post Run, size is %ld\n", SchedSize(new_sched));
	SchedClear(new_sched);
	SchedDestroy(new_sched);


}