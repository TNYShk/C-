#include <stdlib.h> /* size_t, dyncamic memory allocation  */
#include <stdio.h> /* printf */
#include <assert.h> /* asserts */
#include <string.h>	/* strlen, memcpy check*/

#define WORD_SIZE (sizeof(size_t))

void TestOne();
void TestTwo();
void TestThree();
void *Mem_Cpy(void *dest, const void *src, size_t nbytes);


int main (void)
{
	
	TestOne();
	TestTwo();
	TestThree();

	return 0;
}

void TestOne()
{
	char *string = "Hello there!";
	char destin[] = "one two three four five";
	printf("\n\t**********************Test One ***************************\n");
	Mem_Cpy(destin, string, 9);
	printf("%s\n", destin);
}

void TestTwo()
{
	char *string = "@@@Hello there!";
	char destin[] = "one two three four five";
	
	char *str_dest = NULL;
	str_dest = (char *)calloc(strlen(destin) + 1 , 1);
	assert(NULL != str_dest);
	printf("\n\t**********************Test Two ***************************\n");
	
	Mem_Cpy(str_dest, destin, 11);
	printf("%s\n", str_dest);

	Mem_Cpy(destin, string, 5);
	printf("%s\n", destin);

	free(str_dest);
	str_dest = NULL;
}

void TestThree()
{
	
	char *string = "Hello there!";
	char destin[] = "one two three four five";
	char *str_dest = (char *)calloc(strlen(destin) + 1 , 1);
	assert(NULL != str_dest);
	printf("\n\t**********************compare to memcpy:***************************\n");
	
	memcpy(str_dest, destin, 11);
	printf("memcpy:\n%s\n", str_dest);

	memcpy(destin, string, 9);
	printf("memcpy:\n%s\n", destin);

	free(str_dest);
	str_dest = NULL;
}



void *Mem_Cpy(void *dest, const void *src, size_t nbytes)
{
	void *dest_runner = dest;
	size_t unaligned_dest = ((size_t)( char *)dest % WORD_SIZE);
	size_t words = nbytes / WORD_SIZE;
	
	assert (NULL != dest);

	while (unaligned_dest)
	{
		*(*(char **)&dest_runner) = *(char *)src;
		++(*(char **)&dest_runner);
		++(*(char **)&src);
		-- unaligned_dest;
		--nbytes;
	}
	while(words)
	{
		*(*(size_t **)&dest_runner) = *(size_t *)src;
		++(*(size_t **)&dest_runner);
		++(*(size_t **)&src);
		nbytes -= WORD_SIZE;
		--words;
	}
	while(nbytes)
	{
		*(*(char **)&dest_runner) = *(char *)src;
		++(*(char **)&dest_runner);
		++(*(char **)&src);
		--nbytes;
	}
	
	return dest;


}