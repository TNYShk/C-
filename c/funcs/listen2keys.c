#include <stdio.h> /* print*/
#include <stdlib.h> /* system() hide func*/


#include "listen2keys.h"

#define ASCIT (256)
#define ESC (27)
#define HIDE (system("stty -icanon -echo"))
#define UNHIDE (system("stty icanon echo"))

typedef void (*foo)(char);
typedef void (*ptr_to_func)(void);

static void DoNothing(void);
static void PrintT(void);
static void PrintA(void);



void iAT(void)
{
	char cc = ' ';
	HIDE;

	while (cc != ESC)
	{
		while((cc != 'T') && (cc != 'A'))
		{
			cc = getc(stdin);
		}
		printf("%c-pressed! Well hello there\n",cc);
		cc = getc(stdin);
	}

	UNHIDE;
}

void ifAT(void)
{
	char cc =' ';
	HIDE;
	
	while (cc != ESC)
	{
		cc = getc(stdin);

		if((cc == 'A') || (cc == 'T'))
		{
			printf("%c-pressed!\n",cc);
		}
	}
	UNHIDE;

}

void PrintAT(void)
{
	char cc = ' ';
	HIDE;
	
	while(1)
	{
		cc = getc(stdin);
		
		switch(cc){
			case (ESC):
				UNHIDE;
				return;
			case 'A':
			case 'T':
			printf("%c pressed!! \n\tplease don't dump my core\n",cc);
		}
	}
	
}

void PrintChar(char c)
{
	if( c == 'A' || c == 'T')
	{
		printf("%c is Bananna also %c pressed\n",c,c);
	}
}

static void DoNothing(void)
{
	printf("\n\t");
}

static void PrintA(void)
{
	printf("AAA\n");
}

static void PrintT(void)
{
	printf("TT\n");
}


void ActionFunc()
{
	char cc = ' ';
	int i = 0;

	ptr_to_func lut_of[ASCIT];
	

	ptr_to_func nada = DoNothing;
	ptr_to_func a_pressed = PrintA;
	ptr_to_func t_pressed = PrintT;

	for(i = 0;i < ASCIT; ++i)
	{
		lut_of[i] = nada;
		
	}
	lut_of['A'] = a_pressed;
	lut_of['T'] = t_pressed;

	HIDE;
	
	while((cc = getc(stdin)) != ESC)
	{
		lut_of[(unsigned char)cc]();
	}
	
	UNHIDE;
	
}


