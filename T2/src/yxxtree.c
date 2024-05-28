#include "yxxtree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "figuras.h"
#include "fila.h"
#include "lista.h"

// ===================================== STRUCTS ==========================================================

// estrutura nó
typedef struct no {
    Info conteudo;
    struct no *esquerda, *meio, *direita;
    bool removido;
    double x, y;
} No;

// estrutura árvore com um ponteiro para um nó
typedef struct {
    No* raiz;
    int tamanho;
    float fd;
    int numRemovidos;
} arvT;

// ================================= CABEÇALHO ===========================================================
void marcaRemovido(YxxTree T, Node N);
void reorganizaArvore(YxxTree T);
void freeTree(Node raiz);

// ================================= FUNÇÕES GET'S =======================================================

Node getRaiz(YxxTree T) {
    arvT* arvore = (arvT*)T;
    return arvore->raiz;
}

Info getItemArv(Node N) {
    No* no = (No*)N;
    return no->conteudo;
}

Node getEsquerda(Node N) {
    No* no = (No*)N;
    return no->esquerda;
}

Node getDireita(Node N) {
    No* no = (No*)N;
    return no->direita;
}

Node getMeio(Node N) {
    No* no = (No*)N;
    return no->meio;
}

Info getInfoYxxT(YxxTree T, Node N) {
    No* no = (No*)N;
    return no->conteudo;
}

int getXarv(Node N) {
    No* no = (No*)N;
    return no->x;
}

int getYarv(Node N) {
    No* no = (No*)N;
    return no->y;
}

// ===================== FUNÇÕES OBRIGATÓRIAS DO .h =====================================================

// bool figuraAtingida (Info i, double x, double y) {

//     if (getX(i) >= x && getX(i) <= x) {
//         if (getY(i) >= y && getY(i) <= y) {
//             return true;
//         } else {
//             return false;
//         }
//     } else {
//         return false;
//     }

// }

/*
void FvisitaNo (Info i, double x, double y, void *aux) {

    // codigo
}
*/

YxxTree newYxxTree(double fd) {
    arvT* arvore;
    arvore = (arvT*)malloc(sizeof(arvT));
    arvore->raiz = NULL;
    arvore->tamanho = 0;
    arvore->fd = fd;

    return (arvore);
}

Node inserir(YxxTree T, Node N, double x, double y, Info i) {
    No* raiz = (No*)N;
    arvT* tree = (arvT*)T;

    if (raiz == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        novo->x = x;
        novo->y = y;
        novo->conteudo = i;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->meio = NULL;
        novo->removido = false;
        tree->tamanho++;
        if (tree->raiz == NULL) {
            tree->raiz = novo;
        }
        return novo;
    } else {
        if (y < getY(raiz->conteudo)) {
            raiz->esquerda = inserir(T, raiz->esquerda, x, y, i);
        } else if (x < getX(raiz->conteudo)) {
            raiz->meio = inserir(T, raiz->meio, x, y, i);
        } else {
            raiz->direita = inserir(T, raiz->direita, x, y, i);
        }
        return raiz;
    }
}

Node insertYxxT(YxxTree T, double x, double y, Info i) {
    arvT* tree = (arvT*)T;
    No* raiz = getRaiz(tree);

    Node noInserido = inserir(tree, raiz, x, y, i);

    return (noInserido);
}

Node buscaNo(Node N, double x, double y, double epsilon) {
    No* no = (No*)N;

    Info info = getItemArv(no);

    if (no == NULL) {
        return NULL;
    } else {
        if (getX(info) == x && getY(info) == y) {
            return no;
        } else {
            if (getX(info) < x) {
                return buscaNo(no->esquerda, x, y, epsilon);
            } else if (getY(info) < y) {
                return buscaNo(no->meio, x, y, epsilon);
            } else {
                return buscaNo(no->direita, x, y, epsilon);
            }
        }
    }
}

Node getNodeYxxT(YxxTree T, double x, double y, double epsilon) {
    arvT* tree = (arvT*)T;
    No* raiz = getRaiz(tree);

    Node noDesejado = buscaNo(raiz, x, y, epsilon);
    return (noDesejado);
}

