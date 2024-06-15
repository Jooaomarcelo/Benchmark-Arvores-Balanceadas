#include "arvores.h"

#define preto 0
#define vermelho 1

// Função que modifica a árvore padrão para uma ARB (Árvore Rubro-Negra).
void criaARB(arvore *arv);

//Função que insere um elemento na árvore.
//Retorna 1 se a inserção foi realizada com sucesso;
//Retorna 0 se não foi possível realizar a inserção.
int ARB_insereNo(arvore *arv, int valor, int *rotacoes);

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor.
//Retorna 1 se o elemento foi removido;
//Retorna 0 se a árvore estiver vazia;
//Retorna -1 caso o elemento a ser removido não esteja na árvore.
int ARB_removeNo(arvore *arv, int valor, int *rotacoes);

//Função que restaura as propriedades vermelho-preto da árvore após inserção.
int atualizaInsercao(arvore *arv, no *z);

//Função que restaura as propriedades vermelho-preto da árvore após remoção.
int atualizaRemocao(arvore *arv, no *z);
