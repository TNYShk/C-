#include <time.h> /*time_t */
#include <stdio.h> /*printf */
#include <assert.h> /* assert() */

int main(void)
{
	char arr[] = {0x83, 0x82 ,0x81, 0x80, 0x70, 0x60, 0x50, 0x40};
	unsigned long num = *(unsigned long *)arr;
	char result;
	short *sptr = (short *)&num;
	printf("sptr: %d\n", *(short *)&num);
	sptr += (sizeof(num) >> 2);
	result = *sptr;
	printf("%d\n", result);
	printf("%d\n", 8>>2);
	return 0;
}


