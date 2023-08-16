#include "arvoreb.h"

/* Removerá caso seja um nó folha. */
Arvore *remover_de_folha (Arvore *a, int index)
{
    int i;
    /* Puxa todos os número após o index uma posição pra trás. */
    for (i=index+1; i < a->n; i++)
        a->chaves[i-1] = a->chaves[i];

    a->n -= 1; /* diminui a contagem de chaves em 1 */

    return a;
}

/* Removerá caso seja um nó com filhos. */
Arvore *remover_de_nao_folha (Arvore *a, int index)
{
    TIPO k = a->chaves[index];
    TIPO anterior, proximo;
    Arvore *aux;

    /* Caso 2A. Verifica se o filho da esquerda tem pelo menos T filhos, para trazer a
       maior chave, ou "anterior", para por no local dele, removendo-o então. */
    if (a->filhos[index]->n >= T)
    {
        aux = a->filhos[index];
        /* irá ao filho mais a direita até atingir uma folha, pegando então a ultima chave.*/
        while (aux->folha==FALSE)
            aux = aux->filhos[aux->n];

        anterior = aux->chaves[aux->n-1];
        a->chaves[index] = anterior;
        remover(a->filhos[index], anterior);

    }
    /* Caso 2B. Verifica se o filho da direita tem pelo menos T filhos, para trazer a
       menor chave, ou "proximo", para por no local dele, removendo-o então.*/
    else if (a->filhos[index+1]->n >= T)
    {
        aux = a->filhos[index+1];
        /* irá ao filho mais a esquerda, até atingir uma folha, pegando então a primeira chave. */
        while (aux->folha==FALSE)
            aux = aux->filhos[0];

        proximo = aux->chaves[0];
        a->chaves[index] = proximo;
        remover(a->filhos[index+1], proximo);
    }
    /* Caso 2C. Se nenhum tem pelo menos T filhos, iniciará o caso 2C, fundindo então
       k e os filhos de index com os filhos de index+1, deixando index com 2T-1 filhos.
       remove-se então, recursivamente, k. */
    else
    {
        fundir(a, index);
        a->filhos[index] = remover(a->filhos[index], k);
    }

    return a;
    }

//Função para verificar se raiz ficou vazia
Arvore *verificar_raiz_vazia (Arvore *raiz){
    /*Se após a remoção a raiz tiver 0 chaves, tornar o primeiro filho a nova raiz se existir filho; caso contrário ajustar a raiz para NULL. Liberar a raiz antiga*/

    if (raiz->n==0){
        Arvore *v = raiz;
        raiz = raiz->filhos[0];
        free(v);
    }

    return raiz;
}

/*Função que retorna o index da primeira chave maior ou igual à chave*/
int buscar_index_remocao (Arvore *a, TIPO chave) {

   int index = 0;

   /*Procurando a chave no vetor de chaves */
   while ((index < a->n) && (a->chaves[index] < chave))
     index++;

   return index;
}

/* Função para fundir 2 filhos */
Arvore *fundir (Arvore *a, int index)
{
    int i;
    /* Duas árvores auxiliares, uma para o filho que irá receber as chaves do próximo filho (herdeiro) e o próximo filho em si(irmão) */
    Arvore *herdeiro = a->filhos[index];
    Arvore *irmao = a->filhos[index+1];

    /* Puxa a chave do nó atual e coloca na posição T-1 do herdeiro. */
    herdeiro->chaves[T-1] = a->chaves[index];

    /* Copia as chaves do irmão para o herdeiro no fim do vetor */
    for (i=0; i < irmao->n; i++)
        herdeiro->chaves[i+T] = irmao->chaves[i];

    /* Copia os filhos do irmão para o herdeiro, caso não seja um nó folha. */
    if (herdeiro->folha==FALSE)
    {
        for(i=0; i <= irmao->n; i++)
            herdeiro->filhos[i+T] = irmao->filhos[i];
    }

    /* Move todas as chaves depois de index em -1 para preencher o espaço de mover as chaves para o filho. */
    for (i=index+1; i < a->n; i++)
        a->chaves[i-1] = a->chaves[i];

    /* Move os ponteiros filhos depois de index+1 em -1 para preencher os espaços.*/
    for (i=index+2; i <= a->n; i++)
        a->filhos[i-1] = a->filhos[i];

    /* Arruma os contadores de chaves. */
    herdeiro->n += irmao->n+1;
    a->n--;

    /* libera memória que o irmão ocupava anteriormente. */
    free(irmao);

    return a;
}

