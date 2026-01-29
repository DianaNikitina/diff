#include "diff.h"

double evaluate_tree_number(trnode_t* root, int* error) 
{
    if (!root || *error) return 0.0;
    
    switch (root->diff.enum_type_op) {
        case NUMBER: {
            double value = atof(root->diff.value);
            printf("number: %s -> %.4f\n", root->diff.value, value);
            return value;
        }
        
        case VARIABLE: {
            printf("if %s = 1\n", root->diff.value);
            return 1.0;
        }
        
        case OPERATION: {
            switch (root->diff.enum_value) {
                case SIN:
                case COS:
                case TG:
                case CTG:
                case SH:
                case CH:
                case TH:
                case CTH:
                case LOG:
                case LN:
                case EXP:
                case ARCSIN:
                case ARCCOS:
                case ARCTG:
                case ARCCTG:
                {
                    if (!root->left) {
                        printf("ERROR: no operand of operation un\n");
                        *error = 1;
                        return 0.0;
                    }
                    double operand = evaluate_tree_number(root->left, error);
                    if (*error) return 0.0;
                    double result = do_unary_operation(root->diff.enum_value, operand, error);
                    printf(" %s(%.4f) = %.4f\n", sign_to_string(root->diff.enum_value), operand, result);
                    return result;
                }
                
                default: {
                    if (!root->left || !root->right) {
                        printf("ERROR: no operand of operation bin\n");
                        *error = 1;
                        return 0.0;
                    }
                    double left_val = evaluate_tree_number(root->left, error);
                    if (*error) return 0.0;
                    double right_val = evaluate_tree_number(root->right, error);
                    if (*error) return 0.0;
                    double result = do_operation(root->diff.enum_value, left_val, right_val, error);
                    printf("binary operation: %.4f %s %.4f = %.4f\n", left_val, sign_to_string(root->diff.enum_value), right_val, result);
                    return result;
                }
            }
        }
        
        default: {
            printf("ERROR: unknown type of node\n");
            *error = 1;
            return 0.0;
        }
    }
}
