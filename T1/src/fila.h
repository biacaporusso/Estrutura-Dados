#ifndef FILA_CIRC_H
#define FILA_CIRC_H

typedef void* Fila_Circular;
typedef void* Item;

Fila_Circular criaFila(int max_size);   // cria uma fila vazia

void destroi_fila(Fila_Circular q);     // libera elementos para evitar vazamentos de memória

void insereFila(Fila_Circular q, Item x);   //adiciona elementos no rabo fila circular

void removeDaFila(Fila_Circular q); // remove o primeiro elemento da fila

void removeTudoFila(Fila_Circular q); // percorre a fila inteira e remove todas as informações contidas

Item getElement(Fila_Circular q, int n);    // retorna o elemento da fila indicado pela posição n

int getSize(Fila_Circular q);   // retorna o tamanho da fila

#endif