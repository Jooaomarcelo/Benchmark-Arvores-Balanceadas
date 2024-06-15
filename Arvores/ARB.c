#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"
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

void criaARB(arvore *arv) {
    arv->sentinela->cor = preto;
}

int ARB_insereNo(arvore *arv, int valor, int *rotacoes) {
    no *aux, *atual, *novo = (no*)malloc(sizeof(no));
    if(!novo){
        return 0;
    }

    novo->chave = valor;
    novo->Fesq = novo->Fdir = NULL;
    novo->cor = vermelho; // Colore o novo nó de vermelho
    
    if(!arv->numElementos) {
        novo->pai = arv->sentinela;
        novo->cor = preto;
        arv->sentinela->Fdir = novo;
        arv->numElementos++;
        return 1;
    }
    else {
        atual = getRaiz(arv);
        while(atual) {
            aux = atual;
            if(atual->chave > valor)
                atual = atual->Fesq;
            else    
                atual = atual->Fdir;
        }

        novo->pai = aux;
        if(valor < aux->chave)
            aux->Fesq = novo;
        else
            aux->Fdir = novo;

        if(novo->pai->cor == vermelho)
            *rotacoes += atualizaInsercao(arv, novo);
        arv->numElementos++;
        return 1;
    }
    return 0;
}

int ARB_removeNo(arvore *arv, int valor, int *rotacoes) {
    no *atual, *aux, *x;
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

        if(atual->cor == preto) 
            *rotacoes += atualizaRemocao(arv, atual);
        arv->numElementos--;
        return 1;
    }
    return 0;
}

int atualizaInsercao(arvore *arv, no *z) {
    int rotaciona=0;
    no *tio;
    while(z->pai != arv->sentinela && z->pai->cor == vermelho) {
        // z é neto à esquerdo
        if(z->pai == z->pai->pai->Fesq) {
            tio = z->pai->pai->Fdir;    

            // Caso 1
            if(tio && tio->cor == vermelho) {
                z->pai->cor = preto;
                tio->cor = preto;
                z->pai->pai->cor = vermelho;
                z = z->pai->pai;
            }
            else {
                // Caso 2
                if(z == z->pai->Fdir) {
                    z = z->pai;
                    rotacaoEsq(z);
                    rotaciona++;
                }

                // Caso 3
                z->pai->cor = preto;
                z->pai->pai->cor = vermelho;
                rotacaoDir(z->pai->pai);
                rotaciona++;
            }
        }
        // z é neto à direita
        else {
            tio = z->pai->pai->Fesq;

            // Caso 1
            if(tio && tio->cor == vermelho) {
                z->pai->cor = preto;
                tio->cor = preto;
                z->pai->pai->cor = vermelho;
                z = z->pai->pai;
            }
            else {
                // Caso 2
                if(z == z->pai->Fesq) {
                    z = z->pai;
                    rotacaoDir(z);
                    rotaciona++;
                }

                // Caso 3
                z->pai->cor = preto;
                z->pai->pai->cor = vermelho;
                rotacaoEsq(z->pai->pai);
                rotaciona++;
            }
        }
    }
    arv->sentinela->Fdir->cor = preto;
    return rotaciona;
}

int atualizaRemocao(arvore *arv, no *z) {
    int rotaciona=0;
    no *w;
    if(z->Fdir && z->Fdir->cor == vermelho)
        z->Fdir->cor = preto;
    else if(z->Fesq && z->Fesq->cor == vermelho)
        z->Fesq->cor = preto;
    else {
        while (z->pai != arv->sentinela && z->cor == preto) {
            if (z->chave < z->pai->chave) { // z é filho esquerdo
                w = z->pai->Fdir; // w é o irmão de z
                
                if (w->cor == vermelho) { // Caso 1: w é vermelho
                    w->cor = preto;
                    z->pai->cor = vermelho;
                    rotacaoEsq(z->pai);
                    rotaciona++;
                    w = z->pai->Fdir;
                }
                
                if ((!w->Fesq || w->Fesq->cor == preto) && (!w->Fdir || w->Fdir->cor == preto)) { // Caso 2: ambos filhos de w são pretos
                    w->cor = vermelho;
                    z = z->pai;
                } else {
                    if (w->Fdir && w->Fdir->cor == preto) { // Caso 3: w é preto e o filho direito de w é preto
                        w->Fesq->cor = preto;
                        w->cor = vermelho;
                        rotacaoDir(w);
                        rotaciona++;
                        w = z->pai->Fdir;
                    }
                    // Caso 4: w é preto e o filho direito de w é vermelho
                    w->cor = z->pai->cor;
                    z->pai->cor = preto;
                    if(w->Fdir) w->Fdir->cor = preto;
                    rotacaoEsq(z->pai);
                    rotaciona++;
                    z = arv->sentinela->Fdir;
                }
            } else { // z é filho direito
                w = z->pai->Fesq; // w é o irmão de z
                
                if (w->cor == vermelho) { // Caso 1: w é vermelho
                    w->cor = preto;
                    z->pai->cor = vermelho;
                    rotacaoDir(z->pai);
                    rotaciona++;
                    w = z->pai->Fesq;
                }
                
                if ((!w->Fesq || w->Fesq->cor == preto) && (!w->Fdir || w->Fdir->cor == preto)) { // Caso 2: ambos filhos de w são pretos
                    w->cor = vermelho;
                    z = z->pai;
                } else {
                    if (w->Fesq &&  w->Fesq->cor == preto) { // Caso 3: w é preto e o filho esquerdo de w é preto
                        w->Fdir->cor = preto;
                        w->cor = vermelho;
                        rotacaoEsq(w);
                        rotaciona++;
                        w = z->pai->Fesq;
                    }
                    // Caso 4: w é preto e o filho esquerdo de w é vermelho
                    w->cor = z->pai->cor;
                    z->pai->cor = preto;
                    if(w->Fesq) w->Fesq->cor = preto;
                    rotacaoDir(z->pai);
                    rotaciona++;
                    z = arv->sentinela->Fdir;
                }
            }
        }
    }
    z->cor = preto;
    return rotaciona;
}
