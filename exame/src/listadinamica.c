#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

typedef struct celula {
    Item it;
    struct celula *ant;
    struct celula *prox;
} Celula;

typedef struct {
    int tamanho;
    Celula *prim, *ult;
} Lista;

List criaLista() {

    Lista *lista;
    lista = (Lista*) malloc(sizeof(Lista));
    lista->prim = NULL;
    lista->ult = NULL;
    lista->tamanho = 0;

    return(lista);
}

void inserirLista(List L, Item info) {

    Lista* lista = (Lista*) L;
    Celula* novoEle = (Celula*) malloc(sizeof(Celula));

    novoEle->it = info;
    novoEle->prox = NULL;

    if(lista->tamanho == 0) {

        novoEle->ant = NULL;
        lista->ult = novoEle;
        lista->prim = novoEle;

    } else {

        (lista->ult)->prox = novoEle;
        novoEle->ant = lista->ult;
        lista->ult = novoEle;
    }
    lista->tamanho++;
}

void RemoveElemento(List L, Cell C) {

    Lista* lista = (Lista*) L;
    //Celula* auxAnt = malloc(sizeof(Celula));
    Celula* celula = (Celula*) C;
    //auxAnt = celula->ant;
    Celula* auxAnt = celula->ant;

    if (celula == NULL) {
        return;
    }

    if (celula == lista->prim && celula == lista->ult) {
        lista->prim = NULL;
        lista->ult = NULL;

    } else if (celula == lista->prim) {
        lista->prim = celula->prox;
        celula->prox->ant = NULL;

    } else if (celula == lista->ult) {
        lista->ult = auxAnt;
        celula->ant->prox = NULL;

    } else {
        celula->ant->prox = celula->prox;
        celula->prox->ant = celula->ant;

    }

    free(celula);
    lista->tamanho--;
}

Cell getInicio(List L) {
    Lista* lista = (Lista*) L;
    return lista->prim;
}

Cell getNext(Cell C) {
    Celula* celula = (Celula*) C;
    return celula->prox;
}

Cell getPrevious(Cell C) {
    Celula* celula = (Celula*) C; 
    return celula->ant;
}

Cell getLast2(List L) {
    Lista* lista = (Lista*) L;
    return lista->ult;
}

Cell getLast(List L) {
    Lista* lista = (Lista*) L;
    return lista->ult;
}

Item getItem(Cell C) {
    Celula* celula = (Celula*) C;
    return celula->it;
}

void liberaLista(List lista) {
    Cell celula = getInicio(lista);
    Cell celulaRemovida;

    // percorrendo a lista e dando free em todas as células
    while (celula != NULL) {

        celulaRemovida = celula;
        celula = getNext(celula);
        free(celulaRemovida);
    }
    // depois de ter liberado todas as células, libera a lista
    free(lista);
}
