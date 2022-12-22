#ifndef system_h
#define system_h 
#include "SRBtree.h"
#include "parameters.h"

void operations(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, char* arqVia, int leuQry, int leuVia);
/*
    Cria a árvore e chama as operações do geo e do qry.
*/
Digraph geoPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, char* arqVia, int leuQry, SRbTree arvore, int leuVia);
/*
    Realiza todas as operações necessárias para criar o .svg e .dot iniciais.
*/
void qryPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, SRbTree arvore, Digraph grafo);
/*
    Realiza todas as operações necessárias para criar o .svg, .txt e .dot finais.
*/

#endif