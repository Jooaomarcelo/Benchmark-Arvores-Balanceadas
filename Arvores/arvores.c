#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvores.h"
#include "AVL.h"
#include "ARB.h"


struct no {
    int chave;
    int fb;
    int cor;
    no *pai;
    no *Fesq;
    no *Fdir;
};

struct arvore {
    no *sentinela;
    int numElementos;
};

arvore* criaArvore(int tipoArvore) {
    arvore *arv = (arvore*)malloc(sizeof(arvore));

    if(!arv)
        return NULL;
    
    arv->numElementos = 0;
    arv->sentinela = (no*)malloc(sizeof(no));
    if(!arv->sentinela){
        return NULL;
    }
    arv->sentinela->pai = arv->sentinela->Fdir = arv->sentinela->Fesq = NULL;
    arv->sentinela->chave = -1000;
    if(tipoArvore == 1) criaAVL(arv);
    if(tipoArvore == 2) criaARB(arv);
    return arv;
}

void imprimePreOrdem(no *raiz, int tipoArvore) {
    if(raiz){
        if(tipoArvore == 1) {
            printf("%d - %d - %d\n",raiz->chave, raiz->pai->chave, raiz->fb);
            imprimePreOrdem(raiz->Fesq, tipoArvore);
            imprimePreOrdem(raiz->Fdir, tipoArvore);
        }
        if(tipoArvore == 2) {
            char cor[9];

            if(raiz->cor == 0) strcpy(cor, "Preto");
            else strcpy(cor, "Vermelho");

            printf("%d - %d - %s\n",raiz->chave, raiz->pai->chave, cor);
            imprimePreOrdem(raiz->Fesq, tipoArvore);
            imprimePreOrdem(raiz->Fdir, tipoArvore);
        }
    }
}

no *getRaiz(arvore *arv) {
    return arv->sentinela->Fdir;
}

int getNumElementos(arvore *arv) {
    return arv->numElementos;
}

no *pesquisaArvore(arvore *arv, int valor) {
    no *atual=arv->sentinela->Fdir;

    if(!atual)
        return NULL;

    while(atual && atual->chave != valor) {
        if(valor < atual->chave)
            atual = atual->Fesq;
        else
            atual = atual->Fdir;
    }

    if(!atual) {
        printf("Valor não encontrado na árvore!\n");
        return NULL;
    }

    return atual;
}

int processaCarga(arvore *arv, char *nomeArquivo, int tipoArvore, int operacao, int *rotacoes) {
    FILE *arq = fopen(nomeArquivo, "r");
    int valor;
    if(!arq){
        return -2;
    }

    if(tipoArvore == 1) {
        if(operacao == 1) {
            while(!feof(arq)){
                fscanf(arq, "%d", &valor);
                if(!AVL_insereNo(arv, valor, rotacoes))
                    return 0;
            }
        }
        else if(operacao == 2) {
            while(!feof(arq)){
                fscanf(arq, "%d", &valor);
                if(!AVL_removeNo(arv, valor, rotacoes))
                    return 0;
            }
        }
        else {
            while(!feof(arq)){
                fscanf(arq, "%d", &valor);
                if(!pesquisaArvore(arv, valor))
                    return 0;
            }
        }
    }

    if(tipoArvore == 2) {
        if(operacao == 1) {
            while(!feof(arq)){
                fscanf(arq, "%d", &valor);
                if(!ARB_insereNo(arv, valor, rotacoes))
                    return 0;
            }
        }
        else if(operacao == 2)  {
            while(!feof(arq)){
                fscanf(arq, "%d", &valor);
                if(!ARB_removeNo(arv, valor, rotacoes))
                    return 0;
            }
        }
        else {
            while(!feof(arq)){
                fscanf(arq, "%d", &valor);
                if(!pesquisaArvore(arv, valor))
                    return 0;
            }
        }
    }
    return 1;
}

void rotacaoDir(no *noDesbal) {
    if (noDesbal == noDesbal->pai->Fesq)
        noDesbal->pai->Fesq = noDesbal->Fesq;
    else
        noDesbal->pai->Fdir = noDesbal->Fesq;
    
    noDesbal->Fesq->pai = noDesbal->pai;
    noDesbal->pai = noDesbal->Fesq;
    noDesbal->Fesq = noDesbal->pai->Fdir;
    if(noDesbal->Fesq) 
        noDesbal->Fesq->pai = noDesbal;
    noDesbal->pai->Fdir = noDesbal;
}

void rotacaoEsq(no *noDesbal) {
    if (noDesbal == noDesbal->pai->Fesq)
        noDesbal->pai->Fesq = noDesbal->Fdir;
    else
        noDesbal->pai->Fdir = noDesbal->Fdir;
    
    noDesbal->Fdir->pai = noDesbal->pai;
    noDesbal->pai = noDesbal->Fdir;
    noDesbal->Fdir = noDesbal->pai->Fesq;
    if(noDesbal->Fdir) 
        noDesbal->Fdir->pai = noDesbal;
    noDesbal->pai->Fesq = noDesbal;
}
