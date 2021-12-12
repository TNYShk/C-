#include <stdio.h> /* printf */

#include "ilrd_string.h"




int main(){

const char word[] = "tatyanna  ";
const char another_word[] = "Tatyanna";
size_t size = 0, cmp_size = 0;
/*size = (sizeof(word)-1);
printf("word length is %d\n",size);
*/
size = StrLen(word);
printf("word is: %s and its length is %lu\n", word, size);
printf("another word is: %s length is %lu\n",another_word,StrLen(another_word));

cmp_size = StrCmp(word,another_word);
printf("StCmp func,(if equals 0 its good).\fwords compared: %lu\n",cmp_size);
return 0;
}
