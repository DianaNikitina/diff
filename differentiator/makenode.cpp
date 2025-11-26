#include "diff.h"

static opt_t array_opt[] = 
{
    {"+", "ADDITION", ADDITION}, 
    {"-", "SUBTRACTION", SUBTRACTION}, 
    {"*", "MULTIPLICATION", MULTIPLICATION},
    {"/", "DIVISION", DIVISION}, 
    {"^", "DEGREE", DEGREE}, 
    {"log", "LOGARITHM", LOGARITHM}, 
    {"sin", "SINUS", SINUS}, 
    {"cos", "COSINE", COSINE}, 
    {"tg", "TANGENT", TANGENT}, 
    {"ctg", "COTANGENT", COTANGENT},
    {"sh", "SHINUS", SHINUS},
    {"ch", "CHOSINUS", CHOSINUS},
    {"th", "SHTANGENT", SHTANGENT}
};

trnode_t* make_node(char* new_sign)
{
    trnode_t* new_node = 0;
    new_node = (trnode_t*) calloc(1, sizeof(trnode_t));

    assert(new_node);

    new_node->diff.name_type_op = func_name_type_op(new_sign);
    new_node->diff.enum_type_op = func_enum_type_op(new_sign);
    new_node->diff.value = func_variable(new_sign);
    if (new_node->diff.enum_type_op == OPERATION)
        new_node->diff.enum_value = func_enum_value(new_node->diff.value);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

const char* func_name_type_op(char* new_sign)
{
    if (new_sign[0] >= '0' && new_sign[0] <= '9')
    {
        return "NUMBER";
    }
    if (new_sign[0] >= 'a' && new_sign[0] <= 'z' && new_sign[1] == '\0')
    {
        return "VARIABLE";
    }
    return "OPERATION";
}

type_t func_enum_type_op(char* new_sign)
{
    if (new_sign[0] >= '0' && new_sign[0] <= '9')
    {
        return NUMBER;
    }
    if (new_sign[0] >= 'a' && new_sign[0] <= 'z' && new_sign[1] == '\0')
    {
        return VARIABLE;
    }
    return OPERATION;
}

const char* func_variable(char* new_sign)
{
    if (new_sign[0] >= '0' && new_sign[0] <= '9')
    {
        return new_sign;
    }
    if (new_sign[0] >= 'a' && new_sign[0] <= 'z' && new_sign[1] == '\0')
    {
        return new_sign;
    }
    else 
    {
        for (int i = 0; i < 13; i++)
        {
            if (strcmp(new_sign, array_opt[i].name_opt) == 0)
            {
                return array_opt[i].str_opt;
            }
        }
    }
    return 0;
}

sign_t func_enum_value(const char* value)
{
    for (int i = 0; i < 13; i++)
    {
        if(strcmp(value, array_opt[i].name_opt) == 0)
        {
            return array_opt[i].enum_opt;
        }
    }
    return ADDITION;
}
