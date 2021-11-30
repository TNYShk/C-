#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "wbo.h"

#define WORD_SIZE (sizeof(size_t))

void *MemSet(void *s, int c, size_t n)
{
	size_t word = c;
	char *byte_ptr= (char *)s;
	size_t toalign = ((size_t)byte_ptr %WORD_SIZE);
	size_t tail= n % WORD_SIZE;
	size_t wordalign= n/WORD_SIZE;
	word *= 0x0101010101010101;
	
	
	while(toalign)
	{
		*byte_ptr = (unsigned char)c;
		++byte_ptr;
		--toalign;
	}

	while(wordalign > 0)
	{
		*(size_t*)byte_ptr = word;
		(size_t)byte_ptr++;
		--wordalign;
		--n;
	}

	while(tail)
	{
		*byte_ptr = (unsigned char)c;
		++byte_ptr;
		--tail;
	}
return s;
}
/*
void *MemCpyByte(void *dest, const void *src, size_t n)
{
	const char *src_ptr = (char*)src;
	char *runner = (char*)dest;
	
	while(n)
	{
	*runner++ = *src_ptr++;
	--n;
	}
	return dest;
}*/

void *MemCpy(void *dest, const void *src, size_t n)
{
	void *runner = dest;
	size_t num_words = n/ sizeof(size_t);

	while(num_words)
	{
		*(*(size_t**)&runner) = *(size_t*)src;
		++(*(size_t**)&runner);
		++(*(size_t**)&src);
		n -= sizeof(size_t);
		--num_words;	
	}

	
	while(n)
	{
		*(*(char**)&runner) = *(char*)src;
		++(*(char**)&runner);
		++(*(char**)&src);
		--n;
	}

	return dest;
}


void *MemMove(void *dest, const void *src, size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);

	if( (size_t)&src + n > (size_t)&dest)
	{
		printf("attention! source overflows destination\n");
	}

    if(dest > src)
    {
        if((*(size_t*)&dest) - (*(size_t*)&src) > n)
        {
            return MemCpy(dest, src, n);
        }

        while(n)
        {
            --n;
            *(*(char **)&dest + n) = *(*(char **)&src + n);
        }
    }

    else if(dest < src)
    {
        size_t check = 0;
        if(*(size_t*)&src - (*(size_t*)&dest)  > n)
        {
           return MemCpy(dest, src, n);
        }

        while (check < n)
        {
             *(*(char **)&dest + check) = *(*(char **)&src + check);
             ++check;
        }
    }
    return dest;
}



int main()
{
	char str[]= "Hellooo";
	const char srr[]= "source123456789";
	
	/*MemSet(str,'F', 1);
	MemCpy (str,srr,9);
	memcpy(str,srr,0);
	memmove(str,srr,20);
	MemMove(str,srr,20);
	*/
	MemMove(str,srr,3);
	
	printf("%s\n",str);
	return 0;
}


