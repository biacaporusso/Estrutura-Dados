//#include <stdio.h>
#include "paramqry.h"
#include "lista.h"
#include "yxxtree.h"

typedef struct pqry {
    FILE *svgqry;
    FILE *txtqry;
    float x, y, w, h; //sel e sel+
    int id; //dps
    float dx, dy; //dps e ups
    char corp[20], corb[20]; // dps e ups
    int n; //ups
    void* listasel;
    void* arv;
    void* fila;
} paramQry;

void appendListasel(List listaOutrosSelecionados, void *param) {

    paramQry *p = (paramQry*) param;
    Cell no;

    for (no = getInicio(listaOutrosSelecionados); no != NULL ; no = getNext(no)){

      inserirLista(p->listasel, getInfoYxxT(NULL, listaOutrosSelecionados));
    }
}

void* createParamQry() {
    void* p = calloc(1, sizeof(paramQry));
    return p;
}

void setSvg(FILE *svg, void *param) {
    paramQry *p = (paramQry*)param;
    p->svgqry = svg;
}

void setTxt(FILE *txt, void *param) {
    paramQry *p = (paramQry*)param;
    p->txtqry = txt;
}

void setXsel(float x, void *param) {
    paramQry *p = (paramQry*)param;
    p->x = x;
}

void setYsel(float y, void *param) {
    paramQry *p = (paramQry*)param;
    p->y = y;
}

void setWsel(float w, void *param) {
    paramQry *p = (paramQry*)param;
    p->w = w;
}

void setHsel(float h, void *param) {
    paramQry *p = (paramQry*)param;
    p->h = h;
}

void setId(int id, void *param) {
    paramQry *p = (paramQry*)param;
    p->id = id;
}

void setDx(float dx, void *param) {
    paramQry *p = (paramQry*)param;
    p->dx = dx;
}

void setDy(float dy, void *param) {
    paramQry *p = (paramQry*)param;
    p->dy = dy;
}

void setCorpQry(char *corp, void *param) {
    paramQry *p = (paramQry*)param;
    strcpy(p->corp, corp);
}

void setCorbQry(char *corb, void *param) {
    paramQry *p = (paramQry*)param;
    strcpy(p->corb, corb);
}

void setN(int n, void *param) {
    paramQry *p = (paramQry*)param;
    p->n = n;
}

void setListasel(void *listasel, void *param) {
    paramQry *p = (paramQry*)param;
    p->listasel = listasel;
}

void setArv(void *arv, void *param) {
    paramQry *p = (paramQry*)param;
    p->arv = arv;
}

void setFila(void *fila, void* param) {
    paramQry *p = param;
    p->fila = fila;
}

FILE* getSvg(void *param) {
    paramQry *p = (paramQry*)param;
    return p->svgqry;
}

FILE* getTxt(void *param) {
    paramQry *p = (paramQry*)param;
    return p->txtqry;
}

float getXsel(void *param) {
    paramQry *p = (paramQry*)param;
    return p->x;
}

float getYsel(void *param) {
    paramQry *p = (paramQry*)param;
    return p->y;
}

float getWsel(void *param) {
    paramQry *p = (paramQry*)param;
    return p->w;
}

float getHsel(void *param) {
    paramQry *p = (paramQry*)param;
    return p->h;
}

int getId(void *param) {
    paramQry *p = (paramQry*)param;
    return p->id;
}

float getDx(void *param) {
    paramQry *p = (paramQry*)param;
    return p->dx;
}

float getDy(void *param) {
    paramQry *p = (paramQry*)param;
    return p->dy;
}

char* getCorpQry(void *param) {
    paramQry *p = (paramQry*)param;
    return p->corp;
}

char* getCorbQry(void *param) {
    paramQry *p = (paramQry*)param;
    return p->corb;
}

int getN(void *param) {
    paramQry *p = (paramQry*)param;
    return p->n;
}

void* getListasel(void *param) {
    paramQry *p = (paramQry*)param;
    return p->listasel;
}

void* getArv(void *param) {
    paramQry *p = (paramQry*)param;
    return p->arv;
}

void* getFila(void* param) {
    paramQry *p = param;
    return p->fila;
}