#include "diff.h"

int main()
{
    int position = 0;
    tree_t ptree = {};
    tree_t new_ptree = {};
    FILE* fp = fopen("diff.txt", "r");
    size_t size_file = sizeFile(fp);

    char* diff = (char*) calloc(size_file,sizeof(char));
    if (diff == NULL)
    {
        fprintf(stderr, "ERROR calloc diff\n");
        return 1;
    }
    printf("CORRECT calloc diff\n");
    SECTION_SEPARATOR


    fread(diff, size_file, sizeof(char), fp);
    read_node(diff, &position, &ptree);
    
    print_tree(ptree.root);
    printf("\nCORRECT print tree\n");
    SECTION_SEPARATOR
    
    printf("write to file base of data\n");
    SECTION_SEPARATOR
    write_to_file_diff(&ptree, "dot_files/expression.dot");

    printf("function of diff\n");
    SECTION_SEPARATOR
    new_ptree.root = rools_diff(ptree.root);

    print_tree(new_ptree.root);
    printf("\nCORRECT print tree after diff\n");
    SECTION_SEPARATOR

    printf("write to file base of data after diff\n");
    SECTION_SEPARATOR
    write_to_file_diff(&new_ptree, "dot_files/diff.dot");

    destroy_tree(&new_ptree);
    free(diff);
    printf("CORRECT destroy tree\n");
    SECTION_SEPARATOR
}