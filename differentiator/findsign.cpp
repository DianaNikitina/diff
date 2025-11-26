#include "diff.h"

char* find_sign(char* diff, int* position)
{
    char* sign = (char*)calloc(100, sizeof(char));
    int i = 0;

    // sscanf("%[^\"]%n", word, &n)

    while (diff[*position] != '\"')
    {
        sign[i] = diff[*position];
        //printf(">%c\n", word[i]);
        (*position)++;
        i++;
    }
    return sign;
}