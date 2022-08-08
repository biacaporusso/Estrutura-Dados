#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "fila.h"

#define QUEUE_EMPTY INT_MIN

typedef struct queue{
    Item *value;
    int head, tail, num_entries, size;
}fila_circ;


Fila_Circular criaFila(int max_size){
    //Criando nova fila circular
    fila_circ *q = calloc(1, sizeof(fila_circ));

    q->size = max_size;
    q->value = malloc(sizeof(Item) * max_size);    
    q->num_entries = 0;
    q->head = 0;
    q->tail = 0;

    return q;
}

Item getElement(Fila_Circular q, int n) {
    fila_circ *fila = (fila_circ *)q;
    if (n > fila->size) {
        return NULL;
    } 
    return fila->value[n];
}

int getSize(Fila_Circular q) {
    fila_circ *fila = (fila_circ *)q;

    return fila->num_entries;
}

void destroi_fila(Fila_Circular q){
    fila_circ *fila = (fila_circ*) q;

    free(fila->value);
}

void insereFila(Fila_Circular q, Item x){
    fila_circ *fila = (fila_circ*) q;
    //Preencho uma nova celula
    /* if (fila_cheia(fila)){
        printf("Sua fila esta cheia\n");
        return false;
    } */

    fila->value[fila->tail] = x;
    fila->num_entries++;
    fila->tail = (fila->tail + 1) % fila->size;
    //return true;
}

void removeDaFila(Fila_Circular q){
    fila_circ *fila = (fila_circ*) q;
    //fila_circ *result = NULL;

    /* if (fila_vazia(fila)){
        //printf("Sua fila esta vazia\n");
        return QUEUE_EMPTY;
    } */

    //result = fila->value[fila->head];
    fila->head = (fila->head + 1) % fila->size;
    fila->num_entries--;
    //return result;
}

void removeTudoFila(Fila_Circular q) {
    fila_circ *fila = (fila_circ *)q;

    int i=0;
    int j=fila->num_entries;

    while(i < j){
        removeDaFila(fila);
        i++;
    } 

}