void reinsere(YxxTree T, Node N) {

    arvT* arvore = (arvT*)T;
    No* raiz = (No*) N;

    if (raiz == NULL) {
        return;
    }
   
    // se nao foi marcado como removido, insere
    if (!raiz->removido) {
      //printf("endereço do nó da arvore (inserido): %p\n", raiz);
        insertYxxT(arvore, raiz->x, raiz->y, raiz->conteudo);
    } 

    reinsere(arvore,raiz->esquerda);
    reinsere(arvore,raiz->meio);
    reinsere(arvore,raiz->direita);

    //if(raiz->removido)
    free(raiz);
}

void reorganizaArvore(YxxTree T) {

    //return;
    arvT* arvore = (arvT*)T;
    No* raizAntiga = getRaiz(arvore);
    arvore->raiz = NULL;
    arvore->tamanho = 0;
    arvore->numRemovidos = 0;

    reinsere(arvore, raizAntiga);

}



void marcaRemovido(YxxTree T, Node N) {

    arvT* tree = (arvT*)T;
    No* no = (No*)N;

    no->removido = true;
    tree->numRemovidos++;

    double fd = (double)((double)tree->numRemovidos / (double)tree->tamanho);
    /* printf("numRemovidos = %d\n", tree->numRemovidos);
    printf("tamanho = %d\n", tree->tamanho);
    printf("fd = %f\n", fd); */

    if (fd >= tree->fd) {
        //printf("\n****\n****\n*****reorganiza arvore\n*****\n****\n");
        reorganizaArvore(tree);
    }
}


void removeNoYxxT(YxxTree T, Node N) {
    arvT* tree = (arvT*)T;
    No* no = (No*)N;

    if (no == NULL) {
        //("Valor nao encontrado!\n");
        return;
    }

    marcaRemovido(tree, no);
}

Info getInfoXyyT(YxxTree t, Node n) {
    No* no = (No*)n;
    return no->conteudo;
}


void getCoordXyyT (YxxTree t, Node n, double *x, double *y){
  No* no = (No*)n;
    *x = no->x;
    *y = no->y;
}

/*
void infosLista(List lista, Node no, double x1, double y1, double x2, double y2) {

    if(no == NULL) {
        return;
    }

    if (FdentroDe(getItemArv(no), x1, y1, x2, y2)) {

        inserirLista(lista, getItemArv(no));
    }

    infosLista(lista, getEsquerda(no), x1, y1, x2, y2);
    infosLista(lista, getMeio(no), x1, y1, x2, y2);
    infosLista(lista, getDireita(no), x1, y1, x2, y2);

}
 */

List getNodesDentroRegiaoYxxTAux(Node no, List lista, double x1, double y1, double x2, double y2) {

    No* node = (No*) no;
    if (node != NULL) {

        //Info figura = getInfoYxxT(NULL, node);
        if(node->x >= x1 && node->x <= x2 && node->y >= y1 && node->y <= y2) {
            inserirLista(lista, node);
        }

    }
    getNodesDentroRegiaoYxxTAux(getEsquerda(node), lista, x1, y1, x2, y2);
    getNodesDentroRegiaoYxxTAux(getMeio(node), lista, x1, y1, x2, y2);
    getNodesDentroRegiaoYxxTAux(getDireita(node), lista, x1, y1, x2, y2);

    return lista;
}

List getNodesDentroRegiaoYxxT(YxxTree t, double x1, double y1, double x2, double y2) {
    arvT* arv = (arvT*)t;
    List lista = criaLista();

    return getNodesDentroRegiaoYxxTAux(getRaiz(arv), lista, x1, y1, x2, y2);
}

void getInfosDentroRegiaoYxxTAux(No* n, List lista, double x1, double y1, double x2, double y2, FdentroDe f) { // ^<===========

    if (n == NULL) {
        return;
    }

    Info figura = getInfoYxxT(NULL, n);
    if (f(figura, x1, y1, x2, y2)) {
        //printf("inserido\n");
        inserirLista(lista, n);

    }
    getInfosDentroRegiaoYxxTAux(getEsquerda(n), lista, x1, y1, x2, y2, f);
    getInfosDentroRegiaoYxxTAux(getMeio(n), lista, x1, y1, x2, y2, f);
    getInfosDentroRegiaoYxxTAux(getDireita(n), lista, x1, y1, x2, y2, f);

}

List getInfosDentroRegiaoYxxT(YxxTree t, double x1, double y1, double x2, double y2, FdentroDe f) {
    arvT* arv = (arvT*)t;
    No* raiz = arv->raiz;
    List lista = criaLista();
    getInfosDentroRegiaoYxxTAux(raiz, lista, x1, y1, x2, y2, f);
    return lista;
}


