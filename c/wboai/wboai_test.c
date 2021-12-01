#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wboai.h"


void TestItoa();
void TestItoaBase();
void TestAtoi();
void TestAtoiBase();
void CompareAtoiWithSystem(char *str);
void CheckExc2();
void CheckEndian();


int main()
{
	printf("------------------------------Test Itoa:------------------------------\n\n");
	TestItoa();
	printf("\n------------------------------Test Itoa base:------------------------------\n\n");
	TestItoaBase();
	printf("\n------------------------------Test Atoi:------------------------------\n\n");
	TestAtoi();
	printf("\n------------------------------Test Atoi base:------------------------------\n\n");
	TestAtoiBase();
	printf("\n------------------------------Test Exc 2:------------------------------\n\n");
	CheckExc2();
	printf("\n------------------------------Test Check Endian:------------------------------\n\n");
	CheckEndian();
	
	
	return 0;
}


void TestItoa()
{
	char strr[20] = " ";
	char strr2[20] = " ";
	char strr3[20] = " ";
	
	ItoaIntToStr(26000, strr);
	ItoaIntToStr(-338, strr2);
	ItoaIntToStr(14888, strr3);
	
	printf("%s\n", strr);
	printf("%s\n", strr2);
	printf("%s\n", strr3);
	
	
}


void TestAtoi()
{
	char str[] = "     -1999";
	char str2[] = "-345";
	char str3[] = "54/45";
	char str4[] = "/54";
	char str5[] = "4   55";
	
	CompareAtoiWithSystem(str);
	printf("\n");
	CompareAtoiWithSystem(str2);
	printf("\n");
	CompareAtoiWithSystem(str3);
	printf("\n");
	CompareAtoiWithSystem(str4);
	printf("\n");
	CompareAtoiWithSystem(str5);
}

void TestItoaBase()
{
	char *str = malloc(sizeof(char) * 33);
	char *str2 = malloc(sizeof(char) * 33);
	char *str3 = malloc(sizeof(char) * 33);
	
	str = ItoaIntToStrBase(3, str, 2);
	str2 = ItoaIntToStrBase(1779, str2, 10);
	str3 = ItoaIntToStrBase(4777, str3, 24);
	
	printf("3 base 2 %s\n", str);
	printf("1779 base 10 %s\n", str2);
	printf("4777 base 24 %s\n", str3);
	
	free(str);
	free(str2);
	free(str3);
}


void TestAtoiBase()
{
	char *str = " 11";
	char *str2 = "123AB";
	char *str3 = "-1712";
	char *str4 = "  -**ADD33Q";
	
	printf("%d\n", AtoiStrToIntBase(str, 2));
	printf("%d\n", AtoiStrToIntBase(str2, 16));
	printf("%d\n", AtoiStrToIntBase(str3, 10));
	printf("%d\n", AtoiStrToIntBase(str4, 17));
}


void CompareAtoiWithSystem(char *str)
{
	int num = AtoiStrToInt(str);
	int num2 = atoi(str);
	
	printf("System's atoi: %d\n", num2);
	printf("My atoi: %d\n", num);
}


void CheckExc2()
{
	char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '$'};
	char arr2[] = {'a', 'd', 'q', 't', '$', '!',' ','h'};
	char arr3[] = {'q', 'q', 'w', '!', '@', '#'};
	
	
	PrintFromArrays(arr, arr2, arr3, sizeof(arr),sizeof(arr2),sizeof(arr3));
}


void CheckEndian()
{
	if (IsLittleEndian())
	{
		printf("Little Endian!\n");
	}
	else
	{
		printf("Big Endian!\n");
	}
}