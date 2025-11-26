#include "diff.h"

int write_to_file_diff(tree_t* ptree, const char* name_file)
{
    FILE* file = fopen(name_file, "w");
    if (!file)
    {
        printf("ERROR open file\n");
        return 1;
    }
    printf("CORRECT open file\n");


    fprintf(file, "digraph structs {\nrankdir=TB;\n");

    rec_tree_diff(ptree->root, file);

    arrow_tree_diff(ptree->root, file);

    fprintf(file, "}");
    
    fclose(file);
    return 0;
}