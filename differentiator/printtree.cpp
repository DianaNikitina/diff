#include "diff.h"

void print_tree(trnode_t* root)
{
    assert(root);
    if (root->left)
        print_tree(root->left);
    printf("%s ", root->diff.value); 
    if (root->right)
        print_tree(root->right);
}
