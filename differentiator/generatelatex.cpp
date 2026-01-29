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
    
    /*fprintf(f, "\\section{Упрощенная форма (если применимо)}\n");
    fprintf(f, "\\begin{equation*}\n");
    fprintf(f, "f'(x) = ");
    tree_to_latex(derivative, f); 
    fprintf(f, "\n");
    fprintf(f, "\\end{equation*}\n");
    
    fprintf(f, "\\section{Проверка}\n");
    fprintf(f, "Проверим производную на некоторых значениях $x$:\n");
    fprintf(f, "\\begin{itemize}\n");
    fprintf(f, "    \\item При $x = 0$: $f'(0) = ...$\n");
    fprintf(f, "    \\item При $x = 1$: $f'(1) = ...$\n");
    fprintf(f, "    \\item При $x = \\pi$: $f'(\\pi) = ...$\n");
    fprintf(f, "\\end{itemize}\n");
    
    fprintf(f, "\\section{Используемые правила дифференцирования}\n");
    fprintf(f, "\\begin{enumerate}\n");
    fprintf(f, "    \\item Правило суммы: $(u + v)' = u' + v'$\n");
    fprintf(f, "    \\item Правило произведения: $(u \\cdot v)' = u' \\cdot v + u \\cdot v'$\n");
    fprintf(f, "    \\item Правило частного: $\\left(\\frac{u}{v}\\right)' = \\frac{u' \\cdot v - u \\cdot v'}{v^2}$\n");
    fprintf(f, "    \\item Цепное правило: $(f(g(x)))' = f'(g(x)) \\cdot g'(x)$\n");
    fprintf(f, "\\end{enumerate}\n");*/
    
    fprintf(f, "\\end{document}\n");
    
    fclose(f);
    printf("LaTeX correct save в %s\n", filename);
    printf("For compile: pdflatex %s\n", filename);
}