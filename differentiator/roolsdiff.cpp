#include "diff.h"

trnode_t* rools_diff(trnode_t* root)
{

    trnode_t* new_node = 0;
    //printf(">>%d\n", root->diff.enum_type_op);
    switch (root->diff.enum_type_op)
    {
        case NUMBER:
        {
            return simple_rools("NUMBER", NUMBER, "0");
        }
        case OPERATION:
        {
            if (!root->left || !root->right) assert(root->left);
            
            trnode_t* left_diff = rools_diff(root->left);
            
            trnode_t* right_diff = NULL;
            if (root->right) {
                right_diff = rools_diff(root->right);
            }
            switch(root->diff.enum_value)
            {
                case ADDITION:
                    return dADD(left_diff, right_diff);

                case SUBTRACTION:
                    return dSUB(left_diff, right_diff);
                    
                case MULTIPLICATION:
                    return dADD(dMUL(left_diff, copy_tree(root->right)), dMUL(copy_tree(root->left), right_diff));
                    
                case DIVISION:
                    return dDIV(dSUB(dMUL(left_diff, copy_tree(root->right)), dMUL(copy_tree(root->left), right_diff)),dPOW(copy_tree(root->right), TWO));

                case DEGREE:
                    return dMUL(copy_tree(root),dADD(dMUL(right_diff, dLN(copy_tree(root->left))),dMUL(copy_tree(root->right), dDIV(left_diff, copy_tree(root->left)))));

                case SIN:
                    return dMUL(dCOS(copy_tree(root->left)), left_diff);

                case COS:
                    return dMUL(dMUL(MINUS_ONE, dSIN(copy_tree(root->left))), left_diff);

                case TG:
                    return dMUL(dDIV(ONE, dPOW(dCOS(copy_tree(root->left)), TWO)), left_diff);

                case CTG:
                    return dMUL(dMUL(MINUS_ONE, dDIV(ONE, dPOW(dSIN(copy_tree(root->left)), TWO))), left_diff);    
                
                case LN:
                    return dMUL(dDIV(ONE, copy_tree(root->left)), left_diff);

                case LOG:
                    return dMUL(dDIV(ONE, dMUL(copy_tree(root->left), dLN(copy_tree(root->right)))), left_diff);    
                
                case EXP:
                    return dMUL(dEXP(copy_tree(root->left)), left_diff);

                case ARCSIN:
                    return dMUL(dDIV(ONE, dSQRT(dSUB(ONE, dPOW(copy_tree(root->left), TWO)))),left_diff);

                case ARCCOS: 
                    return dMUL(dMUL(MINUS_ONE, dDIV(ONE, dSQRT(dSUB(ONE, dPOW(copy_tree(root->left), TWO))))),left_diff);

                case ARCTG:
                    return dMUL(dDIV(ONE, dADD(ONE, dPOW(copy_tree(root->left), TWO))),left_diff); 

                case ARCCTG:
                    return dMUL(dMUL(MINUS_ONE, dDIV(ONE, dADD(ONE, dPOW(copy_tree(root->left), TWO)))),left_diff);

                case SH:
                    return dMUL(dCOSH(copy_tree(root->left)), left_diff); 

                case CH:
                    return dMUL(dSINH(copy_tree(root->left)), left_diff); 

                case TH: 
                    return dMUL(dDIV(ONE, dPOW(dCOSH(copy_tree(root->left)), TWO)), left_diff);

                case CTH:
                    return dMUL(dMUL(MINUS_ONE, dDIV(ONE, dPOW(dSINH(copy_tree(root->left)), TWO))), left_diff);   

                default:
                    break;
            }
            return 0;
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