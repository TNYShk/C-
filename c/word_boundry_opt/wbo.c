#include <stdio.h>  /***sizeof****/
#include <stddef.h> /* size_t */
#include <assert.h> /* asserting pointers*/

#include "wbo.h"

#define WORD_SIZE (sizeof(size_t))


void *MemSet(void *s, int c, size_t n)
{
	size_t word = c;
	char *byte_ptr = NULL;

	size_t toalign = ((size_t)byte_ptr % WORD_SIZE);
	size_t wordalign = n / WORD_SIZE;
	
	assert(NULL != s);

	byte_ptr = (char *)s;
	word *= 0x0101010101010101;
	
	while (n)
	{

		if ((wordalign > 0) && (0 == toalign))
		{
			*(size_t *)byte_ptr = word;
			++(*(size_t **)&byte_ptr);
			--wordalign;
			n -= WORD_SIZE;
		}
		else 
		{
			*byte_ptr = (unsigned char)c;
			++byte_ptr;
			--n;
		}
	}
	return s;
}


void *MemCpy(void *dest, const void *src, size_t n)
{

	void *runner = NULL;
	size_t num_words = n / sizeof(size_t);
	
	assert(NULL != dest);
	assert(NULL != src);
	
	runner = dest;
	
	while(num_words)
	{
		*(*(size_t **)&runner) = *(size_t *)src;
		++(*(size_t **)&runner);
		++(*(size_t **)&src);
		
		n -= WORD_SIZE;
		--num_words;	
	}

	
	while(n)
	{
		*(*(char **)&runner) = *(char *)src;
		++(*(char **)&runner);
		++(*(char **)&src);
		--n;
	}

	return dest;
}


void *MemMove(void *dest, const void *src, size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);

    if(dest > src)
    {
        while(n)
        {
            --n;
            *(*(char **)&dest + n) = *(*(char **)&src + n);
        }
    }

    else if(dest < src)
    {
    	return MemCpy(dest, src, n);
        
    }
  
	return dest;
}






