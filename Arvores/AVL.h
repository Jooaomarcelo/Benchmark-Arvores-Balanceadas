#include "arvores.h"

// Função que modifica a árvore padrão para uma AVL
void criaAVL(arvore *arv);

//Função que insere um elemento na árvore
//Retorna 1 se a inserção foi realizada com sucesso
//Retorna 0 se não foi possível realizar a inserção
int AVL_insereNo(arvore *arv, int valor, int *rotacoes);

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Retorna -1 caso o elemento a ser removido não esteja na árvore
int AVL_removeNo(arvore *arv, int valor, int *rotacoes);

//Função que verifica o desbalanceamento na inserção
void atualizaFB_insercao(arvore *arv, no *novoNo, int *rotacoes);

//Função que faz o balanceamento após inseção ou remoção
int balanceamento(arvore *arv, no *noDesbal);

//Função que verifica o desbalanceamento na remoção
void atualizaFB_remocao(arvore *arv, no *pai, int chaveRemovida, int *rotacoes);
