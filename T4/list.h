#ifndef lista_h
#define lista_h
#include "libs.h"
#include "digraph.h" 

List criaLista();                       // cria uma lista vazia  
Edge insertAresta(List vertice, InfoEdge info, Node from, Node to); // insere uma aresta na lista
void RemoveElemento(List L, Edge C);    // remove a célula passada de parâmetro 
void liberaLista(List lista);           // percorre toda a lista e libera todas as células e, ao fim, a lista

// ============================== GETTERS ===========================================

Edge getInicio(List L);                 // retorna a primeira célula da lista
Edge getNext(Edge C);                   // retorna a próxima celula da célula passada de parâmetro
Edge getPrevious(Edge C);               // retorna a célula anterior à célula passada de parâmetro
Edge getLast(List L);                   // retorna a última célula da lista
InfoEdge getItem(Edge C);               // retorna o item contido na célula passada de parâmetro
char* getNomeVert(List vertice);        // retorna o nome do vertice
InfoNode getInfoVert(List vertice);     // retorna a informação associada ao vértice
Node getArestaTo(Edge E);               // retorna a posição da aresta->to
Node getArestaFrom(Edge E);             // retorna a posição da aresta->from
bool getStatusAresta(Edge E);           // retorna true se a aresta está ativada, false se está desativada
char getCorVertice(List L);             // retorna a cor do vértice
int getTempoDescoberta(List L);         // retorna o tempo de descoberta da lista
int getTempoFinalizacao(List L);        // retorna o tempo de finalização da lista
int getDistancia(List L);               // retorna a distância da lista


// ============================== SETTERS ===========================================

void setNomeVert(List vertice, char* nome);     // seta o nome do vértice
void setInfoVert(List vertice, InfoNode info);  // seta a informação contida no vértice
void setInfoAresta(Edge A, InfoEdge I);         // seta a informação contida na aresta
Edge searchEdge(List L, Node from, Node to);    // busca na lista a aresta que contém o vértice de origem "from" e o vértice de destino "to"
void setArestaDesativada(Edge E);               // seta a aresta como desativada
void setArestaAtivada(Edge E);                  // seta a aresta como ativada
void setCorVertice(List L, char cor);           // seta a cor do vértice
void setTempoDescoberta(List L, int t);         // seta o tempo de descoberta da lista
void setTempoFinalizacao(List L, int t);        // seta o tempo de finalização da lista
void setDistancia(List L, int d) ;              // seta a distância da lista


#endif