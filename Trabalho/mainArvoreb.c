#include "arvoreb.h"


/*Função principal:*/
int main () {

    Arvore *a = criar();

    a = inserir (a, 'F');
    a = inserir (a, 'S');
    a = inserir (a, 'Q');
    a = inserir (a, 'K');
    a = inserir (a, 'C');
    a = inserir (a, 'L');
    a = inserir (a, 'H');
    a = inserir (a, 'T');
    a = inserir (a, 'V');
    a = inserir (a, 'W');
    a = inserir (a, 'M');
    a = inserir (a, 'R');
    a = inserir (a, 'N');
    a = inserir (a, 'P');
    a = inserir (a, 'A');
    a = inserir (a, 'B');
    a = inserir (a, 'X');
    a = inserir (a, 'Y');
    a = inserir (a, 'D');
    a = inserir (a, 'Z');
    a = inserir (a, 'E');

    printf("Arvore apos insercoes: \n");
    imprimir (a, 0);

    /* Teste de remoção. */

    printf("Arvore apos remocao de S, caso 1: \n");
    a = remover(a, 'S');
    imprimir (a, 0);

    printf("Arvore apos remocao de F, caso 2A: \n");
    a = remover (a, 'F');
    imprimir (a, 0);

    printf("Arvore apos remocao de T, caso 2C: \n");
    a = remover (a, 'T');
    imprimir (a, 0);

    printf("Arvore apos remocao de A, caso 3A: \n");
    a = remover (a, 'A');
    imprimir (a, 0);

    printf("Arvore apos remocao de B, caso 3B: \n");
    a = remover (a, 'B');
    imprimir (a, 0);

   return 0;
}
