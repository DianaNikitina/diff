#include "diff.h"

void tree_to_latex(trnode_t* node, FILE* output) 
{
    if (!node) return;
    
    switch(node->diff.enum_type_op) 
    {
        case NUMBER:
            fprintf(output, "%s", node->diff.value);
            break;
            
        case VARIABLE:
            fprintf(output, "%s", node->diff.value);
            break;
            
        case OPERATION:
            switch(node->diff.enum_value) 
            {
                case ADDITION:
                {
                    fprintf(output, "(");
                    tree_to_latex(node->left, output);
                    fprintf(output, " + ");
                    tree_to_latex(node->right, output);
                    fprintf(output, ")");
                    break;
                } 

                case SUBTRACTION:
                {
                    fprintf(output, "(");
                    tree_to_latex(node->left, output);
                    fprintf(output, " - ");
                    tree_to_latex(node->right, output);
                    fprintf(output, ")");
                    break;
                } 

                case MULTIPLICATION:
                {
                    int need_left_paren = (node->left && node->left->diff.enum_type_op == OPERATION &&
                                          (node->left->diff.enum_value == ADDITION || 
                                           node->left->diff.enum_value == SUBTRACTION));
                    int need_right_paren = (node->right && node->right->diff.enum_type_op == OPERATION &&
                                           (node->right->diff.enum_value == ADDITION || 
                                            node->right->diff.enum_value == SUBTRACTION));
                    
                    if (need_left_paren) fprintf(output, "(");
                    tree_to_latex(node->left, output);
                    if (need_left_paren) fprintf(output, ")");
                    
                    fprintf(output, " \\cdot ");
                    
                    if (need_right_paren) fprintf(output, "(");
                    tree_to_latex(node->right, output);
                    if (need_right_paren) fprintf(output, ")");
                    break;
                }

                case DIVISION:
                {
                    fprintf(output, "\\frac{");
                    tree_to_latex(node->left, output);
                    fprintf(output, "}{");
                    tree_to_latex(node->right, output);
                    fprintf(output, "}");
                    break;
                }

                case DEGREE:
                {
                    if (node->left && node->left->diff.enum_type_op == NUMBER && 
                        strcmp(node->left->diff.value, "e") == 0) {
                        fprintf(output, "e^{");
                        tree_to_latex(node->right, output);
                        fprintf(output, "}");
                    } else {
                        fprintf(output, "{");
                        tree_to_latex(node->left, output);
                        fprintf(output, "}^{");
                        tree_to_latex(node->right, output);
                        fprintf(output, "}");
                    }
                    break;
                }

                case SIN:
                {
                    fprintf(output, "\\sin(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case COS:
                {
                    fprintf(output, "\\cos(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case TG:
                {
                    fprintf(output, "\\tan(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case CTG:
                {
                    fprintf(output, "\\cot(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case LN:
                {
                    fprintf(output, "\\ln(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case LOG:
                {
                    fprintf(output, "\\log_{");
                    tree_to_latex(node->right, output);
                    fprintf(output, "}(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case EXP:
                {
                    fprintf(output, "e^{");
                    tree_to_latex(node->left, output);
                    fprintf(output, "}");
                    break;
                } 

                case ARCSIN:
                {
                    fprintf(output, "\\arcsin(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case ARCCOS:
                {
                    fprintf(output, "\\arccos(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case ARCTG:
                {
                    fprintf(output, "\\arctan(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case ARCCTG:
                {
                    fprintf(output, "\\arccot(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                }

                case SH:
                {
                    fprintf(output, "\\sinh(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case CH:
                {
                    fprintf(output, "\\cosh(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                } 

                case TH:
                {
                    fprintf(output, "\\tanh(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                }

                case CTH:
                {
                    fprintf(output, "\\coth(");
                    tree_to_latex(node->left, output);
                    fprintf(output, ")");
                    break;
                }
                default:
                    fprintf(output, "\\text{?}(?\\text{)}");
                    break;
            }
            default:
                break;
    }
}