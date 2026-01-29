#include "diff.h"

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

trnode_t* create_number_node(double value)
{
    trnode_t* new_node = (trnode_t*)calloc(1, sizeof(trnode_t));
    assert(new_node);
    
    new_node->diff.name_type_op = "NUMBER";
    new_node->diff.enum_type_op = NUMBER;
    new_node->diff.value = NULL;
    
    char* num_str = (char*)calloc(32, sizeof(char));
    assert(num_str);
    
    snprintf(num_str, 32, "%.10g", value);
    new_node->diff.value = num_str;
    
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}