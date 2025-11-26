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

trnode_t* rools_diff(trnode_t* root)
{
    trnode_t* new_node = 0;
    switch (root->diff.enum_type_op)
    {
        case NUMBER:
        {
            new_node = simple_rools("NUMBER", NUMBER, "0");
            return new_node;
        }
        case OPERATION:
        {

            trnode_t* left_diff = rools_diff(root->left);
            trnode_t* right_diff = rools_diff(root->right);
            
            new_node = create_operation_node(ADDITION, left_diff, right_diff, "ADDITION");
            return new_node;
            break;
        }
        case VARIABLE:
        {
            new_node = simple_rools("NUMBER", NUMBER, "1");
            return new_node;
        }
        default:
            break;
    }
    return root;
}

trnode_t* simple_rools(const char* name_type_op, type_t enum_type_op, const char* value)
{
    trnode_t* new_node = 0;
    new_node = (trnode_t*) calloc(1, sizeof(trnode_t));

    assert(new_node);

    new_node->diff.name_type_op = name_type_op;
    new_node->diff.enum_type_op = enum_type_op;
    new_node->diff.value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

trnode_t* create_operation_node(sign_t operation, trnode_t* left, trnode_t* right, const char* value)
{
    trnode_t* new_node = (trnode_t*)calloc(1, sizeof(trnode_t));
    assert(new_node);
    
    new_node->diff.name_type_op = "OPERATION";
    new_node->diff.enum_type_op = OPERATION;
    new_node->diff.value = value;
    new_node->diff.enum_value = operation;
    new_node->left = left;
    new_node->right = right;
    
    return new_node;
}