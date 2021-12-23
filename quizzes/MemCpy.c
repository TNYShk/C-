#include <stdlib.h> /* size_t, dyncamic memory allocation  */
#include <stdio.h> /* printf */
#include <assert.h> /* asserts */
#include <string.h>	/* strlen, memcpy check*/

#define WORD_SIZE (sizeof(size_t))

void TestOne();
void TestTwo();
void *Mem_Cpy(void *dest, const void *src, size_t nbytes);


int main (void)
{
	
	TestOne();
	TestTwo();

	return 0;
}

void TestOne()
{
	char *string = "Hello there!";
	char destin[] = "one two three four five";
	Mem_Cpy(destin, string, 9);
	printf("%s\n", destin);

}

void TestTwo()
{
	char *string = "@@@Hello there!";
	char destin[] = "one two three four five";
	
	char *str_dest = NULL;
	str_dest = (char *)calloc(strlen(destin) + 1 , 1);

	Mem_Cpy(str_dest, destin, 8);
	printf("%s\n", str_dest);
	Mem_Cpy(destin, string, 7);
	printf("%s\n", destin);

	free(str_dest);
	str_dest = NULL;


}



void *Mem_Cpy(void *dest, const void *src, size_t nbytes)
{
	const void *src_runner = src;
	void *dest_runner = dest;
	size_t words = nbytes / WORD_SIZE;

	assert (NULL != dest);

	while(words)
	{
		*(*(size_t **)&dest_runner) = *(*(size_t **)&src_runner);
		++(*(size_t **)&dest_runner);
		++(*(size_t **)&src_runner);
		nbytes -= WORD_SIZE;
		--words;
	}
	while(nbytes)
	{
		*(*(char **)&dest_runner) = *(*(char **)&src_runner);
		++(*(char **)&dest_runner);
		++(*(char **)&src_runner);
		--nbytes;
	}

	

	
	return dest;


}