#include "../Arvores/arvores.h"

int criaArquivoOrdenado(char *nomeArquivo, long long int tamanho);

// Função que recebe um arquivo, uma seed e o tamanho do vetor
// e cria um arquivo de tamanho x (parâmetro tamanho) de números
// aleatórios de 0 até o 10000;
// 0 - Se houve erro ao abrir o arquivo;
// 1 - Se criou o arquivo com sucesso.
int criaArquivoAleatorios(char *nomeArquivo, int seed, long long int tamanho);

int criaArquivoResultados(int operacao, char *caminho, int rotacoes, double tempo);

double calcularTempo(clock_t inicio, clock_t fim);

int realizarTeste(arvore *arv, char *nomeArquivo, int tipoArvore, int operacao, int *rotacoes);
