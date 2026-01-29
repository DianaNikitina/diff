#include "diff.h"

double evaluate_tree(trnode_t* root) 
{
    if (!root) {
        printf("ERROR: empty tree\n");
        return 0.0;
    }
    
    int error = 0;
    double result = evaluate_tree_number(root, &error);
    
    if (error) {
        printf("ERROR evaluate tree\n");
        return 0.0;
    }
    
    printf("result express: %.4f\n", result);
    return result;
}
