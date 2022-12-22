#include "fila.h"

typedef struct NoFila {
    Node valor;
    struct NoFila* prox;
} NoFila;

typedef struct Queue {
    NoFila* head;
    NoFila* tail;
} Queue;

Fila criaFila() {
    Queue* fila = calloc(1, sizeof(Queue));
    return fila;
}

bool insereFila(Fila q, Node n) {
    // crio uma nova celula
    Queue* fila = q;
    NoFila* novaCelula = calloc(1, sizeof(NoFila));
    if (!novaCelula) {
        return false;
    }
    novaCelula->valor = n;
    novaCelula->prox = NULL;
    // se existe um rabo, ligo esse rabo na nova celula
    if (fila->tail != NULL) {
        fila->tail->prox = novaCelula;
    }
    fila->tail = novaCelula;
    // conferir se o começo da fila ainda faz sentido
    if (!fila->head) {
        fila->head = novaCelula;
    }
    return true;
}

bool isEmpty(Fila q) {  // retorna true se a fila estiver vazia
    Queue* fila = q;
    if (fila->head == NULL) 
        return true;
    else
        return false;
}

Node removeFila(Fila q) {
    // conferir se a fila está ou não vazia
    Queue* fila = q;
    if (!fila->head) {
        return -1;
    }
    // salvo o começo da fila
    NoFila* tmp = fila->head;
    // salvo o valor a ser removido
    Node result = tmp->valor;
    // removo o valor
    fila->head = fila->head->prox;
    if (!fila->head) {
        fila->tail = NULL;
    }
    free(tmp);
    return result;
}