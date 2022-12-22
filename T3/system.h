#ifndef system_h
#define system_h 
#include "SRBtree.h"
#include "parameters.h"

void operations(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry);
/*
    Cria a árvore e chama as operações do geo e do qry.
*/
void geoPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, SRbTree arvore);
/*
    Realiza todas as operações necessárias para criar o .svg e .dot iniciais.
*/
void qryPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, SRbTree arvore);
/*
    Realiza todas as operações necessárias para criar o .svg, .txt e .dot finais.
*/

#endif