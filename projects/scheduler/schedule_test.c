#include <time.h> /*time_t */
#include <stdio.h> /*printf */
#include <assert.h> /* assert() */
#include <stdlib.h>

#include "task.h"
#include "scheduler.h" 
#include "priority_queue.h"

void TestOne();
void TestTwo();



int Action(void *task_args)
{
	void *ptr = task_args;
	printf("int arg is %d\n", *(int *)ptr);
	
	return 0;
}

void CleanT(void *cleanup_args)
{
	(void)cleanup_args;

}

int main(void)
{
	TestOne();
	TestTwo();
	

	

	

	return 0;
}

void TestOne()
{
	int x = 26;
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

	SchedRemoveTask(new_sched, test_uid);
	
	
	SchedDestroy(new_sched);
}

void TestTwo()
{
	int x = 3000;
	int y = 16;

	ilrd_uid_t test_uid;
	ilrd_uid_t test2_uid;

	scheduler_t *new_sched = SchedCreate();
	assert (NULL != new_sched);
	assert(1 == SchedIsEmpty(new_sched));
	printf("\n\t------------------------------Test2---------------------------\n");
	printf("created sched, size is %ld\n", SchedSize(new_sched));

	test_uid = SchedAddTask(new_sched, &Action, &x, &CleanT, &x, time(NULL));
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));
	
	assert(0 == UIDIsSame(test_uid, UIDBadUID));

	assert(0 == SchedIsEmpty(new_sched));


	test2_uid = SchedAddTask(new_sched, &Action, &y, NULL, NULL, time(NULL) + 6001);
	
	printf("added another task to sched, size is %ld\n", SchedSize(new_sched));
	assert(0 == UIDIsSame(test2_uid, UIDBadUID));
	assert(0 == UIDIsSame(test_uid, test2_uid));
	

	SchedClear(new_sched);
	printf("scheduler clear test, size is %ld\n", SchedSize(new_sched));
	
	
	SchedDestroy(new_sched);
}