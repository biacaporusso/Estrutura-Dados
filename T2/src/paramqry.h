#ifndef paramqry_h
#define paramqry_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void* createParamQry();

void appendListasel(List listaOutrosSelecionados, void *param);

void setSvg(FILE *svg, void *param);
void setTxt(FILE *txt, void *param);
void setXsel(float x, void *param);
void setYsel(float y, void *param);
void setWsel(float w, void *param);
void setHsel(float h, void *param);
void setId(int id, void *param);
void setDx(float dx, void *param);
void setDy(float dy, void *param);
void setCorpQry(char *corp, void *param);
void setCorbQry(char *corb, void *param);
void setN(int n, void *param);
void setListasel(void *listasel, void *param);
void setArv(void *arv, void *param);
void setFila(void *fila, void *param);

FILE* getSvg(void *param);
FILE* getTxt(void *param);
float getXsel(void *param);
float getYsel(void *param);
float getWsel(void *param);
float getHsel(void *param);
int getId(void *param);
float getDx(void *param);
float getDy(void *param);
char* getCorpQry(void *param);
char* getCorbQry(void *param);
int getN(void *param);
void* getListasel(void *param);
void* getArv(void *param);
void* getFila(void *param);

#endif