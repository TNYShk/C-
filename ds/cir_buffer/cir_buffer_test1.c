#include <unistd.h> /* size_t ssize_t*/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* offsetof*/
#include <stdlib.h> /* mem alllocation*/
#include <string.h> /* string.h*/
#include "cir_buffer.h"
#include "../../include/utils.h"
void Testone(void);
void Testtwo(void);
void TestThree(void);
void TestFour(void);


int main(void)
{
	
	Testone();
	Testtwo();
	TestThree();
	TestFour();
	return 0;
}

void Testone(void)
{
	
	cbuffer_t *cyc_buff = NULL;
	
	char *string = "hello one two three";

	ssize_t ans = 0;
	 
	printf("\n\t----------------------Test1-------------------------------\n");
	cyc_buff  = CBuffCreate(5);
	TEST_NOT_NULL(cyc_buff);
	

	printf("Capacity is %ld\n", CBuffCapacity(cyc_buff));
	printf("struct empty? %d\n", CBuffIsEmpty(cyc_buff));
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("\n**************** writing 2 to buffer**************************\n");
	ans = CBuffWrite(cyc_buff,string,2);
	printf("written %ld bytes\n", ans);
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));
	printf("\n**************** writing 8 to buffer**************************\n");
	ans = CBuffWrite(cyc_buff,string,8);
	printf("written %ld bytes\n", ans);
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));
	printf("\n**************** writing 2 to buffer**************************\n");
	ans = CBuffWrite(cyc_buff,string,2);
	printf("written %ld bytes\n", ans);

	printf("\n\n");
	CBuffDestroy(cyc_buff);
}

void Testtwo(void)
{
	
	cbuffer_t *cyc_buff = NULL;
	
	char *string = "hello there";

	ssize_t ans = 0;
	char *dest = NULL;
	dest = (char*)calloc(BUFSIZ, sizeof(char));
	
	printf("\n\t----------------------Test2-------------------------------\n");
	cyc_buff  = CBuffCreate(10);
	TEST_NOT_NULL(cyc_buff);

	printf("Capacity check is %ld\n", CBuffCapacity(cyc_buff));
	printf("is Empty? %d\n", CBuffIsEmpty(cyc_buff));
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------writing 6 to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,6);
	printf("written %ld bytes\n", ans);
	printf("is Empty? %d\n", CBuffIsEmpty(cyc_buff));
	
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));

	printf("\n-------------------Reading 4 from buffer-------------------------------\n");
	ans = CBuffRead(cyc_buff,dest,4);
	printf("read %ld bytes from buffer\n",ans);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("destination is %s\n", dest);
	
	printf("\n-------------------Reading 2 more----------------------------------\n");
	ans = CBuffRead(cyc_buff,dest,2);
	printf("read %ld bytes from buffer\n",ans);
	
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------Reading 2 more----------------------------------\n");
	ans = CBuffRead(cyc_buff,dest,2);
	printf("read %ld bytes from buffer\n",ans);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("is Empty? %d\n", CBuffIsEmpty(cyc_buff));
	printf("\n-------------------Writing 5 to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,5);
	printf("written %ld bytes\n", ans);

	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	
	printf("\n-------------------Reading 2 from buffer-------------------------------\n");
	ans = CBuffRead(cyc_buff,dest,2);
	printf("read %ld bytes from buffer\n",ans);
	printf("struct empty? %d\n", CBuffIsEmpty(cyc_buff));
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));

	printf("\n-------------------Writing 5 to buffer-------------------------------\n");
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	ans = CBuffWrite(cyc_buff,string,5);
	printf("written %ld bytes\n\n", ans);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	
	free(dest);
	dest = NULL;
	CBuffDestroy(cyc_buff);
}

void TestThree(void)
{
	
	cbuffer_t *cyc_buff = NULL;
	
	char *string = "Akuna Matata thats all";

	ssize_t ans = 0;
	char *dest = (char *)calloc(BUFSIZ, sizeof(char));
	TEST_NOT_NULL(dest);

	printf("\n\t----------------------Test3-------------------------------\n");
	cyc_buff  = CBuffCreate(20);
	TEST_NOT_NULL(cyc_buff);

	printf("Capacity check is %ld\n", CBuffCapacity(cyc_buff));
	printf("is Empty? %d\n", CBuffIsEmpty(cyc_buff));
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------writing 8 to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,8);
	printf("written %ld bytes\n", ans);
	printf("is Empty? %d\n", CBuffIsEmpty(cyc_buff));
	CONDITION_TEST(ans, CBuffCapacity(cyc_buff) - CBuffFreeSpace(cyc_buff))
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------writing 8 more -------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,8);
	printf("written %ld bytes\n", ans);
	printf("is Empty? %d\n", CBuffIsEmpty(cyc_buff));
	
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));
	
	printf("\n-------------------Reading 6 from buffer-------------------------------\n");
	ans = CBuffRead(cyc_buff,dest,10);
	printf("read %ld bytes from buffer\n",ans);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	
	
	free(dest);
	dest = NULL;
	CBuffDestroy(cyc_buff);
}

void TestFour(void)
{
	
	cbuffer_t *cyc_buff = NULL;
	char *string = "Akuna Matata thats all";
	char *another = "Monkey Bufsiz Business";
	ssize_t ans = 0;
	char *dest = (char *)calloc(BUFSIZ, sizeof(char));
	TEST_NOT_NULL(dest);
	
	printf("\n\t----------------------Test4-------------------------------\n");
	cyc_buff  = CBuffCreate(20);
	TEST_NOT_NULL(cyc_buff);
	assert (NULL != cyc_buff);
	printf("Capacity check is %ld\n", CBuffCapacity(cyc_buff));
	CONDITION_TEST(1,CBuffIsEmpty(cyc_buff))
	CONDITION_TEST(20, CBuffFreeSpace(cyc_buff) )
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------writing 20 to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff, string, 20);
	printf("written %ld bytes\n", ans);
	printf("is Empty? %d\n", CBuffIsEmpty(cyc_buff));
	
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------writing 8 more? -------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,8);
	CONDITION_TEST(-1, ans);
	CONDITION_TEST(0, CBuffIsEmpty(cyc_buff));

	
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));
	
	printf("\n-------------------Reading 20 from buffer-------------------------------\n");
	ans = CBuffRead(cyc_buff,dest, 20);
	printf("read %ld bytes from buffer\n",ans);
	printf("read: %s\n", dest);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));

	printf("\n-------------------writing another -------------------------------\n");
	ans = CBuffWrite(cyc_buff, another, strlen(another));
	printf("written %ld bytes\n", ans);
	
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------Reading another-------------------------------\n");
	ans = CBuffRead(cyc_buff,dest, strlen(dest));
	printf("read %ld bytes from buffer\n", ans);
	printf("read: %s\n", dest);
	
	CONDITION_TEST(1, CBuffIsEmpty(cyc_buff))
	free(dest);
	dest = NULL;
	CBuffDestroy(cyc_buff);
}