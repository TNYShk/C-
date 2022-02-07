#include <time.h> /*time_t */
#include <stdio.h> /*printf */
#include <assert.h> /* assert() */

#include "task.h" /*task related header  */
#include "scheduler_heap.h" /*scheduler header  */
#include "pq_heap.h" /* for the scheduler */


typedef struct remove
{
	scheduler_t *sched;
	ilrd_uid_t uid;

}remove_t;


void TestOne();
void TestTwo();
void TestThree();
void TestFour();
void TestFive();
void TestSix();

int Action(void *task_args);
int FAction(void *task_args);
int RAction(void *task_args);
int RAction1(void *task_args);
int RAction2(void *task_args);
int RAction3(void *task_args);

static int CreateAction(void *task_args);
int RemoveTaskAction(void *task_args);

static int StopAction(void *task_args);
static int StopAction1(void *task_args);

void CleanT(void *cleanup_args);
void CleanVoid(void *cleanup_args);









int main(void)
{
	

	TestOne();
	TestTwo();
	TestFour();
	TestThree();
	TestFive();
	TestSix();
	return 0;
}
int Action(void *task_args)
{
	void *ptr = task_args;
	printf("taks done removes itself %d ", *(int *)ptr);
	printf(" time now %lu\n\n", time(0));
	return 0;
}

int FAction(void *task_args)
{
	void *ptr = task_args;
	printf("Failed action, %d ", *(int *)ptr);
	printf(" time now %lu\n\n", time(0));
	return -1;
}

int RAction(void *task_args)
{
	static int status = 3;
	void *ptr = task_args;
	printf("Repeat task, %d ", *(int *)ptr);
	printf(" print time %lu\n\n", time(0));
	return --status;
}
int RAction1(void *task_args)
{
	static int status = 2;
	void *ptr = task_args;
	printf("Repeat task, %d ", *(int *)ptr);
	printf(" print time %lu\n\n", time(0));
	return --status;
}
int RAction2(void *task_args)
{
	static int status = 3;
	void *ptr = task_args;
	printf("Repeat task, %d ", *(int *)ptr);
	printf(" print time %lu\n\n", time(0));
	return --status;
}
int RAction3(void *task_args)
{
	static int status = 4;
	void *ptr = task_args;
	printf("Repeat task, %d ", *(int *)ptr);
	printf(" time now %lu\n\n", time(0));
	return --status;
}
static int CreateAction(void *task_args)
{
	time_t new = time(0) + 5;
	printf("\tcreate task +5,print time %lu\n\n", time(0));
	SchedAddTask((scheduler_t *)task_args, &StopAction, task_args, NULL,NULL, (time_t)new);
	return 0;
}

static int StopAction(void *task_args)
{
	FILE *stop = fopen("stop", "r");
	if (NULL != stop)
	{
		SchedStop((scheduler_t *)task_args);
		printf("stop action, print time %lu\n\n", time(0));
	}
	fclose(stop);
	return 1;
}

static int StopAction1(void *task_args)
{
	FILE *stop = fopen("stop", "r");
	if (NULL != stop)
	{
		fclose(stop);
		SchedStop((scheduler_t *)task_args);
		printf("stop action1, print time %lu\n\n", time(0));
	}
	if (!SchedIsEmpty((scheduler_t *)task_args))
	{
		return 0;
	}
	return 1;
}


int RemoveTaskAction(void *task_args)
{
	SchedRemoveTask( ((remove_t *)task_args)->sched, ((remove_t *)task_args)->uid );
	printf("Remove task action! print time %lu\n\n", time(0));
	return 0;
}


