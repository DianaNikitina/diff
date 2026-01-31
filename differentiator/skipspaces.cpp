#include "diff.h"

void skip_spaces(char** ptr)
{
    while (**ptr == ' ' || **ptr == '\t' || **ptr == '\r' || **ptr == '\n') {
        (*ptr)++;
    }
}