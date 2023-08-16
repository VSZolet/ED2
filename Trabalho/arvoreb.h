#ifndef _ARVOREB_H_
#define _ARVOREB_H_

#include <stdio.h>
#include <stdlib.h>

#define TIPO char

#define T 2           /*Número que define mínimo e máximo de chaves!*/
#define NOT_FOUND -1  /*Valor retornado quando o nó não existe!*/
#define TRUE 1        /*Booleano para verdadeiro!*/
#define FALSE 0       /*Booleano para falso!*/

/*Estrutura básica para uma árvore B: */
typedef struct _node {
  int n; /*Número de chaves armazenadas no nó!*/
  int folha; /*Booleano que indica se o nó é folha ou não!*/
  TIPO chaves[2 * T - 1]; /*Número máximo de chaves {tipo char} em um nó!*/
  struct _node *filhos[2 * T]; /*Ponteiros para os filhos de cada nó!*/
} No, Arvore;

/*Função para criar e inicializar uma árvore B:*/
Arvore* criar ();

/*Função para buscar uma chave em uma árvore B:*/
void imprimir (Arvore *a, int nivel);

/*Função para buscar uma chave em uma árvore B:*/
int buscar (Arvore *a, TIPO chave);

/*Função para dividir o nó caso esteja cheio.*/
Arvore* dividir_no (Arvore *x, int i, Arvore *y);

/*Funcão para inserir*/
Arvore* inserir_arvore_nao_cheia (Arvore *x, TIPO k);

/*Função para inserir uma chave em uma árvore B:*/
Arvore *inserir (Arvore *raiz, TIPO chave);

/*Removerá por caso 1 ou 3 (A ou B)*/
Arvore* remover_de_folha (Arvore *a, int index);

/*Removerá por caso 2 (A, B ou C)*/
Arvore* remover_de_nao_folha (Arvore *a, int index);

/*Função para verificar se raiz ficou vazia*/
Arvore *verificar_raiz_vazia (Arvore *raiz);

/*Função que retorna o index da primeira chave maior ou igual à chave*/
int buscar_index_remocao (Arvore *a, TIPO chave);

/* Função auxiliar para fundir 2 filhos */
Arvore *fundir (Arvore *a, int index);

/* Irá pegar uma chave do filho anterior [index-1] e inserir no atual */
Arvore *pegaAnterior(Arvore *a, int index);

/* Irá pegar uma chave do proximo filho [index+1] e inserir no atual */
Arvore *pegaProximo(Arvore *a, int index);

/* Função que preencher a->filhos[index] caso tenha T-1 chaves */
Arvore *preencher(Arvore *a, int index);

/* Ira verificar se é folha ou não, para escolher caso de remoção*/
Arvore *remover (Arvore *a, TIPO k);

#endif
