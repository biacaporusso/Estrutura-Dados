#ifndef qry_h
#define qry_h 
#include "lista.h"
#include "fila.h"
#include "yxxtree.h"

bool figuraDentro(Info i, double x1, double y1 , double x2, double y2);
void interpretandoQry(FILE *qryFile, YxxTree arvore, FILE *svg, FILE *arqTxt);  // lê o arquivo qry e chama as funções dos queries contidos nele

// QUERIES 
void funcaoINP(Info i, double x, double y, void *aux);
void funcaoRMP(Fila_Circular fila, FILE* arqTxt);
void funcaoPOL(int id, float d, float e, char corb[], char corp[], FILE* svg, FILE* arqTxt, YxxTree arvore, Fila_Circular fila);
void funcaoCLP(Fila_Circular fila, FILE* arqTxt);
void funcaoSEL(void *aux);
void funcaoSELplus(void *aux);
void funcaoDELS(YxxTree arvore, FILE* arqTxt, List selecionados);
void funcaoDPS(YxxTree arvore, void *aux);
void funcaoUPS(YxxTree arvore, void *aux);

#endif
