#include <stdio.h>  /*     standard library, because why not  */
#include <stdlib.h> 
#include <assert.h> /*     test assertions made  */
#include <string.h> /* to test str-related funcs & stop crying */

#include "ptr_2.h"

const int aA=32;    /* the difference between upper case and lower case */

char * StrCpy(char* destination, const char* source)
{
	
	size_t length_src= StrLen(source)+1;
	char *ptr = destination; 
	assert(NULL != destination);
	assert(NULL != source);
	ptr = StrnCpy(destination,source,length_src);
	return ptr;
	
}

char * StrnCpy(char *dest, const char *src, size_t n)
{
	char * ptr_dest= dest+n;
	char *ptr_s= dest;
	while (dest < ptr_dest) 
	{
		if ('\0' != *src)
		{
			*dest = *src;
			++dest;
			++src;
		}
		else
		{
			*dest = '\0';
			++dest;
		}
	}
	return ptr_s;
}
/* man version
char * StrnCpy(char *dest, const char *src, size_t n)
           {
               size_t i;

               for (i = 0; i < n && src[i] != '\0'; i++)
                   dest[i] = src[i];
               for ( ; i < n; i++)
                   dest[i] = '\0';

               return dest;
           }

*/

int StrCaseCmp(const char *str1, const char *str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	while (*str2 && ( (*str1 - *str2 == aA) || (*str2 - *str1 == aA) || (*str1 == *str2) ))
	{
	  str1++;
	  str2++;
	}
   return (*str1 - *str2);

}

char * StrChr(const char *str, int ch)
{
	assert(NULL != str);
	while('\0' != *str)
	{
		if (*str == ch)
		{
			return (char *)str;
		}
		str++; 
	}
	if (*str == ch)
		return (char *)str;	
	return NULL;
}


size_t StrSpn(const char *s, const char *accept)
{
	
	size_t counter= 0;
	while (('\0' != *s) && (StrChr(accept,*s) != NULL))
	{
		++s;
		++counter;	
	}		
	return counter;

}


size_t StrLen(const char *str)
{
	size_t size=0;
	while(*str && str++ && ++size);
	return size;
}

char* StrDup(const char *s)
{
	size_t length= StrLen(s);
	char* dup=(char*)malloc(length*sizeof(char)+1);
	dup= StrnCpy(dup,s,length);
	return dup;
}

char * StrCat(char *dest, const char *src)
{
	
	size_t length_src = StrLen(src);
	return StrnCat(dest,src,length_src);
}

char * StrnCat(char *dest, const char *src, size_t n)
{
	size_t length_dest = StrLen(dest);
	char *ptr = dest + length_dest;
	StrnCpy(ptr,src,n);
	return dest;
}

/* man versio
char * StrnCat(char *dest, const char *src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

   return dest;
}
*/
int StrnCmp (const char *str1,const char *str2)
{
	int x = StrLen(str2);
	while ((*str2 == *str1) && (0<x))
	{
	  str1++;
	  str2++;
	  --x;
	}
	
   return x;
}

char * StrStr (const char * haystack, const char * needle)
{
	while ('\0' != *haystack)
	{
		char * ptr_st= StrChr(haystack,needle[0]);
		int x = StrnCmp(ptr_st,needle);
		if(0==x)
			return ptr_st;
	haystack++;
	}		
return NULL;
}

void isPalindrome(char* string)
{
	size_t length= strlen(string);
	char * start= string;
	char * end= string+length-1;
	
	while ((start<=end) && (*start == *end))
	{
		start++;
		--end;
	}
	if(start>end)
	{
		printf("%s is a palindrome\n", string);
	}
	else
	{
		printf("%s is NOT a palindrome\n", string);
	}
	
}
























