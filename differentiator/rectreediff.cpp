#include "diff.h"

void rec_tree_diff(trnode_t* root, FILE* file)
{
    if (root->diff.enum_type_op == NUMBER)
        fprintf(file, "%lu [shape=Mrecord; style = filled; fillcolor = \"#b5ebfaff\"; color = \"#030303ff\"; label=\"{type = %s | value = %s | {left = %p | right = %p}}\";]\n", (unsigned long)&root->diff, root->diff.name_type_op, root->diff.value, root->left, root->right);
    else if (root->diff.enum_type_op == VARIABLE)
        fprintf(file, "%lu [shape=Mrecord; style = filled; fillcolor = \"#b5fab8ff\"; color = \"#030303ff\"; label=\"{type = %s | value = %s | {left = %p | right = %p}}\";]\n", (unsigned long)&root->diff, root->diff.name_type_op, root->diff.value, root->left, root->right);
    else if (root->diff.enum_type_op == OPERATION)
        fprintf(file, "%lu [shape=Mrecord; style = filled; fillcolor = \"#facdb5ff\"; color = \"#030303ff\"; label=\"{type = %s | value = %s | {left = %p | right = %p}}\";]\n", (unsigned long)&root->diff, root->diff.name_type_op, root->diff.value, root->left, root->right);
    if (root->left)
        rec_tree_diff(root->left, file); 
    if (root->right)
        rec_tree_diff(root->right, file);
}


void arrow_tree_diff(trnode_t* root, FILE* file)
{
    
    if (root->left)
        fprintf(file, "%lu->%lu[color = \"#f93319ff\"]\n", (unsigned long)&root->diff, (unsigned long)root->left);

    if (root->right)
        fprintf(file, "%lu->%lu[color = \"#2c07fdff\"]\n", (unsigned long)&root->diff, (unsigned long)root->right);

    if (root->left)
        arrow_tree_diff(root->left, file);
    if (root->right) 
        arrow_tree_diff(root->right, file);
}