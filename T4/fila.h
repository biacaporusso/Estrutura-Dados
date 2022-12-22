#ifndef fila_h
#define fila_h
#include "libs.h"

typedef void* Fila;

Fila criaFila();    // cria uma fila vazia
bool insereFila(Fila q, Node n) ;   // insere um elemento no fim da fila
bool isEmpty(Fila q) ;  // retorna true se a fila está vazia; false se a fila não está vazia
Node removeFila(Fila q); // remove o primeiro nó da fila

#endif
