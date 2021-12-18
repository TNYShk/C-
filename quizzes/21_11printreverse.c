#include <stdio.h> /* printf */
#include <string.h>
#include <stdlib.h>
#define SPACE (32)
#define NULL_CHARACTER_TERMINATOR (1)

static void Reverse(char *start, char *end);
void ReverseString(char *str);

/*seg faults*/
void ReverseWords(char *);



int main()
{
    
    char string[]="Green Forever";
   
    printf("before: %s \n",string);
    ReverseString(string);
    printf("after: %s \n",string);

    return 0;
}



static void Reverse(char *start, char *end)
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

/* seg fault
void ReverseWords(char *str)
{
    char *rev = (char *)calloc(sizeof(str),1);
    
    int i = 0, index = 0, word_start = 0, word_end = 0;
   size_t len = strlen(str);
   printf("len %ld\n", len);
   
    word_start = len -1;
    word_end = len - 1;
    
    while(word_start > 0)
    {
        if(str[word_start] == ' ')
        {
            i = word_start + 1;

            while(1 <= word_end)
            {
                rev[index] = str[i];
                ++i;
                ++index;
            }
            rev[index++] = ' ';

            word_end = word_start - 1;
        }
        --word_start;
    }

    for(i = 0; i<= word_end; ++i)
    {
        rev[index] = str[i];
        ++index;
    }

    rev[index] = '\0';
    printf("%s", rev);
    free(rev);
    rev = NULL;

}
*/