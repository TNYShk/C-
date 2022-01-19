#include <stdio.h> /* print*/
#include <stdlib.h> /* system() hide func*/


#include "listen2keys.h"

#define ASCIT (256)
#define ESC (27)
#define HIDE (system("stty -icanon -echo"))
#define UNHIDE (system("stty icanon echo");)

typedef void (*foo)(char);
typedef void (*ptr_to_func)(void);

static void DoNothing(void);




void iAT(void)
{
	char cc=' ';
	system("stty -icanon -echo");
	while (cc != ESC)
	{
		while((cc != 'T') && (cc != 'A'))
		{
			cc = getc(stdin);
		}
		printf("%c-pressed! Well hello there\n",cc);
		cc = getc(stdin);
	}

	system("stty icanon echo");
}

void ifAT(void)
{
	char cc =' ';
	system("stty -icanon -echo");
	
	while (cc != ESC)
	{
		cc = getc(stdin);

		if((cc == 'A') || (cc == 'T'))
		{
			printf("%c-pressed!\n",cc);
		}
	}
	system("stty icanon echo");

}

void PrintAT(void)
{
	char cc = ' ';
	system("stty -icanon -echo");
	
	while(1)
	{
		cc = getc(stdin);
		
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
	if( c == 'A' || c == 'T')
	{
		printf("%c is Bananna also %c pressed\n",c,c);
	}
}

static void DoNothing(void)
{
	printf("\n\t");
}


void ActionFunc()
{
	char cc = ' ';
	int i = 0;

	ptr_to_func lut_of[ASCIT];
	foo lut[ASCIT] = {0};

	ptr_to_func nada = DoNothing;
	ptr_to_func a_t_pressed = ifAT;
	

	for(i = 0;i < ASCIT; ++i)
	{
		lut_of[i] = nada;
		lut[i] = PrintChar;
	}
	lut_of['A'] = a_t_pressed;
	lut_of['T'] = a_t_pressed;

	system("stty -icanon -echo");
	
	while((cc = getc(stdin)) != ESC)
	{
		lut[(unsigned char)cc](cc);
	}
	
	system("stty icanon echo");
	
}