/* Irá pegar uma chave do filho anterior [index-1] e inserir no atual */
Arvore *pegaAnterior(Arvore *a, int index)
{
    int i;
    Arvore *atual = a->filhos[index];
    Arvore *anterior = a->filhos[index-1];

    /* Pega a ultima chave do anterior (a maior) e irá colocar no lugar do pai.
       O pai desce para a primeira posição do atual(se tornando o menor),
       mantendo assim o equilíbrio */

    /* Move as chaves do atual para frente. */
    for (i = atual->n-1; i>=0; i--)
        atual->chaves[i+1] = atual->chaves[i];

    /* Caso ele não seja um nó folha é necessário mover todos os ponteiros filhos também */
    if (atual->folha==FALSE) {
        for(i = atual->n; i>=0; i--)
            atual->filhos[i+1] = atual->filhos[i];
    }

    /* Enfim, colocando a primeira chave do atual sendo o (antigo)pai */
    atual->chaves[0] = a->chaves[index-1];

    /* Coloca entãp o ultimo filho do anterior como o primeiro filho do atual */
    if(atual->folha==FALSE)
        atual->filhos[0] = anterior->filhos[anterior->n];

    /* colocamos a ultima chave do anterior no lugar a qual precisa ser colocado agora */
    a->chaves[index-1] = anterior->chaves[anterior->n-1];

    /* e por ultimo balanceia n em ambos. */
    atual->n += 1;
    anterior->n -= 1;

    return a;
}

/* Irá pegar uma chave do proximo filho [index+1] e inserir no atual */
Arvore *pegaProximo(Arvore *a, int index)
{
    int i;
    Arvore *atual = a->filhos[index];
    Arvore *proximo = a->filhos[index+1];

    /* O nó pai é colocado na ultima posição de chaves do atual, se tornando a maior.
       A primeira chave (a menor) do próximo se torna o novo pai,
       mantendo assim o equilíbrio. */

    /* a chave pai é colocado na ultima posição do filho atual */
    atual->chaves[(atual->n)] = a->chaves[index];

    /* caso não seja um nó folha, o primeiro filho do próximo é inserido como ultimo filho do atual */
    if (atual->folha==FALSE)
        atual->filhos[(atual->n)+1] = proximo->filhos[0];

    /* A primeira, e menor, chave do próximo é inserida no local do (antigo)pai */
    a->chaves[index] = proximo->chaves[0];

    /* Reorganiza todas as chaves 1 passo para trás */
    for (i=1; i < proximo->n; i++)
        proximo->chaves[i-1] = proximo->chaves[i];

    /* Caso não seja um nó folha, move todos os ponteiros filhos também para trás */
    if (proximo->folha==FALSE){
        for(i=1; i <= proximo->n; i++)
            proximo->filhos[i-1] = proximo->filhos[i];
    }

    /* e por ultimo balanceia n em ambos */
    atual->n += 1;
    proximo->n -= 1;

    return a;
}

/* Função que preencher a->filhos[index] caso tenha T-1 chaves */
Arvore *preencher(Arvore *a, int index)
{
    /* Se o filho anterior, ou index-1, tem T ou mais chaves, pega uma chave dele. Caso 3A */
    if (index!=0 && a->filhos[index-1]->n >= T)
        a = pegaAnterior(a, index);

    /* Se o próximo filho, ou index+1, tem T ou mais chaves, pega uma chave dele. Caso 3B */
    else if (index!=a->n && a->filhos[index+1]->n >= T)
        a = pegaProximo(a, index);

    /* Se nenhum dos dois tiver T ou mais chaves, irá fundir com o irmão dele.
       É fundido com o próximo se não for o último ou, se for, com o anterior. */
    else
    {
        if (index != a->n)
            a = fundir(a, index);
        else
            a = fundir(a, index-1);
    }
    return a;
}

/* Base geral para identificar o local do valor e o caso de remoção necessário. */
Arvore *remover (Arvore *a, TIPO k){
    int aux;

    if (a == NULL)
        printf("Arvore não existe.\n");

    int index = buscar_index_remocao(a, k);

   //A chave a ser removida está presente neste nó
    if (index >= 0 && a->chaves[index] == k){
        if (a->folha==TRUE)
            a = remover_de_folha (a, index);
        else
            a = remover_de_nao_folha (a, index);
    }
    else{
      //Se este nó é um nó folha, então a chave não está na árvore
        if (a->folha==TRUE){
        printf("\nA chave %c não está na árvore.\n",k);

        return a;
        }

        /* Ira servir de auxilio, pois caso o filho esteja em algum filho desse nó,
           ele irá virar 1 caso esteja dentro do ultimo filho. É necessário pois caso
           a função preencher use a função fundir, a árvore tera n-1 depois do próximo passo.*/
        if (index == a->n)
            aux = 1;

        /* Se o filho onde é para estar a chave tem menos que T filhos,
           é necessário preencher este filho */
        if(a->filhos[index]->n < T)
            a = preencher(a, index);

        /* Caso a função preencher tenha usado a função fundir, haverá n-1 filhos com relação a
           antes da função ter sido utilizada, então verificamos se, anteriormete, index apontava
           para o ultimo filho (aux==1) e se foi fundido (index se tornará maior que n, uma vez que
           eles eram do mesmo tamanho, ou seja, index > a->n) */
        if((aux==1) && (index > a->n))
            a->filhos[index-1] = remover(a->filhos[index-1], k);
        else
            a->filhos[index] = remover(a->filhos[index], k);

   }
   a = verificar_raiz_vazia(a);

   return a;
}

