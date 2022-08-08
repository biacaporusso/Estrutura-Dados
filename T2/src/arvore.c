#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "figuras.h"

// estrutura nó
typedef struct no {
    Item conteudo;
    struct no *esquerda, *meio, *direita;
} No;

// estrutura árvore com um ponteiro para um nó
typedef struct {
    No *raiz;
    int tamanho;
} arvT;

Tree criaArvore() {
    arvT *arvore;
    arvore = (arvT*) malloc(sizeof(arvT));
    arvore->raiz = NULL;
    arvore->tamanho = 0;

    return(arvore);
}

Node getRaiz(Tree T) {
    arvT* arvore = (arvT*) T;
    return arvore->raiz;
}

Item getItem(Node N) {
    No* no = (No*) N;
    return no->conteudo;
}

Node getEsquerda(Node N) {
    No* no = (No*) N;
    return no->esquerda;
}

Node getDireita(Node N) {
    No* no = (No*) N;
    return no->direita;
}

Node getMeio(Node N) {
    No* no = (No*) N;
    return no->meio;
}

/*  nova versão para a inserção, mais resumida
    perceba que agora é só uma função
*/
Node inserir(Tree T, Node N, Item info, double xFig, double yFig) {
    No* raiz = (No*) N;
    arvT* tree = (arvT*) T;
    if(raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = info;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->meio = NULL;
        if(tree->raiz == NULL)
            tree->raiz = novo;
        return novo;
    } else {
        if(xFig < getX(raiz->conteudo)) {                 // se x1 < x insere na esquerda
            raiz->esquerda = inserir(T, raiz->esquerda, info, xFig, yFig);
        } else if(yFig < getY(raiz->conteudo)) {          // se x1 >= x e y1 < y insere no meio
            raiz->meio = inserir(T, raiz->meio, info, xFig, yFig);
        } else {                                                 // se x1 >= x e y1 >= y insere na direita
            raiz->direita = inserir(T, raiz->direita, info, xFig, yFig);
        } 
        return raiz;
    }
}

// função que retorna o tamanho de uma árvore
int tamanho(Node N) {
    No* raiz = (No*) N;
    if(raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->meio) + tamanho(raiz->direita);
}

// função para buscar um elemento na árvore
Item buscar(Node N, Item info) {
    No* raiz = (No*) N;
    if(raiz == NULL) {
        return 0;
        //return NULL;
    } else {
        if(raiz->conteudo == info)
            return raiz->conteudo;
            //return raiz->conteudo;
        else {
            if(getX(info) < getX(raiz->conteudo)) 
                return buscar(raiz->esquerda, info);
            else if(getY(info) < getY(raiz->conteudo))
                return buscar(raiz->meio, info);
            else
                return buscar(raiz->direita, info);
        }
    }
}

/*  faz a impressão da árvore em ordem crescente
    esquerda - raiz - direita
*/
void imprimir(Node N) {
    No* raiz = (No*) N;
    if(raiz != NULL) {
        imprimir(raiz->esquerda);
        imprimir(raiz->meio);
        imprimir(raiz->direita);
        printf("%s\n", getID(raiz->conteudo));
    }
}

// função para a remoção de um nó
Node removeNo(Node N, Item info) {
    No* raiz = (No*) N;
    // 3 casos de remoção:
    // 1º : quando o nó que desejo remover é folha (não possui filhos);
    // 2º : quando o nó que desejo remover tem 1 filho (esquerda ou direita);
    // 3º : quando o nó que desejo remover tem os 2 filhos (caso mais difícil).
    if(raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if(raiz->conteudo == info) {
            // remove nós folhas (nós sem filhos)
            // if(raiz->esquerda == NULL && raiz->meio == NULL && raiz->direita == NULL)
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                return NULL;
            }
            else{
                // remover nós que possuem apenas 1 filho
                if(raiz->esquerda == NULL || raiz->direita == NULL){
                    No *aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                }
                else{
                    No *aux = raiz->esquerda;
                    while(aux->direita != NULL)
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = info;
                    raiz->esquerda = removeNo(raiz->esquerda, info);
                    return raiz;
                }
            }
        } else {
            if(info < raiz->conteudo)
                raiz->esquerda = removeNo(raiz->esquerda, info);
            else
                raiz->direita = removeNo(raiz->direita, info);
            return raiz;
        }
    }
}

void liberaArv(Tree T) {
    arvT* tree = (arvT*) T;
    free(tree);
}