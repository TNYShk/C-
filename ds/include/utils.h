#ifndef __UTILS_H__
#define __UTILS_H__

#define GREEN printf("\033[0;32m");

#define BOLD_GREEN printf("\033[1;32m");

#define BLUE printf("\033[0;34m");

#define RED printf("\033[0;31m");

#define BOLD_RED printf("\033[1;31m");

#define WHITE printf("\033[0;37m");

#define TRUE (1)

#define FALSE (0)

#define SUCCESS (0)

#define FAILURE (1)

#define MALLOC_FAIL (2)

#define MAX(a,b) ((a > b) ? (a) : (b))

#define MIN(a,b) ((a > b) ? (b) : (a))

#define TEST_NOT_NULL(var){\
	if(NULL != (var))\
	{\
		GREEN;\
		printf("Not NULL test - SUCCESS\n");\
		WHITE;\
	}\
	else\
	{\
		BOLD_RED;\
		printf("Not NULL test - FAILURE - line %d file %s\n", __LINE__, __FILE__);\
		WHITE;\
	}\
}\

#define TEST_IS_NULL(var){\
	if(NULL == (var))\
	{\
		GREEN;\
		printf(" NULL test - SUCCESS\n");\
		WHITE;\
	}\
	else\
	{\
		BOLD_RED;\
		printf("Not NULL test - FAILURE - line %d file %s\n", __LINE__, __FILE__);\
		WHITE;\
	}\
}\

#define CONDITION_TEST(left, right){\
	if ((left) == (right))\
	{\
		GREEN;\
		printf("Condition test - SUCCESS\n");\
		WHITE;\
	}\
	else\
	{\
		BOLD_RED;\
		printf("Condition test - FAILURE - line %d file %s\n", __LINE__, __FILE__);\
		WHITE;\
	}\
}\

#define PRINT_ARR(arr, arr_size){\
	size_t index = 0;\
	for(index = 0; arr_size > index; ++index)\
	{\
		printf("%d\n",arr[index]);\
	}\
}\

#define RAND_ARR(arr, arr_size, modulo){\
	size_t index = 0;\
	for(index = 0; arr_size > index; ++index)\
	{\
		arr[index] = rand()%modulo;\
	}\
}\

#endif
