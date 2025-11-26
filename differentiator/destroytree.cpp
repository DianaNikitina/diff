#include "diff.h"

void destroy_tree(tree_t* ptree)
{
    if (ptree != NULL)
    {
        destroy_all(ptree->root);
    }
    ptree->root = NULL;
    ptree->size = 0;
}

void destroy_all(trnode_t* root)
{
    trnode_t* pright;
    if (root != NULL)
    {
        pright = root->right;
        destroy_all(root->left);
        free(root);
        destroy_all(pright);
    }
}