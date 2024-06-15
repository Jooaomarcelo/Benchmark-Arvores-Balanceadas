typedef struct no no;
typedef struct arvore arvore;

#define AVL 1
#define ARB 2

#define incercao 1
#define remocao 2
#define pesquisa 3

//Função que cria e retorna uma estrutura do tipo árvore balanceada utilizando o algoritmo AVL
arvore* criaArvore(int tipoArvore);

//Função que imprime a árvore em pré-ordem
//printf("%d - %d\n", raiz->chave, raiz->pai->chave);
void imprimePreOrdem(no *raiz, int tipoArvore);

//Função que retorna a raiz da árvore
no *getRaiz(arvore *arv);

//Função que retorna a quantidade de elementos da árvore
int getNumElementos(arvore *arv);

no *pesquisaArvore(arvore *arv, int valor);

//Função que lê um arquivo com números inteiros e um tipo
//Se o tipo for 1, a função deve chamar insereNo
//Se o tipo for 2, a função deve chamar removeNo
//Retorna -2 se o arquivo não puder ter sido lido
//Se o tipo for 1, insere os elementos na árvore e retorna os valores obtidos com o processamento da inserção
//  Retorna 1 se a inserção foi realizada com sucesso
//  Retorna 0 se não foi possível realizar a inserção
//Se o tipo for 2, remove os elementos da árvore e retorna os valores obtidos com o processamento da remoção
//  Retorna 1 se o elemento foi removido
//  Retorna 0 se a árvore estiver vazia
//Os valores retornados são tratados na main
int processaCarga(arvore *arv, char *nomeArquivo, int tipoArvore, int operacao, int *rotacoes);

//Função que implementa a rotação à direita
void rotacaoDir(no *noDesbal);

//Função que implementa a rotação à esquerda
void rotacaoEsq(no *noDesbal);
