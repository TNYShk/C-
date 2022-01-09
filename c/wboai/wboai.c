#include <stdio.h>  /******* printing ****************/
#include <string.h> /******* strncpy *****************/
#include <stdlib.h> /******* atoi, memory allocation */
#include <assert.h> /******* assert viability ********/
#include <ctype.h>  /******* isalnum, isdigit ********/

#include "wboai.h"


#define DECIM (10)
#define ASCII (256)
#define ZERO ('0')
#define CAP_LETTER ('A')

#define MIN2(a,b) ((a)<(b)?(a):(b))

#define IS_LITTLE_ENDIAN (*(int *)&("=1") != 0 ) 




void PrintFromArrays(char *a, char *b, char *c, size_t a_arr, size_t b_arr, size_t c_arr)
{
	
	size_t i = 0;
	int ascii[ASCII] = {0};

	assert (NULL != a);
	assert (NULL != b);
	assert (NULL != c);

	for (i = 0; i < a_arr; ++i)
	{
		ascii[(int)a[i]]= 1;
	}
	for (i = 0; i < b_arr; ++i)
	{
		ascii[(int)b[i]] += 5;
	}
	for(i = 0; i < c_arr; ++i)
	{
		ascii[(int)c[i]] = 0; 
	}
	for (i = 0; i < ASCII; ++i)
	{
		if(ascii[i] > 5)
			printf(" %c ",(char)i);
	}
}




static void Reverse(char *str, size_t length)
{
	char *start = str;
	char *end = str + length - 1;
		
	while (start < end)
	{
		char t = *start;
		*start = *end; 
		*end = t;
		++start;
		--end;
	}
}


char *ItoaIntToStrBase(int value, char *str, unsigned int base)
{
	char *ptr = str;
	int i = 0;
	size_t len = 0;
	char flag = '\0';
	
	assert(NULL != str);
	
	if(0 > value)
	{
		value= -value;
		flag = '-';
	}
	
	while(value)
	{
		char leftover = value % base;

		if (leftover > 9)
		{
			leftover -= DECIM;
			leftover += CAP_LETTER;
			*(ptr+i) = leftover;
		}
		else
		{
			leftover += ZERO;
			*(ptr + i) = leftover;
		}

	value /= base;
	++i;
	
	}
	*(ptr + i) = flag;
	len = strlen(str);
	Reverse(str,len);
	
	return str;
}

int AtoiStrToIntBase(const char *nptr, unsigned int base)
{
	int num = 0;
	int i = 0;
	int sign = 1;

	assert(NULL != nptr);
	
	while (isspace(nptr[i]))
	{
		++i;
	}
	if ( nptr[i] == '-')
	{
		sign = -1;
		++i;
	}

	while (isalnum(nptr[i]))
	{
		if (isdigit(nptr[i]))
		{
			num *=  base;
			num += (nptr[i] - ZERO);
		}
		else
		{
			num = (num * base) + toupper(nptr[i]) - CAP_LETTER + DECIM;
		}

		++i;
	} 
	
	return sign * num;		
}
	


int AtoiStrToInt(const char *nptr)
{
	assert(NULL != nptr);

	return (AtoiStrToIntBase(nptr,10));  

}


char *ItoaIntToStr(int value, char *str)
{
	assert(NULL != str);
	
	return ItoaIntToStrBase(value, str, 10);
	
}

int IsLittleEndian(void)
{
	int num = 1;
	char *indian = (char *)&num;
        
    return (indian[0] == 1);
}

/* previous version, works but not as efficient
void PrintFromArrays(char *a, char *b, char *c, size_t a_arr, size_t b_arr, size_t c_arr)
{

	int i = 0;
	size_t shorter = MIN2(a_arr, b_arr);
	size_t bigger = a_arr + b_arr - shorter;
	
	char *temp = NULL; 
	char *a1 = NULL;
	char *a2 = NULL;
	char *a3 = NULL;
	
	temp = (char*)calloc(shorter, sizeof(char*));
	a1= (char*)calloc(a_arr+1, sizeof(char*));
	a2 = (char*)calloc(b_arr+1, sizeof(char*));
	a3 = (char*)calloc(c_arr+1, sizeof(char*));
	
	strncpy(a1,a,a_arr);
	strncpy(a2,b,b_arr);
	strncpy(a3,c,c_arr);
	
	assert (NULL != temp);
	assert (NULL != a1);
	assert (NULL != a2);
	assert (NULL != a3);

	while(bigger)
	{
		if (NULL != strchr(a1,*(a2+i)))
		{
			*(temp +i) = *(strchr(a1,*(a2+i)));
		}
			++i;
			--bigger;
	}
	i=0;
	
	while (shorter)
	{
		if (NULL == strchr(a3,*(temp+i)))
		{
			printf("%c ", temp[i]);
		}
		--shorter;
		++i;
	}
	
	free(temp);
	free(a1);
	free(a2);
	free(a3);
	a1 = NULL;
	a2 = NULL;
	a3 = NULL;
	temp = NULL;
	
}*/