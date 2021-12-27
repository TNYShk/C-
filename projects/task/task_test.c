#include <time.h> /*time_t */
#include <stdio.h> /*printf */
#include <assert.h> /* assert()         */
#include <stdlib.h>

#include "task.h"

void TestOne();
void TestTwo();

int TaskAction(void *task_args)
{
	void *ptr = task_args;
	printf("int arg is %d\n", *(int *)ptr);
	
	return 0;
}
int FloatAction(void *task_args)
{
	void *ptr = task_args;
	printf("arg is %f\n", *(float *)ptr);
	
	return 0;
}


void Clean(void *cleanup_args)
{
	cleanup_args = NULL;

}

void CleanMalloc(void *cleanup_args)
{
	void *ptr = cleanup_args;
	free (cleanup_args);
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
	task_t *test = NULL;
	task_t *test2 = NULL;
	ilrd_uid_t test_uid;

	test = TaskCreate(&TaskAction, &x, &Clean, &x, time(NULL));
	test2 = TaskCreate(&TaskAction, &y, &Clean, &x, time(NULL));

	assert(NULL != test);
	assert(NULL != test2);
	
	printf("\n\t***********************-Test-1-*********************************\n\n");
    printf("\t****Run and destroy tasks***********\n");
    	TaskRun(test);
    	TaskRun(test2);
    printf("\t****Get UID***********\n");
    test_uid = TaskGetUID(test);
    printf("task1 UID: %ld-%ld-%d \n", test_uid.u_id, test_uid.t_id, test_uid.p_id);
    test_uid = TaskGetUID(test2);
    printf("task2 UID: %ld-%ld-%d \n", test_uid.u_id, test_uid.t_id, test_uid.p_id);
   
    TaskDestroy(test);
	TaskDestroy(test2);

}

void TestTwo()
{
	float x = 1.316;
	float y = -5.1;
	task_t *test = NULL;
	task_t *test2 = NULL;
	const time_t now = time(NULL);
	time_t task_time;

	struct tm *tmp;

	test = TaskCreate(&FloatAction, &x, &Clean, &x, time(NULL));
	test2 = TaskCreate(&FloatAction, &y, &Clean, &y, time(NULL));

	printf("\n\t***********************-Test-2-*********************************\n\n");
    printf("\n\t****Action Func ***********\n");
	TaskRun(test);
	TaskRun(test2);

    printf("\n\t****Get & Set time***********\n");
	TaskSetTimeToRun(test, now - 1812);
	task_time = TaskGetTimeToRun(test);
	tmp = localtime(&task_time);
	printf("task1: %s\n", asctime(tmp));

	TaskSetTimeToRun(test2, now + 611);
	task_time = TaskGetTimeToRun(test2);
	tmp = localtime(&task_time);
	printf("task2 : %s\n", asctime(tmp));
	printf("\t****Compare time tasks***********\n");
	printf("compare: %d sec difference\n",TasksCompare(test, test2));

	printf("\n\t****Compare UID***********\n");
	printf("isMatch?  %d\n",TaskIsMatch(test, TaskGetUID(test2)));
	printf("test itself (1 for yes), isMatch? %d\n",TaskIsMatch(test, TaskGetUID(test)));
	
	TaskDestroy(test);
	TaskDestroy(test2);
}