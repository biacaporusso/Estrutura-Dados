#ifndef system_h
#define system_h 
#include "arvore.h"
#include "qry.h"

void operacoes(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry);
void geoPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, Tree arvore);
void qryPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, Tree arvore);

#endif