#include "arvoreb.h"

/*Função para dividir o nó, caso esteja cheio*/
Arvore* dividir_no (Arvore *x, int i, Arvore *y)
{
    int j;
    /* cria o novo nó filho, que irá armazenar T-1 chaves de y.*/
    Arvore *z = (Arvore *)malloc(sizeof(Arvore));
    z->folha = y->folha;
    z->n = T-1;

    /* copia os últimos T-1 filhos do nó y */
    for (j=0; j<T-1; j++)
        z->chaves[j] = y->chaves[j+T];

    /* copia os ultimos T filhos de y */
    if(y->folha==FALSE){
        for (j=0; j<T; j++)
            z->filhos[j] = y->filhos[j+T];
    }

    /* Reduz o número de chaves em y */
    y->n = T-1;

    /* criando o espaço para o novo filho do nó */
    for (j = x->n; j>=i+1; j--)
        x->filhos[j+1] = x->filhos[j];

    x->filhos[i+1] = z; /* Adiciona o filho ao espaço criado. */

    /* Uma chave de y precisa vir para o nó x, então
       é criado espaço para que ele seja inserido */
    for(j = x->n-1; j>=i; j--)
        x->chaves[j+1] = x->chaves[j];

    /* Copia a chave e aumenta a contagem de chaves em x */
    x->chaves[i] = y->chaves[T-1];
    x->n = x->n+1;

    return x;
}

/*Função que irá inserir quando o nó não estiver cheio*/
Arvore* inserir_arvore_nao_cheia (Arvore *x, TIPO k) {
    int i=x->n-1;

    /* Verifica se é uma folha */
    if(x->folha==TRUE)
    {
        /* Procura o local da nova chave, jogando para frente o que for maior que o mesmo. */
        while (i >= 0 && x->chaves[i] > k){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }
        /* Insere nova chave no local encontrado */
        x->chaves[i+1] = k;
        x->n += 1;

        return x;
    }
    else
    {
        /* procura o filho na qual será inserido */
        while (i >= 0 && x->chaves[i] > k)
            i--;

        /* verifica se o nó que será inserido não está cheio */
        if (x->filhos[i+1]->n == 2*T-1){
            /* Divide o filho caso esteja cheio */
            x = dividir_no(x, i+1, x->filhos[i+1]);
            /* verifica se ficará na esquerda ou direita do novo nó*/
            if (x->chaves[i+1] < k)
                i++;
        }
        x->filhos[i+1] = inserir_arvore_nao_cheia(x->filhos[i+1], k);
    }

    return x;
}

/*Função para inserir uma chave em uma árvore B:*/
Arvore *inserir (Arvore *raiz, TIPO chave)
{
    Arvore *r = raiz;
    if (r->n == (2*T - 1)) {
      Arvore *s = criar();
      s->folha = FALSE;
      s->filhos[0] = r;
      s = dividir_no (s, 0, r);
      s = inserir_arvore_nao_cheia (s, chave);
      return s;
    }
    else {
      return inserir_arvore_nao_cheia (r, chave);
    }
}
