#include "diff.h"

double cot(double x) { return 1.0 / tan(x); }
double coth(double x) { return 1.0 / tanh(x); }
double acot(double x) { return M_PI_2 - atan(x); }
double log2_custom(double x) { return log(x) / M_LN2; }

MathFunction math_functions[] = 
{
    {"sin", sin, 0, 0},
    {"cos", cos, 0, 0},
    {"tan", tan, 0, 0},
    {"tg", tan, 0, 0},             
    {"ctg", cot, 0, 0},        
    {"asin", asin, 0, 0},
    {"arcsin", asin, 0, 0},
    {"acos", acos, 0, 0},
    {"arccos", acos, 0, 0},
    {"atan", atan, 0, 0},
    {"arctan", atan, 0, 0},
    {"arctg", atan, 0, 0}, 
    {"arcctg", acot, 0, 0},
    {"sh", sinh, 0, 0},
    {"ch", cosh, 0, 0},
    {"th", tanh, 0, 0},
    {"cth", coth, 0, 0},
    {"ln", log, 0, 0},        
    {"log", log10, 0, 0},      
    {"log2", log2_custom, 0, 0},
    {"exp", exp, 0, 0},
    {"sqrt", sqrt, 0, 0},
    {"pi", NULL, 1, M_PI},
    {"PI", NULL, 1, M_PI},
    {"e", NULL, 1, M_E},
    {"E", NULL, 1, M_E},
};

int gramm(char* diff)
{
    char* ptr = diff;
    double val = GetG(&ptr);
    printf("value = %g\n", val);
    return 0;
}

double GetG(char** diff_ptr)
{
    skip_spaces(diff_ptr);
    double val = GetE(diff_ptr);
    
    skip_spaces(diff_ptr);
    if (**diff_ptr != '$') 
    {
        fprintf(stderr, "Syntax ERROR: expected '$', got '%c'\n", **diff_ptr);
        (*diff_ptr)++; 
        return 0;
    }
    return val;
}

double GetN(char** diff_ptr)
{
    char* diff = *diff_ptr;
    double val = 0.0;
    double fraction = 1.0;
    
    skip_spaces(&diff);
    
    int is_negative = 0;
    if (*diff == '-') 
    {
        is_negative = 1;
        diff++;
    }
    
    while (*diff >= '0' && *diff <= '9') 
    {
        val = val * 10.0 + (*diff - '0');
        diff++;
    }
    
    if (*diff == '.') 
    {
        diff++;
        while (*diff >= '0' && *diff <= '9') 
        {
            fraction *= 0.1;
            val += (*diff - '0') * fraction;
            diff++;
        }
    }
    
    if (*diff == 'e' || *diff == 'E') 
    {
        diff++;
        int exp_is_negative = 0;
        if (*diff == '-') 
        {
            exp_is_negative = 1;
            diff++;
        } 
        else if (*diff == '+')
            diff++;
        
        int exponent = 0;
        while (*diff >= '0' && *diff <= '9') 
        {
            exponent = exponent * 10 + (*diff - '0');
            diff++;
        }
        
        if (exp_is_negative)
            val /= pow(10.0, exponent);
        else
            val *= pow(10.0, exponent);
    }
    
    *diff_ptr = diff;
    return is_negative ? -val : val;
}

double GetE(char** diff_ptr)
{
    skip_spaces(diff_ptr);
    double val = GetT(diff_ptr);
    
    while (1) 
    {
        skip_spaces(diff_ptr);
        if (**diff_ptr == '+' || **diff_ptr == '-') 
        {
            char op = **diff_ptr;
            (*diff_ptr)++;
            
            double val2 = GetT(diff_ptr);
            if (op == '+')
                val += val2;
            else 
                val -= val2;
        } 
        else 
            break;
    }
    
    return val;
}

double GetT(char** diff_ptr)
{
    skip_spaces(diff_ptr);
    double val = GetW(diff_ptr);
    
    while (1) 
    {
        skip_spaces(diff_ptr);
        if (**diff_ptr == '*' || **diff_ptr == '/') 
        {
            char op = **diff_ptr;
            (*diff_ptr)++;
            
            double val2 = GetW(diff_ptr);
            if (op == '*')
                val *= val2;
            else 
            {
                if (fabs(val2) < 1e-12) 
                {
                    fprintf(stderr, "ERROR: division on 0\n");
                    return 0;
                }
                val /= val2;
            }
        } 
        else
            break;
    }
    
    return val;
}

double GetW(char** diff_ptr)
{
    skip_spaces(diff_ptr);
    double val = GetF(diff_ptr);
    
    while (1) 
    {
        skip_spaces(diff_ptr);
        if (**diff_ptr == '^') 
        {
            (*diff_ptr)++;
            double exponent = GetF(diff_ptr);
            val = pow(val, exponent);
        } 
        else
            break;
    }
    
    return val;
}

double GetP(char** diff_ptr)
{
    skip_spaces(diff_ptr);
    
    if (**diff_ptr == '(') 
    {
        (*diff_ptr)++;
        double val = GetE(diff_ptr);
        
        skip_spaces(diff_ptr);
        if (**diff_ptr != ')') 
        {
            fprintf(stderr, "ERROR: expected ')', got '%c'\n", **diff_ptr);
            return 0;
        }
        
        (*diff_ptr)++;
        return val;
    } 
    else
        return GetN(diff_ptr);
}


double GetF(char** diff_ptr)
{
    skip_spaces(diff_ptr);
    
    for (size_t i = 0; i < NUM_FUNCTIONS; i++) 
    {
        if (match_word(diff_ptr, math_functions[i].name)) 
        {
            skip_spaces(diff_ptr);
            
            if (math_functions[i].is_constant)
                return math_functions[i].const_value;
            
            if (**diff_ptr != '(') 
            {
                fprintf(stderr, "ERROR: expected '(' after %s, got '%c'\n", math_functions[i].name, **diff_ptr);
                return 0;
            }
            
            (*diff_ptr)++;
            
            double arg = GetE(diff_ptr);
            
            skip_spaces(diff_ptr);
            
            if (**diff_ptr != ')') 
            {
                fprintf(stderr, "ERROR: expected ')' after %s argument, got '%c'\n", math_functions[i].name, **diff_ptr);
                return 0;
            }
            
            (*diff_ptr)++;
            
            if (math_functions[i].func != NULL)
                return math_functions[i].func(arg);
            
            return 0;
        }
    }

    return GetP(diff_ptr);
}
