
#include <stdio.h>    /* printf */
#include <string.h> /* strlen*/



int CheckValidity(const char *string);



typedef enum 
{
	START,
	BLACKHOLE,
	Q1,
	Q2

}fsm_state;

typedef struct event
{
	char input;
	fsm_state output;

}event_t;

typedef struct fsm
{
	fsm_state fsm_cur_state;
	event_t fsm_state_change[2];
}fsm_t;

static const fsm_t FiniteStateM[] = 
{
	{START, {{'1', BLACKHOLE}, {'0', Q1}} },
	{BLACKHOLE, {{'1', BLACKHOLE},{'0', BLACKHOLE}} },
	{Q1,{{'1', Q1},{'0', Q2}} },
	{Q2, {{'1', Q1},{'0', Q2}} }
};

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

int CheckValidity(const char *string)
{
	int cur_state = START;
	size_t length = strlen(string);
	const char *runner = string;
	size_t index = 0;

	while(length && (cur_state != BLACKHOLE))
	{
		while(FiniteStateM[cur_state].fsm_state_change[index].input != *runner)
		{
			++index;
		}
		cur_state =  FiniteStateM[cur_state].fsm_state_change[index].output;

		--length;
		++runner;
		index = 0;
	}

	return cur_state;
}

