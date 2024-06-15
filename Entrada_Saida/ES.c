#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ES.h"


int criaArquivoOrdenado(char *nomeArquivo, long long int tamanho) {
    long long int i;
    FILE *arq;

    arq = fopen(nomeArquivo, "w");
    if(!arq) {
        printf("Falha ao criar arquivo!\n");
        return 0;
    } 

    for(i=1; i<tamanho; i++) {
        fprintf(arq, "%lld\n", i);
    }
    fprintf(arq, "%lld", i);

    fclose(arq);
    return 1;
}

int criaArquivoAleatorios(char *nomeArquivo, int seed, long long int tamanho) {
    long long int i;
    FILE *arq;

    arq = fopen(nomeArquivo, "w");
    if(!arq) {
        printf("Falha ao criar arquivo!\n");
        return 0;
    }

    srand(seed);

    for(i=1;i<tamanho;i++) {
        fprintf(arq, "%lld\n", (long long int)(rand() % (10000 + 1)));
    }
    fprintf(arq, "%lld", (long long int)(rand() % (10000 + 1)));

    fclose(arq);
    return 1;
}

int criaArquivoResultados(int operacao, char *caminho, int rotacoes, double tempo) {
    FILE *arq;

    arq = fopen(caminho, "w");
    if(!arq) return 0;

    if(operacao != pesquisa){
        fprintf(arq, "%d\n", rotacoes);
        fprintf(arq, "%lf", tempo);
    }
    else
        fprintf(arq, "%lf", tempo);

    fclose(arq);
    return 1;
}

double calcularTempo(clock_t inicio, clock_t fim) {
    return (double)(fim - inicio)/(CLOCKS_PER_SEC/1000);
}

int realizarTeste(arvore *arv, char *nomeArquivo, int tipoArvore, int operacao, int *rotacoes) {
    clock_t inicio, fim;
    int controle;
    double tempo;
    char resultados[50];

    *rotacoes = 0;
    if(operacao == incercao) {
        if(tipoArvore == AVL)
            strcpy(resultados, "Resultados/AVL_insercao.txt");
        else
            strcpy(resultados, "Resultados/ARB_insercao.txt");
    }
    else if(operacao == remocao) {
        if(tipoArvore == AVL)
            strcpy(resultados, "Resultados/AVL_remocao.txt");
        else
            strcpy(resultados, "Resultados/ARB_remocao.txt");
    }
    else {
        if(tipoArvore == AVL)
            strcpy(resultados, "Resultados/AVL_pesquisa.txt");
        else
            strcpy(resultados, "Resultados/ARB_pesquisa.txt");
    }

    inicio = clock();
    controle = processaCarga(arv, nomeArquivo, tipoArvore, operacao, rotacoes);
    fim = clock();

    if(controle == -2) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }
    if(controle == 0) {
        printf("Erro na operação.\n");
        return 2;
    }

    tempo = calcularTempo(inicio, fim);
    if(!criaArquivoResultados(operacao, resultados, *rotacoes, tempo)) {
        printf("Erro ao criar arquivo.");
        return 3;
    }
    return 0;
}

