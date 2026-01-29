#include "diff.h"

trnode_t* copy_tree(trnode_t* root)
{
    if(!root) return NULL;
    char* new_value = (char*)(root->diff.value);

    trnode_t* copy = make_node(new_value);

    if (!copy) return NULL;

    if (root->left)
        copy->left = copy_tree(root->left);
    if (root->right)
        copy->right = copy_tree(root->right);
    return copy;
}