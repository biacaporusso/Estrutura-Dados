#ifndef qry_h
#define qry_h 
#include "arvore.h"

// função que lê o arquivo .qry e chama as funções passadas nele
void leituraQry(FILE *qryFile, Tree arv, FILE *svg, FILE *arqTxt);

// atribui o nível de agressividade v às regiões de ataque
void funcaoNA(Tree arv, FILE* svg, FILE* arqTxt, float v);

// remove todas as figuras contidas na coordenada x, y
void funcaoTP(Node no, FILE* svg, FILE* arqTxt, float x, float y, float* scoreDest);

// faz uma cópia das figuras contidas nas coordenadas x, y e as desloca dx dy, troca as cores de borda e preenchimento dessas cópias
void funcaoTR(Node no, FILE* svg, FILE* arqTxt, float x, float y, float dx, float dy, char id[]);

// 
void funcaoBE(Node no, FILE* svg, FILE* arqTxt, float x, float y, float w, float h, float agress, float* scoreInat);

// funções que verificam se as coordenadas passadas de parâmetro se encontram dentro das respectivas figuras
int rectInside(float x, float y, Item rect);
int circInside(float x, float y, Item circ);
int lineInside(float x, float y, Item line);
int textInside(float x, float y, Item text);
int insideIrradiation(float x, float y, float w, float h, char type,Item item);

#endif