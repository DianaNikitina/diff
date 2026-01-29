#include "diff.h"

void generate_latex_document(trnode_t* original, trnode_t* derivative, const char* filename) 
{
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("ERROR: do not open file: %s\n", filename);
        return;
    }
    
    fprintf(f, "\\documentclass[12pt]{article}\n");
    fprintf(f, "\\usepackage{amsmath}\n");
    fprintf(f, "\\usepackage{amssymb}\n");
    fprintf(f, "\\usepackage[T2A]{fontenc}\n");
    fprintf(f, "\\usepackage[russian]{babel}\n");
    fprintf(f, "\\usepackage{hyperref}\n\n");
    fprintf(f, "\\hypersetup{\n");
    fprintf(f, "    colorlinks=true,\n");
    fprintf(f, "    linkcolor=blue,\n");
    fprintf(f, "    filecolor=magenta,\n");
    fprintf(f, "    urlcolor=cyan,\n");
    fprintf(f, "}\n\n");
    
    fprintf(f, "\\title{Результат дифференцирования}\n");
    fprintf(f, "\\author{Автоматический дифференциатор}\n");
    fprintf(f, "\\date{\\today}\n\n");
    
    fprintf(f, "\\begin{document}\n\n");
    fprintf(f, "\\maketitle\n\n");
    
    fprintf(f, "\\section{Исходная функция}\n");
    fprintf(f, "\\begin{equation*}\n");
    fprintf(f, "f(x) = ");
    tree_to_latex(original, f);
    fprintf(f, "\n");
    fprintf(f, "\\end{equation*}\n");
    
    fprintf(f, "\\section{Производная}\n");
    fprintf(f, "\\begin{equation*}\n");
    fprintf(f, "f'(x) = ");
    tree_to_latex(derivative, f);
    fprintf(f, "\n");
    fprintf(f, "\\end{equation*}\n");
    
    fprintf(f, "\\end{document}\n");
    
    fclose(f);
    printf("LaTeX correct save в %s\n", filename);
    printf("For compile: pdflatex %s\n", filename);
}