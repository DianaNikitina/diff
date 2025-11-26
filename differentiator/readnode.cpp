#include "diff.h"

trnode_t* read_node(char* diff, int* position, tree_t* ptree) 
{
    if (diff[*position] == '\0') {
        return NULL;
    }
    
    if (diff[*position] == '\"') (*position)++;
    printf("Current char: '%c' at position %d\n", diff[*position], *position);
    
    if (diff[*position] == '(') {
        (*position)+=2;
        while (diff[*position] == ' ') (*position)++;
        
        if (diff[*position] == '0') {
            (*position)++;
            
            while (diff[*position] == ' ') (*position)++;
            
            if (diff[*position] == ')') {
                (*position)++;
            }
            return NULL;
        }
        
        char* new_sign = find_sign(diff, position);
        printf("new_sign: %s\n", new_sign);
        
        while (diff[*position] == ' ') (*position)++;
        
        trnode_t* new_node = make_node(new_sign);
        if (ptree->root == NULL)
            ptree->root = new_node;

        new_node->left = read_node(diff, position, ptree);
        new_node->right = read_node(diff, position, ptree);
        
        while (diff[*position] == ' ') (*position)++;
       
        if (diff[*position] == ')') {
            (*position)++;
        }
    
        return new_node;
    }

    else if (diff[*position] == '0') 
    {
        (*position)++;
        return NULL;
    }
    return NULL;
}