void visitaLarguraYxxT(YxxTree t, FvisitaNo f, void* aux) {
    arvT* tree = (arvT*)t;
    Fila_Circular fila = criaFila(97);

    // Item info = getItemArv(getRaiz(tree));
    Node no = NULL;

    insereFila(fila, getRaiz(tree));

    while (!fila_vazia(fila)) {
        no = removeDaFila(fila);  // remove primeiro elemento da fila
        if (getEsquerda(no) != NULL) {
            insereFila(fila, getEsquerda(no));
        }
        if (getMeio(no) != NULL) {
            insereFila(fila, getMeio(no));
        }
        if (getDireita(no) != NULL) {
            insereFila(fila, getDireita(no));
        }
        f(getInfoYxxT(t, no), getXarv(no), getYarv(no), aux);
    }
}

void visitaProfundidadeYxxTAux(Node N, FvisitaNo f, void* aux) {

    No* no = (No*) N;
    if (no == NULL) {
        return;
    }

    // se o no não estiver marcado como removido
    if(!no->removido) {
        f(no->conteudo, no->x, no->y, aux);
    } 

    //f(getInfoYxxT(NULL, no), 0, 0, aux);
    //f(no, 0, 0, aux);
    visitaProfundidadeYxxTAux(getEsquerda(no), f, aux);
    visitaProfundidadeYxxTAux(getMeio(no), f, aux);
    visitaProfundidadeYxxTAux(getDireita(no), f, aux);
}

void visitaProfundidadeYxxT(YxxTree t, FvisitaNo f, void* aux) {
    visitaProfundidadeYxxTAux(getRaiz(t), f, aux);
}


void freeYxxTree(YxxTree t) {
    freeTree(getRaiz(t));
    free(t);
}

void reportaAux(Node N, double x, double y, void *aux) {

  FILE *txt = (FILE *)aux;

    No* no = (No*) N;
    Info info = getInfoYxxT(NULL, no);

    if (no->removido) {
      fprintf(txt, "[---]x = %f, y = %f  REMOVIDA\n",no->x,no->y);
    } else {
        if(strcmp(getTipo(info), "l") == 0)
            fprintf(txt, "[id: %d] tipo: linha x1 = %f, y1 = %f, x2 = %f, y2 = %f, cor = %s\n", getID(info), getX1(info), getY1(info), getX2(info), getY2(info), getCorp(info));
        else
            fprintf(txt, "[id: %d] tipo: %s x = %f, y = %f, cor = %s\n", getID(info), getTipo(info), getX(info), getY(info), getCorp(info));
    }

}

void visitaProfundidadeYxxTAux2(Node N, FvisitaNo f, void* aux) {

    No* no = (No*) N;
    if (!no) {
        return;
    }

    f(no, 0, 0, aux);
    visitaProfundidadeYxxTAux2(getEsquerda(no), f, aux);
    visitaProfundidadeYxxTAux2(getMeio(no), f, aux);
    visitaProfundidadeYxxTAux2(getDireita(no), f, aux);
}

void visitaProfundidadeYxxT2(YxxTree t, FvisitaNo f, void* aux) {
    visitaProfundidadeYxxTAux2(getRaiz(t), f, aux);
}


void reportarArvore(YxxTree T, FILE* txt) {

    arvT* tree = (arvT*)T;
    fprintf(txt, "\n ========== RELATORIO ARVORE ==========\n");
    fprintf(txt, "numero de nos: %d\n", tree->tamanho);
    fprintf(txt, "numero de nos removidos: %d\n", tree->numRemovidos);
    fprintf(txt, "fator de degradacao: %lf\n", tree->fd); // esse fd ta errado, tem q ser o fd final

    visitaProfundidadeYxxT2(tree, reportaAux, txt);

}

void freeTree(Node raiz) {

    //arvT* tree = (arvT*)T;
    No* no = (No*) raiz;

    //reportarArvore(t, f);

    if (no == NULL) {
        return;
    }

    if (no->conteudo != NULL) {
        free(no->conteudo);
    }

    freeTree(no->esquerda);
    freeTree(no->meio);
    freeTree(no->direita);

    if (no != NULL) {
        free(no);
    }
}

void dumpTree(YxxTree t, FILE* f) {

    //printf("dump tree\n");
    reportarArvore(t, f);
    //freeTree(t);
}
