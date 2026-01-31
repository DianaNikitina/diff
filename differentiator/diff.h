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

#define dADD(left, right) create_operation_node(ADDITION, left, right, "ADDITION")
#define dSUB(left, right) create_operation_node(SUBTRACTION, left, right, "SUBTRACTION")
#define dMUL(left, right) create_operation_node(MULTIPLICATION, left, right, "MULTIPLICATION")
#define dDIV(left, right) create_operation_node(DIVISION, left, right, "DIVISION")
#define dPOW(left, right) create_operation_node(DEGREE, left, right, "DEGREE")
#define dSIN(x) create_operation_node(SIN, x, NULL, "SIN")
#define dCOS(x) create_operation_node(COS, x, NULL, "COS")
#define dTAN(x) create_operation_node(TG, x, NULL, "TG")
#define dCOT(x) create_operation_node(CTG, x, NULL, "CTG")
#define dLN(x) create_operation_node(LN, x, NULL, "LN")
#define dLOG(base, x) create_operation_node(LOG, base, x, "LOG")
#define dEXP(x) create_operation_node(EXP, x, NULL, "EXP")
#define dASIN(x) create_operation_node(ARCSIN, x, NULL, "ARCSIN")
#define dACOS(x) create_operation_node(ARCCOS, x, NULL, "ARCCOS")
#define dATAN(x) create_operation_node(ARCTG, x, NULL, "ARCTG")
#define dACOT(x) create_operation_node(ARCCTG, x, NULL, "ARCCTG")
#define dSINH(x) create_operation_node(SH, x, NULL, "SH")
#define dCOSH(x) create_operation_node(CH, x, NULL, "CH")
#define dTANH(x) create_operation_node(TH, x, NULL, "TH")
#define dCOTH(x) create_operation_node(CTH, x, NULL, "CTH")
#define dSQRT(x) dPOW(x, num(0.5))
#define num(val) create_number_node(val)
#define ONE num(1.0)
#define TWO num(2.0)
#define MINUS_ONE num(-1.0)
#define NUM_FUNCTIONS (sizeof(math_functions) / sizeof(math_functions[0]))

typedef int Item;

typedef struct {
    const char* name;  
    double (*func)(double);
    int is_constant;   
    double const_value;
} MathFunction;

enum treeErr_t 
{
    correct = 0x01,
    full_tree = 0x02,

};

typedef enum type
{
    OPERATION = 21,
    VARIABLE = 22,
    NUMBER = 23
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
    CTH = 19,
    SQRT = 20 

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


int gramm(char* diff);
void destroy_tree(tree_t* ptree);
void tree_to_latex(trnode_t* node, FILE* output); 
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
void generate_latex_document(trnode_t* original, trnode_t* derivative, const char* filename);
int match_word(char** ptr, const char* word);
void skip_spaces(char** ptr);
double GetG(char** diff_ptr);
double GetE(char** diff_ptr);
double GetT(char** diff_ptr);
double GetW(char** diff_ptr); 
double GetF(char** diff_ptr);
double GetP(char** diff_ptr);
double GetN(char** diff_ptr);
double cot(double x);
double coth(double x);
double acot(double x);
double log2_custom(double x);
#endif