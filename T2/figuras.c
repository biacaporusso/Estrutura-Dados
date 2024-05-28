#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "figuras.h"
#include "lista.h"

typedef struct figura{

    char tipo[2], ancora[2]; //id[40];
    int id;
    double x, x1, x2, y, y1, y2, r, w, h;
    char corb[25], corp[25], txto[100];
    bool selecionada;

} figura;

typedef struct pg {
    double x;
    double y;
} ponto;

Ponto criaPonto(double x, double y) {
    ponto *novoPonto = calloc(1, sizeof(ponto));

    novoPonto->x = x;
    novoPonto->y = y;

    return novoPonto;
}

float getXponto(Ponto Pnt) {

    if (Pnt == NULL) {
        return 0;
    }
    ponto* pt = (ponto*) Pnt;
    return(pt->x); 
}

float getYponto(Ponto Pnt) {

    if (Pnt == NULL) {
        return 0;
    }
    ponto* pt = (ponto*) Pnt;
    return(pt->y); 
}

Figura criarFig(char tipo[], int id, double x, double x1, double x2, double y, double y1, double y2, double r, double w, double h, char borda[], char preench[], char textoGeo[], char ancora[]) {

    figura* fig = (figura*)malloc(sizeof(figura));

    strcpy(fig->tipo, tipo);
    fig->id = id;
    fig->x = x;
    fig->x1 = x1;
    fig->x2 = x2;
    fig->y = y;
    fig->y1 = y1;
    fig->y2 = y2;
    fig->r = r;
    fig->w = w;
    fig->h = h;
    fig->selecionada = false;

    if(!borda) {
        strcpy(fig->corb, "");
    } else {
        strcpy(fig->corb, borda);
    }

    if(!preench) {
        strcpy(fig->corp, "");
    } else {
        strcpy(fig->corp, preench);
    }

    if(!textoGeo) {
        strcpy(fig->txto, "");
    } else {
        strcpy(fig->txto, textoGeo);
    }

    if(!ancora) {
        strcpy(fig->ancora, "");
    } else {
        strcpy(fig->ancora, ancora);
    }

    return(fig);

}


char* getTipo(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->tipo);
}

int getID(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->id);
}

double getX(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->x); 
}

double getX1(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->x1); 
}

double getX2(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->x2); 
}

double getY(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->y);

}

double getY1(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->y1); 
}

double getY2(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->y2); 
}

double getW(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->w);
    
}

double getH(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->h);
    
}

double getR(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->r);
    
}

char* getCorb(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->corb);
}

char* getCorp(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->corp);
}

char* getText(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->txto);
}

char* getAncora(Figura Fig) {

    figura* fig = (figura*) Fig;
    return(fig->ancora);
}

void changeX(Figura Fig, double novoX) {

    figura* fig = (figura*) Fig;
    fig->x = novoX;
}

void changeY(Figura Fig, double novoY) {

    figura* fig = (figura*) Fig;
    fig->y = novoY;
}

void changeX1(Figura Fig, double novoX1) {

    figura* fig = (figura*) Fig;
    fig->x1 = novoX1;
}

void changeY1(Figura Fig, double novoY1) {

    figura* fig = (figura*) Fig;
    fig->y1 = novoY1;
}

void changeX2(Figura Fig, double novoX2) {

    figura* fig = (figura*) Fig;
    fig->x2 = novoX2;
}

void changeY2(Figura Fig, double novoY2) {

    figura* fig = (figura*) Fig;
    fig->y2 = novoY2;
}

void changeW(Figura Fig, double novoW) {

    figura* fig = (figura*) Fig;
    fig->w = novoW;
}

void changeH(Figura Fig, double novoH) {

    figura* fig = (figura*) Fig;
    fig->h = novoH;
}

void changeBorda(Figura Fig, char novaBorda[]) {

    figura* fig = (figura*) Fig;
    strcpy(fig->corb, novaBorda);
}

void changePreench(Figura Fig, char novoPreench[]) {

    figura* fig = (figura*) Fig;
    strcpy(fig->corp, novoPreench);
}
//void liberaFigura
//free

void setSelecionada(Figura Fig) {

    figura* fig = (figura*) Fig;
    fig->selecionada = true;
}

bool getSelecionada(Figura Fig) {
    
    figura* fig = (figura*) Fig;
    return fig->selecionada;
}