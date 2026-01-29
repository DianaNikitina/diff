#include "diff.h"

static opt_t array_opt[] = 
{
    {"+", "ADDITION", ADDITION}, 
    {"-", "SUBTRACTION", SUBTRACTION}, 
    {"*", "MULTIPLICATION", MULTIPLICATION},
    {"/", "DIVISION", DIVISION}, 
    {"^", "DEGREE", DEGREE}, 
    {"log", "LOG", LOG},
    {"ln", "LN", LN}, 
    {"sin", "SIN", SIN}, 
    {"cos", "COS", COS}, 
    {"tg", "TG", TG}, 
    {"ctg", "CTG", CTG},
    {"exp", "EXP", EXP},
    {"arcsin", "ARCSIN", ARCSIN},
    {"arccos", "ARCCOS", ARCCOS},
    {"arctg", "ARCTG", ARCTG},
    {"arcctg", "ARCCTG", ARCCTG},
    {"ctg", "CTG", CTG},
    {"sh", "SH", SH},
    {"ch", "CH", CH},
    {"th", "TH", TH},
    {"cth", "CTH", CTH},

};

trnode_t* make_node(char* new_sign)
{
    trnode_t* new_node = 0;
    new_node = (trnode_t*) calloc(1, sizeof(trnode_t));

    assert(new_node);

    func_type_op(new_sign, new_node);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

int func_type_op(char* new_sign, trnode_t* new_node)
{
    if (new_sign[0] >= '0' && new_sign[0] <= '9')
    {
        new_node->diff.name_type_op = "NUMBER";
        new_node->diff.enum_type_op = NUMBER;
        new_node->diff.value = new_sign;
        return 1;
    }
    if (new_sign[0] >= 'a' && new_sign[0] <= 'z' && new_sign[1] == '\0')
    {
        new_node->diff.name_type_op = "VARIABLE";
        new_node->diff.enum_type_op = VARIABLE;
        new_node->diff.value = new_sign;
        return 1;
    }
    else 
    {
        new_node->diff.name_type_op = "OPERATION";
        new_node->diff.enum_type_op = OPERATION;
        for (int i = 0; i < 13; i++)
        {
            if (strcmp(new_sign, array_opt[i].name_opt) == 0)
            {
                new_node->diff.value = array_opt[i].str_opt;
                new_node->diff.enum_value = array_opt[i].enum_opt;
                return 1;
            }
        }
    }
    return 0;
}