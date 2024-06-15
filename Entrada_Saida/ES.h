#include "../Arvores/arvores.h"

// Função que recebe o nome do arquivo, e seu tamanho
// e cria um arquivo de números ordenados
// 0 - Se houve erro ao abrir o arquivo;
// 1 - Se criou o arquivo com sucesso.
int criaArquivoOrdenado(char *nomeArquivo, long long int tamanho);

// Função que recebe o nome do arquivo, uma seed e seu tamanho
// e cria um arquivo de números aleatórios de 0 até o 10000;
// 0 - Se houve erro ao abrir o arquivo;
// 1 - Se criou o arquivo com sucesso.
int criaArquivoAleatorios(char *nomeArquivo, int seed, long long int tamanho);

// Função para a criação de arquivos com os resultados obtidos
// Entrada: tipo da operação, o caminho para a criação do arquivo,
// o número de rotações e o tempo a serem escritos no arquivo.
// 0 - Se houve erro ao abrir o arquivo;
// 1 - Se criou o arquivo com sucesso.
int criaArquivoResultados(int operacao, char *caminho, int rotacoes, double tempo);

// Função para calcular o tempo em milisegundos
// Entrada: tempo de início e fim.
// Saída: tempo em milisegundos.
double calcularTempo(clock_t inicio, clock_t fim);

// Função que realiza o teste desejado
// Entrada: a árvore (AVL ou Rubro-Negra), o nome do arquivo, a operacao,
// e o ponteiro para a variável que controla o número de rotações realizadas em uma árvore
// Saída:
//  Atualização da variável rotacoes;
//  0 - Se houve sucesso na realização do teste;
//  1 - Se houve erro na abertura do arquivo;
//  2 - Se houve erro na operação realizada;
//  3 - Se houve erro na criação do arquivo de resultados.
int realizarTeste(arvore *arv, char *nomeArquivo, int tipoArvore, int operacao, int *rotacoes);
