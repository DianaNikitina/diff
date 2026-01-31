#include "diff.h"

int match_word(char** ptr, const char* word)
{
    char* saved_ptr = *ptr;
    
    skip_spaces(ptr);
    
    const char* w = word;
    while (*w != '\0') 
    {
        if (**ptr != *w) 
        {
            *ptr = saved_ptr;
            return 0;
        }
        (*ptr)++;
        w++;
    }

    if (isalpha(**ptr) || isdigit(**ptr)) 
    {
        *ptr = saved_ptr;
        return 0;
    }
    
    return 1;
}