#include <stdio.h> /* printf */
#include <string.h>
#define SPACE (32)
#define NULL_CHARACTER_TERMINATOR (1)

void Reverse(char *start, char *end)
{
    char temp = '\0';
    while (start < end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}

void ReverseString(char *str)
{
    char *end = str + strlen(str) - NULL_CHARACTER_TERMINATOR;
    char *word_beg = str;
    char *word_end = NULL;
    int exit_flag = 0;
    Reverse(str, end);
    do
    {
        word_end = strchr(word_beg, SPACE);
        
        if (NULL == word_end)
        {
            word_end = end + 1; /* becuase end point to the character before '\0' */
            exit_flag = 1;
        }
        
        Reverse(word_beg, word_end - 1);
        word_beg = word_end + 1;
        
    } while(!exit_flag);
}

int main()
{
    char string[]="Green Forever";

    printf("before: %s \n",string);
    ReverseString(string);
    printf("after: %s \n",string);


    return 0;
}