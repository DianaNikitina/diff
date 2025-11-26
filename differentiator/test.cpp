#include <stdio.h>

int main()
{
    const char* word = "y";
    if (word[1] == '\0')
    {
        printf("CORRECT\n");
        return 1;

    }
    return 0;
}