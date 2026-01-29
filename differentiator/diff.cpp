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

    //printf("%s\n", diff);
    //gramm(diff);

    read_node(diff, &position, &ptree);
    
    print_tree(ptree.root);
    printf("\nCORRECT print tree\n");
    SECTION_SEPARATOR
    
    printf("write to file base of data\n");
    SECTION_SEPARATOR
    write_to_file_diff(&ptree, "dot_files/expression.dot");

    printf("function of calc\n");
    SECTION_SEPARATOR
    evaluate_tree(ptree.root);

    printf("function of diff\n");
    SECTION_SEPARATOR
    new_ptree.root = rools_diff(ptree.root);
    printf("correct!\n");
    if(!new_ptree.root)
    {
        fprintf(stderr, "ERROR: null pointer of root\n");
        return 1;
    }

    printf("function of calc\n");
    SECTION_SEPARATOR
    evaluate_tree(new_ptree.root);

    /*print_tree(new_ptree.root);
    printf("\nCORRECT print tree after diff\n");
    SECTION_SEPARATOR*/

    printf("write to file base of data after diff\n");
    SECTION_SEPARATOR
    write_to_file_diff(&new_ptree, "dot_files/diff.dot");

    printf("go to latex\n");
    SECTION_SEPARATOR
    generate_latex_document(ptree.root, new_ptree.root, "latex.txt");

    destroy_tree(&new_ptree);
    free(diff);
    printf("CORRECT destroy tree\n");
    SECTION_SEPARATOR
}