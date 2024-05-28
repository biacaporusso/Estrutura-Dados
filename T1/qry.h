#ifndef qry_h
#define qry_h 
#include "lista.h"
#include "fila.h"

void interpretandoQry(FILE *qryFile, List lista, FILE *svg, FILE *arqTxt);  // lê o arquivo qry e chama as funções dos queries contidos nele

// QUERIES 
void funcaoINP(List lista, FILE* svg, FILE* arqTxt, float id, Fila_Circular fila);
void funcaoRMP(Fila_Circular fila, FILE* arqTxt);
void funcaoPOL(char id[], float d, float e, char corb[], char corp[], FILE* svg, FILE* arqTxt, List lista, Fila_Circular fila);
void funcaoCLP(Fila_Circular fila, FILE* arqTxt);
void funcaoSEL(double x, double y, double w, double h, FILE *svg, FILE *arqTxt,  List lista);
void funcaoSELplus(double x, double y, double w, double h, FILE *svg, FILE *arqTxt, List lista);
void funcaoDELS(double x, double y, double w, double h, FILE *svgFinal, FILE *arqTxt, List lista);
void funcaoDPS(List lista, FILE* svg, FILE* arqTxt, char id[], float dx, float dy, char corb[], char corp[], double x, double y, double w, double h);
void funcaoUPS(char corb[], char corp[], float dx, float dy, int n, List lista, FILE* svg, FILE* arqTxt,double x, double y, double w, double h);

// FUNÇÕES VERIFICADORAS DE FIGURAS DENTRO DO RETÂNGULO DE COORDENADAS X,Y , LARGURA W E ALTURA H
// retornam 0 se estiverem dentro do retângulo ou 1 se estiverem fora do retângulo
int rectInside(double x, double y, double w, double h, Item rect, FILE *svg, FILE* txt);
int circInside(double x, double y, double w, double h, Item circ, FILE *svg, FILE* txt);
int lineInside(double x, double y, double w, double h, Item line, FILE *svg, FILE* txt);
int textInside(double x, double y, double w, double h, Item text, FILE *svg, FILE* txt);

#endif