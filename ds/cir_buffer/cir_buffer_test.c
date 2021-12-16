#include <unistd.h> /* size_t ssize_t*/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* offsetof*/

#include "cir_buffer.h"



int main(void)
{
	
	cbuffer_t *cyc_buff = NULL;
	
	char *string = "hello";
	ssize_t ans = 0;

	cyc_buff  = CBuffCreate(10);

	assert (NULL != cyc_buff);

	printf("capacity struct = %ld\n",CBuffCapacity(cyc_buff));
	
	printf("struct empty? %d\n", CBuffIsEmpty(cyc_buff));
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	
	ans = CBuffWrite(cyc_buff,string,3);
	printf("written ans is %ld\n", ans);
	printf("struct free space = %ld\n", CBuffFreeSpace(cyc_buff));
	printf("struct empty? %d\n", CBuffIsEmpty(cyc_buff));

	CBuffDestroy(cyc_buff);
	return 0;
}