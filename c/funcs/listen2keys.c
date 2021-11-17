#include <stdio.h>
#include <stdlib.h>


#include "listen2keys.h"

#define UNSC 256
#define ESC 27
typedef void (*foo)(char);

void iAT()
{
	char cc=' ';
	system("stty -icanon -echo");
	while (cc != ESC)
	{
		while((cc !='T') && (cc !='A'))
		{
			cc= getc(stdin);
		}
		printf("%c-pressed! Well hello there\n",cc);
		cc= getc(stdin);
	}

	system("stty icanon echo");
}

void ifAT()
{
	char cc=' ';
	system("stty -icanon -echo");
	
	while (cc !=ESC)
	{
		cc= getc(stdin);

		if((cc == 'A') || (cc =='T'))
		{
			printf("%c-pressed! Yey Timo\n",cc);
		}
	}
	system("stty icanon echo");

}

void PrintAT()
{
	char cc = ' ';
	system("stty -icanon -echo");
	
	while(1)
	{
		cc=getc(stdin);
		
		switch(cc){
			case (ESC):
				system("stty icanon echo");
				return;
			case 'A':
			case 'T':
			printf("%c pressed!! \n\tplease don't dump my core\n",cc);
		}
	}
	
}

void PrintChar(char c)
{
	if( c== 'A' || c== 'T')
	{
		printf("%c is Bananna also %c pressed\n",c,c);
	}
}


void ActionFunc()
{
	char cc;
	int i;
	foo lut_of[UNSC];
	
	for(i=0;i<UNSC;i++)
	{
		lut_of[i]=PrintChar;
	}
	
	system("stty -icanon -echo");
	
	while((cc=getc(stdin)) != ESC)
	{
		lut_of[(unsigned char)cc](cc);
	}

	system("stty icanon echo");
}

