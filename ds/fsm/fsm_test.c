
#include <stdio.h>    /* printf */
#include <string.h> /* strlen*/

#include "fsm.h"

int main()
{
	char *str = "01110";
	char *str2 = "1100";
	char *str3 = "0";
	char *str4 = "1111111";
	char *a_str = "0000000000000000001";
	char *b_str = "0000000011100000000";

	(CheckValidity(str) == Q2 ? printf("%s\t ACCEPTED!\n", str): printf("%s NOT accepted\n", str));
	(CheckValidity(str4) == Q2 ? printf("%s\t ACCEPTED!\n", str4): printf("%s NOT accepted\n", str4));
	(CheckValidity(str2) == Q2 ? printf("%s\t ACCEPTED!\n", str2): printf("%s NOT accepted\n", str2));
	(CheckValidity(str3) == Q2 ? printf("%s\t ACCEPTED!\n", str3): printf("%s NOT accepted\n", str3));
	
	(CheckValidity(a_str) == Q2 ? printf("%s\t ACCEPTED!\n", a_str): printf("%s NOT accepted\n", a_str));
	(CheckValidity(b_str) == Q2 ? printf("%s\t ACCEPTED!\n", b_str): printf("%s NOT accepted\n", b_str));
	
	return 0;
}


