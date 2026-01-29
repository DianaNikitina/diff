#include "diff.h"

double do_operation(sign_t op, double left, double right, int* error) 
{
    switch (op) 
    {
        case ADDITION:
            return left + right;
            
        case SUBTRACTION:
            return left - right;
            
        case MULTIPLICATION:
            return left * right;
            
        case DIVISION:
            if (right == 0) {
                printf("ERROR: division on 0\n");
                *error = 1;
                return 0.0;
            }
            return left / right;
            
        case DEGREE:
            return pow(left, right);
            
        default:
            printf("ERROR: unknown operation\n");
            *error = 1;
            return 0.0;
    }
}