#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ilrd_string.h"

int StrLen (const char *str)
{
	int size=0;
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
	
	assert((*str1) && (*str2));
	while (*str2 && (*str1 == *str2))
	{
	  str1++;
	  str2++;
	}
   return (*str1 - *str2);
}

