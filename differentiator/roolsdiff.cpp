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
                    return create_operation_node(ADDITION, left_diff, right_diff, "ADDITION");
            
                case SUBTRACTION:
                    return create_operation_node(SUBTRACTION, left_diff, right_diff, "SUBTRACTION");
                    
                case MULTIPLICATION:
                    return create_operation_node(ADDITION, create_operation_node(MULTIPLICATION, left_diff, copy_tree(root->right), "MULTIPLICATION"), create_operation_node(MULTIPLICATION, copy_tree(root->left), right_diff, "MULTIPLICATION"), "ADDITION");
                    
                case DIVISION:
                    return create_operation_node(DIVISION, create_operation_node(SUBTRACTION, create_operation_node(MULTIPLICATION, left_diff, copy_tree(root->right), "MULTIPLICATION"), create_operation_node(MULTIPLICATION, copy_tree(root->left), right_diff, "MULTIPLICATION"), "SUBTRACTION"), create_operation_node(DEGREE, copy_tree(root->right), create_number_node(2.0), "DEGREE"), "DIVISION");
                    
                case DEGREE:
                    return create_operation_node(MULTIPLICATION, copy_tree(root), create_operation_node(ADDITION, create_operation_node(MULTIPLICATION, right_diff, create_operation_node(LN, copy_tree(root->left), NULL, "LN"),"MULTIPLICATION"), create_operation_node(MULTIPLICATION, copy_tree(root->right), create_operation_node(DIVISION, left_diff, copy_tree(root->left), "DIVISION"), "MULTIPLICATION"), "ADDITION"),"MULTIPLICATION");
                
                case SIN:
                    return create_operation_node(MULTIPLICATION, create_operation_node(COS, copy_tree(root->left), NULL, "COS"), left_diff, "MULTIPLICATION");
    
                case COS:
                    return create_operation_node(MULTIPLICATION, create_operation_node(MULTIPLICATION, create_number_node(-1.0), create_operation_node(SIN, copy_tree(root->left), NULL, "SIN"), "MULTIPLICATION"), left_diff, "MULTIPLICATION");
    
                case TG:
                    return create_operation_node(MULTIPLICATION, create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(DEGREE, create_operation_node(COS, copy_tree(root->left), NULL, "COS"), create_number_node(2.0), "DEGREE"), "DIVISION"), left_diff, "MULTIPLICATION");
    
                case CTG:
                    return create_operation_node(MULTIPLICATION, create_operation_node(MULTIPLICATION, create_number_node(-1.0), create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(DEGREE, create_operation_node(SIN, copy_tree(root->left), NULL, "SIN"), create_number_node(2.0), "DEGREE"), "DIVISION"), "MULTIPLICATION"), left_diff, "MULTIPLICATION");
    
                case LN:
                    return create_operation_node(MULTIPLICATION, create_operation_node(DIVISION, create_number_node(1.0), copy_tree(root->left), "DIVISION"), left_diff, "MULTIPLICATION");
    
                case LOG:
                    return create_operation_node(MULTIPLICATION, create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(MULTIPLICATION, copy_tree(root->left), create_operation_node(LN, copy_tree(root->right), NULL, "LN"), "MULTIPLICATION"), "DIVISION"), left_diff, "MULTIPLICATION");
    
                case EXP:
                    return create_operation_node(MULTIPLICATION, create_operation_node(EXP, copy_tree(root->left), NULL, "EXP"), left_diff, "MULTIPLICATION");
    
                case ARCSIN:
                    return create_operation_node(MULTIPLICATION, create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(DEGREE, create_operation_node(SUBTRACTION, create_number_node(1.0), create_operation_node(DEGREE, copy_tree(root->left), create_number_node(2.0), "DEGREE"), "SUBTRACTION"), create_number_node(0.5), "DEGREE"), "DIVISION"), left_diff, "MULTIPLICATION");
    
                case ARCCOS: 
                    return create_operation_node(MULTIPLICATION, create_operation_node(MULTIPLICATION, create_number_node(-1.0), create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(DEGREE, create_operation_node(SUBTRACTION, create_number_node(1.0), create_operation_node(DEGREE, copy_tree(root->left), create_number_node(2.0), "DEGREE"), "SUBTRACTION"), create_number_node(0.5), "DEGREE"), "DIVISION"), "MULTIPLICATION"), left_diff, "MULTIPLICATION");
    
                case ARCTG:
                    return create_operation_node(MULTIPLICATION, create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(ADDITION, create_number_node(1.0), create_operation_node(DEGREE, copy_tree(root->left), create_number_node(2.0), "DEGREE"), "ADDITION"), "DIVISION"), left_diff, "MULTIPLICATION");
    
                case ARCCTG:
                    return create_operation_node(MULTIPLICATION, create_operation_node(MULTIPLICATION, create_number_node(-1.0), create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(ADDITION, create_number_node(1.0), create_operation_node(DEGREE, copy_tree(root->left), create_number_node(2.0), "DEGREE"), "ADDITION"), "DIVISION"), "MULTIPLICATION"), left_diff, "MULTIPLICATION");
    
                case SH:
                    return create_operation_node(MULTIPLICATION, create_operation_node(CH, copy_tree(root->left), NULL, "CH"), left_diff, "MULTIPLICATION");
    
                case CH:
                    return create_operation_node(MULTIPLICATION, create_operation_node(SH, copy_tree(root->left), NULL, "SH"), left_diff, "MULTIPLICATION");
    
                case TH: 
                    return create_operation_node(MULTIPLICATION, create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(DEGREE, create_operation_node(CH, copy_tree(root->left), NULL, "CH"), create_number_node(2.0), "DEGREE"), "DIVISION"), left_diff, "MULTIPLICATION");
    
                case CTH:
                    return create_operation_node(MULTIPLICATION, create_operation_node(MULTIPLICATION, create_number_node(-1.0), create_operation_node(DIVISION, create_number_node(1.0), create_operation_node(DEGREE, create_operation_node(SH, copy_tree(root->left), NULL, "SH"), create_number_node(2.0), "DEGREE"), "DIVISION"), "MULTIPLICATION"), left_diff, "MULTIPLICATION");
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