#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"
#include "AVL.h"

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

void criaAVL(arvore *arv) {
    arv->sentinela->fb=0;
}

int AVL_insereNo(arvore *arv, int valor, int *rotacoes) {
    no *aux, *atual, *novo = (no*)malloc(sizeof(no));
    if(!novo){
        return 0;
    }
    novo->chave = valor;
    novo->fb = 0;
    novo->Fesq = novo->Fdir = NULL;
    if(!arv->numElementos){
        arv->sentinela->Fdir = novo;
        novo->pai = arv->sentinela;
    }else{
        atual = aux = arv->sentinela->Fdir;
        while(aux){
            atual = aux;
            if(aux->chave > valor){
                aux = aux->Fesq;
            }else{
                aux = aux->Fdir;
            }
        }
        novo->pai = atual;
        if(atual->chave > valor){
            atual->Fesq = novo;
        }else{
            atual->Fdir = novo;
        }
    }
    arv->numElementos++;
    atualizaFB_insercao(arv, novo, rotacoes);
    return 1;
}

int AVL_removeNo(arvore *arv, int valor, int *rotacoes) {
    no *atual, *aux;
    atual = getRaiz(arv);
    if(atual) {
        // Percorrendo a árvore até encontrar o nó com o valor desejado
        while(atual && atual->chave != valor) {
            if(valor < atual->chave)
                atual = atual->Fesq;
            else
                atual = atual->Fdir;
        }

        // O elemento não se encontra na árvore
        if(!atual) return -1;
        
        // O nó a ser removido é uma folha
        if(!atual->Fesq && !atual->Fdir) {
            if(valor < atual->pai->chave)
                atual->pai->Fesq = NULL;
            else
                atual->pai->Fdir = NULL;
        }
        // O nó a ser removido possui dois filhos
        else if(atual->Fesq && atual->Fdir) {
            // Encontrar o sucessor do nó
            aux = atual;
            atual = atual->Fdir;
            while(atual->Fesq)
                atual = atual->Fesq;
            
            // Copiando o valor do sucessor para o nó que se deseja remover
            aux->chave = atual->chave;
            
            // Verificando se o sucessor possui filhos e removendo-o
            if(atual->Fdir) {
                if(atual->chave < atual->pai->chave) {
                    atual->Fesq = atual->Fdir;
                    atual->Fdir->pai = atual->pai;
                }
                else {
                    atual->pai->Fdir = atual->Fdir;
                    atual->Fdir->pai = atual->pai;
                }
            }
            else if(atual->chave < atual->pai->chave)
                atual->pai->Fesq = NULL;
            else
                atual->pai->Fdir = NULL;
        }
        // O nó a ser removido possui apenas um filho
        else if(atual->Fesq){
            if(valor < atual->pai->chave) {
                atual->pai->Fesq = atual->Fesq;
                atual->Fesq->pai = atual->pai;
            }    
            else {
                atual->pai->Fdir = atual->Fesq;
                atual->Fesq->pai = atual->pai;
            }
        }
        else{
            if(valor < atual->pai->chave) {
                atual->pai->Fesq = atual->Fdir;
                atual->Fdir->pai = atual->pai;
            }    
            else {
                atual->pai->Fdir = atual->Fdir;
                atual->Fdir->pai = atual->pai;
            }
        }
        atualizaFB_remocao(arv, atual->pai, atual->chave, rotacoes);
        free(atual);
        arv->numElementos--;
        return 1;
    }
    return 0;
}

void atualizaFB_insercao(arvore *arv, no *novoNo, int *rotacoes) {
    no *aux=novoNo;
    do {
        if (aux->chave < aux->pai->chave && aux->pai != arv->sentinela)
            aux->pai->fb--; 
        else if(aux->pai != arv->sentinela)
            aux->pai->fb++;
        aux = aux->pai;
    } while(aux->fb != 0 && aux->fb != 2 && aux->fb != -2 && aux->pai != arv->sentinela);

    if(aux->fb == 2 || aux->fb == -2)
        *rotacoes += balanceamento(arv, aux);
}

int balanceamento(arvore *arv, no *noDesbal) {
    int rotaciona=0;
    no *filho;
    if(noDesbal->fb == 2){
        //A sub-árvore direita está maior que a esquerda.

        filho = noDesbal->Fdir;
        if(filho->fb >= 0){
            //Rotação Simples

            //Verificando condições para a atualização dos fatores de balanceamento (fb) dos nós envolvidos
            if(filho->fb == 1){
                noDesbal->fb = filho->fb = 0;
            }else{
                noDesbal->fb = 1;
                filho->fb = -1;
            }

            //Rotacionando
            rotacaoEsq(noDesbal);
            rotaciona++;

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = filho;
            }
        }else{
            //Rotação dupla

            //Verificando condições para a atualização dos fatores de balanceamento (fb) dos nós envolvidos
            if(filho->Fesq->fb == 0){
                noDesbal->fb = filho->fb = 0;
            }else if(filho->Fesq->fb == 1){
                noDesbal->fb = -1;
                filho->fb = 0;
            }else{
                noDesbal->fb = 0;
                filho->fb = 1;
            }
            filho->Fesq->fb = 0;

            //Rotacionando
            rotacaoDir(filho);
            rotacaoEsq(noDesbal);
            rotaciona+=2;

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = noDesbal->pai;
            }
        }
    }else{
        //A sub-árvore esquerda está maior que a direita.

        filho = noDesbal->Fesq;
        if(filho->fb <= 0){
            //Rotação Simples

            //Verificando condições para a atualização dos fatores de balanceamento (fb) dos nós envolvidos
            if(filho->fb == -1){
                noDesbal->fb = filho->fb = 0;
            }else{
                noDesbal->fb = -1;
                filho->fb = 1;
            }

            //Rotacionando
            rotacaoDir(noDesbal);
            rotaciona++;

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = filho;
            }
        }else{
            //Rotação Dupla

            //Verificando condições para a atualização dos fatores de balanceamento (fb) dos nós envolvidos
            if(filho->Fdir->fb == 0){
                noDesbal->fb = filho->fb = 0;
            }else if(filho->Fdir->fb == 1){
                noDesbal->fb = 0;
                filho->fb = -1;
            }else{
                noDesbal->fb = 1;
                filho->fb = 0;
            }
            filho->Fdir->fb = 0;

            //Rotacionando
            rotacaoEsq(filho);
            rotacaoDir(noDesbal);
            rotaciona+=2;

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = noDesbal->pai;
            }
        }
    }
    return rotaciona;
}

void atualizaFB_remocao(arvore *arv, no *pai, int chaveRemovida, int *rotacoes) {
    no *aux=pai;

    if(aux == arv->sentinela)
        return;

    if(chaveRemovida < aux->chave)
        aux->fb++;
    else
        aux->fb--;
    
    // Consições de parada
    while(aux->pai != arv->sentinela && aux->fb != 2 && aux->fb != -2 && aux->fb != -1 && aux->fb != 1){
        aux = aux->pai;
        if(chaveRemovida < aux->chave) {
            aux->fb++;
        }else{
            aux->fb--;
        }
    }
    //Verificando se houve um desbalanceamento.
    if(aux->fb == 2 || aux->fb == -2){
        *rotacoes += balanceamento(arv, aux);
        if(aux->pai != arv->sentinela && aux->pai->fb == 0){
            atualizaFB_remocao(arv, aux->pai->pai, chaveRemovida, rotacoes);
        }
    }
}
