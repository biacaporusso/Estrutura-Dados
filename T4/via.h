#ifndef via_h
#define via_h
#include "libs.h"

InfoEdge criaArestaVia(char* rua, char* ldir, char* lesq, double cmp, double vm);
/*
    Cria uma via a partir dos parâmetros passados
*/
InfoNode criaVerticeVia(char* id, double x, double y);
/*
    Cria um vértice da via através do x e y passados
*/

// ======================================== GETTERS
double getXvia(InfoNode V);     // retorna o X da via V
double getYvia(InfoNode V);     // retorna o Y da via V
char* getSentido(InfoEdge A);   // retorna o sentido da aresta (ns, sn, lo, ol)
char* getNomeBloqueio(InfoEdge E);  // retorna o nome do bloqueio da aresta E
char* getNomeRua(InfoEdge E);       // retorna o nome da rua (contida na informação da aresta E)
double getVelocidadeAresta(InfoEdge E); // retorna a velocidade da aresta
double getComprimento(InfoEdge E);      // retorna o comprimento contido na informação da aresta E

// ======================================== SETTERS
void setSentido(InfoEdge A, char* sentido);     // seta o sentido da via A (ns, sn, lo, ol)
void setNomeBloqueio(InfoEdge E, char* nome);   // seta o nome do bloqueio da via E
void setVelocidadeAresta(InfoEdge E, double v); // seta a velocidade da aresta

#endif