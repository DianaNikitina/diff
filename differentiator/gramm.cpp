#include "diff.h"

int GetG(char** diff_ptr);
int GetN(char** diff_ptr);
int GetE(char** diff_ptr);
int GetT(char** diff_ptr);
int GetP(char** diff_ptr);

int gramm(char* diff)
{
    char* ptr = diff;
    int val = GetG(&ptr);
    printf("value = %d\n", val);
    return 0;
}

int GetG(char** diff_ptr)
{
    char* diff = *diff_ptr;
    int val = GetE(diff_ptr);
    
    if (**diff_ptr != '$') 
    {
        fprintf(stderr, "Syntax ERROR: expected '$', got '%c'\n", **diff_ptr);
        (*diff_ptr)++; 
        return 0;
    }
    return val;
}

int GetN(char** diff_ptr)
{
    char* diff = *diff_ptr;
    int val = 0;
    
    while (*diff >= '0' && *diff <= '9')
    {
        val = *diff - '0' + val * 10;
        diff++;
    }
    
    *diff_ptr = diff; 
    return val;
}

int GetE(char** diff_ptr)
{
    int val = GetT(diff_ptr);
    
    while (**diff_ptr == '+' || **diff_ptr == '-')
    {
        char op = **diff_ptr;
        (*diff_ptr)++;
        
        int val2 = GetT(diff_ptr);
        if (op == '+')
            val += val2;
        else 
            val -= val2;
    }
    
    return val;
}

int GetT(char** diff_ptr)
{
    int val = GetP(diff_ptr);
    
    while (**diff_ptr == '*' || **diff_ptr == '/')
    {
        char op = **diff_ptr;
        (*diff_ptr)++;
        
        int val2 = GetP(diff_ptr);
        if (op == '*')
            val *= val2;
        else 
            val /= val2;
    }
    
    return val;
}

int GetP(char** diff_ptr)
{
    if (**diff_ptr == '(')
    {
        (*diff_ptr)++;
        int val = GetE(diff_ptr);
        
        if (**diff_ptr != ')') {
            fprintf(stderr, "Syntax ERROR: expected ')', got '%c'\n", **diff_ptr);
            return 0;
        }
        
        (*diff_ptr)++;
        return val;
    }
    else
    {
        return GetN(diff_ptr);
    }
}