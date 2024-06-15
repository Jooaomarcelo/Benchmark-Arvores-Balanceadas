#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Arvores/arvores.h"
#include "Arvores/AVL.h"
#include "Arvores/ARB.h"
#include "Entrada_Saida/ES.h"


int main() {
    arvore *avl, *arb;
    clock_t inicio, fim;
    int seed, ver, controle, flag=0, rotacoesARB, rotacoesAVL;
    char nomeArquivo_Ordenado[50] = "entradaOrdenada.txt", nomeArquivo_Aleatorio[50]="entradaAleatoria.txt", path[55]="../Arquivos/";
    long long int tamanhoArquivo;
    double tempo;

    printf("Já possui os arquivos de entrada:\n1 - Sim\n2 - Não\n");
    scanf(" %d", &ver);
    if(ver==1) {
        printf("Nome do arquivo de dados ordenados: ");
        scanf(" %[^\n]", nomeArquivo_Ordenado);
        printf("Nome do arquivo de dados aleatórios: ");
        scanf(" %[^\n]", nomeArquivo_Aleatorio);
    }
    else {
        printf("Qual o nome para o arquivo de dados ordenados: ");
        scanf(" %[^\n]", nomeArquivo_Ordenado);

        printf("Digite a seed: ");
        scanf(" %d", &seed);
        printf("Qual o nome para o arquivo de dados aleatórios: ");
        scanf(" %[^\n]", nomeArquivo_Aleatorio);

        printf("Tamanho dos arquivo: ");
        scanf(" %lld", &tamanhoArquivo);
        
        if(!criaArquivoOrdenado(nomeArquivo_Ordenado, tamanhoArquivo))
            return 1;
        
        if(!criaArquivoAleatorios(nomeArquivo_Aleatorio, seed, tamanhoArquivo))
            return 1;
    }

    do {
    printf("\nÁrvore que deseja analisar:\n1 - AVL\n2 - Rubro-Negra\n0 - Sair\n");
    scanf(" %d", &flag);
    if(flag != 0 && flag != 1 && flag != 2) printf("Valor inválido! Tente novamente.");
    } while(flag != 0 && flag != 1 && flag != 2);

    while(flag != 0) {

        if(flag == AVL) {
            avl = criaArvore(AVL);
            realizarTeste(avl, nomeArquivo_Ordenado, flag, incercao, &rotacoesAVL);
            realizarTeste(avl, nomeArquivo_Aleatorio, flag, pesquisa, &rotacoesAVL);
            realizarTeste(avl, nomeArquivo_Ordenado, flag, remocao, &rotacoesAVL);
        }
        if(flag == ARB) {
            arb = criaArvore(ARB);
            realizarTeste(arb, nomeArquivo_Ordenado, flag, incercao, &rotacoesARB);
            realizarTeste(arb, nomeArquivo_Aleatorio, flag, pesquisa, &rotacoesARB);
            realizarTeste(arb, nomeArquivo_Ordenado, flag, remocao, &rotacoesARB);
        }

        do {
            printf("Escolha uma opção:\n0 - Sair\n1 - AVL\n2 - Rubro-Negra\n");
            scanf(" %d", &flag);
            if(flag != 0 && flag != 1 && flag != 2) printf("Valor inválido! Tente novamente.");
        } while(flag != 0 && flag != 1 && flag != 2);
    }

    return 0;
}