#include "diff.h"

const char* sign_to_string(sign_t sign) 
{
    switch (sign) 
    {
        case ADDITION: return "+";
        case SUBTRACTION: return "-";
        case MULTIPLICATION: return "*";
        case DIVISION: return "/";
        case DEGREE: return "^";
        case LOG: return "log";
        case LN: return "ln";
        case SIN: return "sin";
        case COS: return "cos";
        case TG: return "tg";
        case CTG: return "ctg";
        case SH: return "sh";
        case CH: return "ch";
        case TH: return "th";
        case CTH: return "cth";
        case ARCSIN: return "arcsin";
        case ARCCOS: return "arccos";
        case ARCTG: return "arctg";
        case ARCCTG: return "arcctg";
        case EXP: return "exp";
        default: return "?";
    }
}