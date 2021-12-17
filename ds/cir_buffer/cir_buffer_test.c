#include <unistd.h> /* size_t ssize_t*/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* offsetof*/

#include "cir_buffer.h"



int main(void)
{
	
	cbuffer_t *cyc_buff = NULL;
	
	char *string = "hello one two three";

	ssize_t ans = 0;
	char dest[BUFSIZ];

	cyc_buff  = CBuffCreate(20);

	assert (NULL != cyc_buff);

	
	printf("struct empty? %d\n", CBuffIsEmpty(cyc_buff));
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("\n-------------------writing to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,4);
	printf("written bytes %ld\n", ans);
	
	
	printf("struct free space = %ld\n\n", CBuffFreeSpace(cyc_buff));

	printf("\n-------------------reading from buffer-------------------------------\n");
	ans = CBuffRead(cyc_buff,dest,4);
	printf("read %ld bytes from buffer\n",ans);
	
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("struct empty? %d\n", CBuffIsEmpty(cyc_buff));

	printf("\n-------------------writing to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,10);
	printf("written %ld bytes\n", ans);
	
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	
	printf("\n-------------------reading from buffer-------------------------------\n");
	ans = CBuffRead(cyc_buff,dest,2);
	printf("read %ld bytes from buffer\n",ans);
	
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));

	printf("\n-------------------writing to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,5);
	printf("written %ld bytes\n\n", ans);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));

	printf("\n-------------------writing 10 more to buffer-------------------------------\n");
	ans = CBuffWrite(cyc_buff,string,10);
	printf("written %ld bytes\n\n", ans);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	

	/*
	ans = CBuffWrite(cyc_buff,string,5);
	printf("written bytes %ld\n\n", ans);

	
	printf("%s\n",(*(char**)&(cyc_buff) + 24));
	printf("%s\n",((char *)cyc_buff + 24));*/
	/*printf("%s\n",dest);*/


	CBuffDestroy(cyc_buff);
	return 0;
}