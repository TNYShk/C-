#include <stdio.h>
#include <stddef.h>
#include <string.h>


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
	const char* src_ptr= (char*)src;
	char *rub = (char *)dest;
	size_t num_words= n/ sizeof(size_t);

	while(num_words)
	{
		*(*(size_t**)&runner) = *(size_t*)src;
		++(*(size_t**)&runner);
		++(*(size_t**)&src);
		n -= sizeof(size_t);
		--num_words;	
	}

	rub = (char*)runner;
	src_ptr = (char*)src;
	
	while(n)
	{
		*rub++ = *src_ptr++;
		--n;
	}

	return dest;
}


void *MemMove(void *dest, const void *src, size_t n)
{

    if(src < dest)
    {
        if((*(size_t*)&dest) - (*(size_t*)&src) > n)
        {
            return MemCpy(dest, src, n);
        }

        while(0 < n)
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
	char str[]= "Hellooooooo";
	const char srr[]= "source123456789";
	size_t len = (sizeof(srr) -1);
	printf("len is %ld\n", len);
	/*MemSet(str,'F', 1);
	MemCpy (str,srr,5);
	memcpy(str,srr,0);
	memmove(str,srr,20);
	
	*/
	MemMove(str,srr,20);
	printf("%s\n",str);
	return 0;
}


