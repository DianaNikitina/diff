#ifndef DIFF_H_INCLUDED
#define DIFF_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#define MAXITEMS 100
#define SECTION_SEPARATOR printf("-----------------\n\n");
#define TREE_OK(ptree, error) error = treeVerify(ptree); if (error != correct) treeDump(ptree, error,  __FILE__, __FUNCTION__, __LINE__);

typedef int Item;

enum treeErr_t 
{
    correct = 0x01,
    full_tree = 0x02,

};

typedef enum type
{
    OPERATION = 20,
    VARIABLE = 21,
    NUMBER = 22
} type_t;

typedef enum sign
{
    ADDITION = 0,
    SUBTRACTION = 1,
    MULTIPLICATION = 2,
    DIVISION = 3,
    DEGREE = 4,
    LOG = 5,
    LN = 6,
    SIN = 7,
    COS = 8,
    TG = 9,
    CTG = 10,
    EXP = 11,
    ARCSIN = 12,
    ARCCOS = 13,
    ARCTG = 14,
    ARCCTG = 15,
    CH = 16,
    SH = 17,
    TH = 18,
    CTH = 19 

} sign_t;


typedef struct opt
{
    const char* name_opt;
    const char* str_opt;
    sign_t enum_opt;

} opt_t;

typedef struct info
{
    const char* name_type_op;
    type_t enum_type_op;
    const char* value;
    sign_t enum_value;

} info_t;

typedef struct trnode
{

    info_t diff;
    struct trnode * left;
    struct trnode * right;
    int rank;
    
} trnode_t;

typedef struct tree
{
    trnode_t* root;
    int size;
} tree_t;

void destroy_tree(tree_t* ptree);
void destroy_all(trnode_t* root);
char* find_sign(char* diff, int* position);
trnode_t* make_node(char* new_sign);
int func_type_op(char* new_sign, trnode_t* new_node);
void print_tree(trnode_t* root);
trnode_t* read_node(char* diff, int* position, tree_t* ptree);
size_t sizeFile(FILE* file);
int write_to_file_diff(tree_t* ptree, const char* name_file);
void rec_tree_diff(trnode_t* root, FILE* file);
void arrow_tree_diff(trnode_t* root, FILE* file);
trnode_t* rools_diff(trnode_t* root);
trnode_t* simple_rools(const char* name_type_op, type_t enum_type_op, const char* value);
trnode_t* create_operation_node(sign_t operation, trnode_t* left, trnode_t* right, const char* value);
trnode_t* create_number_node(double value);
double evaluate_tree(trnode_t* root);
double evaluate_tree_number(trnode_t* root, int* error);
double do_operation(sign_t op, double left, double right, int* error);
double do_unary_operation(sign_t op, double operand, int* error);
const char* sign_to_string(sign_t sign); 
trnode_t* copy_tree(trnode_t* root);
#endif