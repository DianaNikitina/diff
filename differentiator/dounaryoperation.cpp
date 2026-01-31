#include "diff.h"

const double EPS = 1e-9;

double do_unary_operation(sign_t op, double operand, int* error) 
{
    switch (op) {
        case SIN:
            return sin(operand);
    
        case COS:
            return cos(operand);
            
        case TG:
            return tan(operand);
            
        case CTG:
            if (tan(operand) < EPS) {
                printf("ERROR: cotangent not define\n");
                *error = 1;
                return 0.0;
            }
            return 1.0 / tan(operand);
    
        case SH:
            return sinh(operand);
            
        case CH:
            return cosh(operand);
            
        case TH:
            return tanh(operand);
            
        case CTH:
        {
            if (tanh(operand) < EPS) {
                printf("ERROR: hyperbolic cotangent not define\n");
                *error = 1;
                return 0.0;
            }
            return 1.0 / tanh(operand);
        }
    
        case LN:
        {
            if (operand <= 0.0) {
                printf("ERROR: logarithm of non-positive value\n");
                *error = 1;
                return 0.0;
            }
            return log(operand);
        }

        case LOG:
        {
            if (operand <= 0.0) {
                printf("ERROR: not positive value for logarithm\n");
                *error = 1;
                return 0.0;
            }
            return log10(operand);
        }
    
        case EXP:
            return exp(operand);
    
        case ARCSIN:
        {
            if (operand < -1.0 || operand > 1.0) {
                printf("ERROR: arcsin argument out of range [-1, 1]\n");
                *error = 1;
                return 0.0;
            }
            return asin(operand);
        }
            
        case ARCCOS:
        {
            if (operand < -1.0 || operand > 1.0) {
                printf("ERROR: arccos argument out of range [-1, 1]\n");
                *error = 1;
                return 0.0;
            }
            return acos(operand);
        }
    
        case ARCTG:
            return atan(operand);
            
        case ARCCTG:
            return M_PI_2 - atan(operand);
        
        default:
            break;
    }
}