void CleanT(void *cleanup_args)
{
	void *ptr = cleanup_args;
	printf("VoidPrint, %d, ", *(int *)ptr);
	printf(" tprint time %lu\n\n", time(0));
}
void CleanVoid(void *cleanup_args)
{
	(void)cleanup_args;
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
	printf("\tcheck: Creates Scheduler, Add & Remove task, size, assert not empty \n");
	printf("created sched, size is %ld\n", SchedSize(new_sched));

	test_uid = SchedAddTask(new_sched, &Action, &x, NULL, NULL, time(NULL));
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));
	
	assert(0 == UIDIsSame(test_uid, UIDBadUID));

	assert(0 == SchedIsEmpty(new_sched));


	test2_uid = SchedAddTask(new_sched, &Action, &y, NULL, NULL, time(NULL) - 601);
	
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
	printf("\tcheck: Creates Scheduler, Add & Remove task, size, clear \n");
	printf("created Scheduler, size is %ld\n", SchedSize(new_sched));

	test_uid = SchedAddTask(new_sched, &Action, &x, NULL, NULL, time(NULL));
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));

	assert(0 == UIDIsSame(test_uid, UIDBadUID));

	assert(0 == SchedIsEmpty(new_sched));

	test2_uid = SchedAddTask(new_sched, &Action, &y, NULL, NULL, time(NULL) + 6001);
	SchedAddTask(new_sched, &Action, &y, &CleanVoid, &x, time(NULL) + 601);
	SchedAddTask(new_sched, &Action, &y, NULL, NULL, time(NULL) + 601);

	printf("added more tasks to sched, size now  is %ld\n", SchedSize(new_sched));

	assert(0 == UIDIsSame(test2_uid, UIDBadUID));
	assert(0 == UIDIsSame(test_uid, test2_uid));
	SchedRemoveTask(new_sched, test2_uid);

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
	int y = 360;
	
	scheduler_t *new_sched = SchedCreate();

	assert (NULL != new_sched);
	assert(1 == SchedIsEmpty(new_sched));

	printf("\n\t------------------------------Test3---------------------------\n");
	printf("\tcheck: Creates Scheduler, Actions: repeat, fail and done, Run & Stop Scheduler \n");
	printf("\tTo End test, must touch stop in terminal \n");
	SchedAddTask(new_sched, &Action, &x, &CleanT, &x, time(NULL) + 1);
	printf("added task to sched +1 sec, size is %ld\n", SchedSize(new_sched));
	SchedAddTask(new_sched, &FAction, &y, NULL, NULL, time(NULL) );
	printf("added task to sched, size is %ld\n", SchedSize(new_sched));
	SchedAddTask(new_sched, &RAction, &y, &CleanT, &x, time(NULL) + 3);
	printf("added task to sched + 3 sec, size is %ld\n", SchedSize(new_sched));
	
	SchedRun(new_sched);
	printf("Post Run, size is %ld\n", SchedSize(new_sched));

	SchedAddTask(new_sched, &StopAction, &x, &CleanT, &x, time(NULL));
	printf("added task to sched, size is %ld\n", SchedSize(new_sched) );
	
	SchedStop(new_sched);
	printf("Post Stop, size is %ld\n", SchedSize(new_sched));
	
	SchedAddTask(new_sched, &RAction1, &x, NULL, NULL, time(NULL) + 1);
	printf("added task to sched + 1 sec, size is %ld\n", SchedSize(new_sched));
	SchedAddTask(new_sched, &Action, &x, &CleanT, &x, time(NULL) );
	printf("added tasks , size is %ld\n", SchedSize(new_sched));
	
	SchedDestroy(new_sched);

}

void TestFour()
{
	int x = 4000;
	int y = 460;
	
	scheduler_t *new_sched = SchedCreate();
	assert (NULL != new_sched);
	assert(1 == SchedIsEmpty(new_sched));

	printf("\n\t------------------------------Test4---------------------------\n");
	printf("\tcheck: Creates Scheduler, Actions: Stop Action, Void Stop \n");
	printf("\tTo End test, must touch stop in terminal \n");
	SchedAddTask(new_sched, &Action, &x, &CleanT, &y, time(NULL) + 1);
	SchedAddTask(new_sched, &Action, &y,&CleanT, &x, time(NULL) + 2);
	SchedAddTask(new_sched, &RAction2, &y, NULL,NULL, time(NULL) );
	SchedAddTask(new_sched, &Action, &x, &CleanT, &y, time(NULL)+ 1);
	SchedAddTask(new_sched, &StopAction1, (void *)new_sched, NULL, NULL, time(NULL) + 3 );
	printf("added tasks to sched, 1 should remain , current size is %ld\n", SchedSize(new_sched));
	
	SchedRun(new_sched);
	printf("Finished Running, size is %ld\n", SchedSize(new_sched));

	SchedClear(new_sched);
	printf("Post Clear, size is %ld\n", SchedSize(new_sched));

	SchedDestroy(new_sched);

}

void TestFive()
{
	int x = 5000;
	int y = 560;
	
	scheduler_t *new_sched = SchedCreate();
	assert (NULL != new_sched);
	assert(1 == SchedIsEmpty(new_sched));

	printf("\n\t------------------------------Test5---------------------------\n");
	printf("\tcheck: Creates Scheduler, Action: tasks that adds another \n");

	SchedAddTask(new_sched, &Action, &x, &CleanT, &y, time(NULL) );
	SchedAddTask(new_sched, &CreateAction, (void *)new_sched , &CleanT, &y, time(0) + 1);
	printf("\nadded task that will add another and stop , before run size is %ld\n", SchedSize(new_sched));
	
	SchedRun(new_sched);
	printf("Finished Running, size is %ld\n", SchedSize(new_sched));

	SchedClear(new_sched);
	printf("Post Clear, size is %ld\n", SchedSize(new_sched));

	SchedDestroy(new_sched);

}

void TestSix()
{
	int x = 6000;
	int y = 666;
	
	scheduler_t *new_sched = SchedCreate();
	remove_t removetask  = {0};
	ilrd_uid_t test_uid;
	assert (NULL != new_sched);

	assert(1 == SchedIsEmpty(new_sched));

	printf("\n\t------------------------------Test6---------------------------\n");
	printf("\tcheck: Creates Scheduler, Action: tasks that removes another \n");

	SchedAddTask(new_sched, &Action, &y, NULL, NULL, time(NULL) );

	test_uid = SchedAddTask(new_sched, &RAction3, &x, &CleanT, &y, time(NULL) );
	
	removetask.sched = new_sched;
	removetask.uid = test_uid;

	printf("\nadded tasks size is %ld\n", SchedSize(new_sched));
	SchedAddTask(new_sched, &RemoveTaskAction, &removetask, NULL, NULL, time(NULL) );
	printf("\nadded task that removes, size is %ld\n", SchedSize(new_sched));

	SchedRun(new_sched);
	printf("Post Run, size is %ld\n", SchedSize(new_sched));

	SchedClear(new_sched);
	printf("Post Clear, size is %ld\n", SchedSize(new_sched));

	SchedDestroy(new_sched);
}