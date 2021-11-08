#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ilrd_string.h"

size_t StrLen (const char *str)
{
	size_t size=0;
	while(*str && str++ && ++size);
	
	/* old version
	while('\0' != *str)
	{
		str++;
		size++;
	}
	*/ /*old version end */
	
	
   return size;
	
}

int StrCmp (const char *str1,const char *str2)
{
	
	assert(NULL !=str1); 
	assert(NULL != str2);
	while (*str1 && (*str1 == *str2))
	{
	  ++str1;
	  ++str2;
	}
   return (*str1 - *str2);
}

