#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "figuras.h"

typedef struct figura {

    char tipo[2], id[40], ancora[2];
    double x, x1, x2, y, y1, y2, r, w, h;
    char corb[25], corp[25], txto[100];
    float protecao, inativacao, destruicao;
} figura;

typedef struct pg {
    double x;
    double y;
} ponto;

Ponto criaPonto(double x, double y) {
    ponto* novoPonto = calloc(1, sizeof(ponto));

    novoPonto->x = x;
    novoPonto->y = y;

    return novoPonto;
}

float getXponto(Ponto Pnt) {

    if (Pnt == NULL) {
        return 0;
    }
    ponto* pt = (ponto*)Pnt;
    return(pt->x);
}

float getYponto(Ponto Pnt) {

    if (Pnt == NULL) {
        return 0;
    }
    ponto* pt = (ponto*)Pnt;
    return(pt->y);
}

Figura criarFig(char tipo[], char id[], double x, double x1, double x2, double y, double y1, double y2, double r, double w, double h, char borda[], char preench[], char textoGeo[], char ancora[]) {

    figura* fig = (figura*)malloc(sizeof(figura));

    if (strcmp(tipo, "c") == 0) {
        fig->protecao = 60;

    }
    else if (strcmp(tipo, "t") == 0) {
        fig->protecao = 5;

    }
    else if (strcmp(tipo, "l") == 0) {
        fig->protecao = 50;

    }
    else if (strcmp(tipo, "r") == 0) {
        fig->protecao = 60;
    }

    sprintf(fig->tipo, "%s", tipo);
    sprintf(fig->id, "%s", id);

    fig->x = x;
    fig->x1 = x1;
    fig->x2 = x2;
    fig->y = y;
    fig->y1 = y1;
    fig->y2 = y2;
    fig->r = r;
    fig->w = w;
    fig->h = h;
    sprintf(fig->corb, "%s", borda);
    sprintf(fig->corp, "%s", preench);
    sprintf(fig->txto, "%s", textoGeo);
    sprintf(fig->ancora, "%s", ancora);

    return(fig);

}

float getProtecao(Figura Fig) {
    figura* fig = (figura*)Fig;
    return(fig->protecao);
}

char* getTipo(Figura Fig) {


    figura* fig = (figura*)Fig;
    return(fig->tipo);
}

char* getID(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->id);
}

double getX(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->x);
}

double getX1(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->x1);
}

double getX2(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->x2);
}

double getY(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->y);

}

double getY1(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->y1);
}

double getY2(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->y2);
}

double getW(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->w);

}

double getH(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->h);

}

double getR(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->r);

}

char* getCorb(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->corb);
}

char* getCorp(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->corp);
}

char* getText(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->txto);
}

char* getAncora(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->ancora);
}

double getcomprimentolinha(Figura Fig) {
    figura* fig = (figura*)Fig;

    if (fig->x1 > fig->x2 && fig->y1 == fig->y2) { // mesmo y e x diferente
        return fig->x1 - fig->x2;
    }    
else if (fig->x1 < fig->x2 && fig->y1 == fig->y2) { // mesmo y e x diferente
        return fig->x2 - fig->x1;
    }
    else if (fig->y1 < fig->y2 && fig->x1 == fig->x2) { // mesmo x e y diferente
        return fig->y2 - fig->y1;
    }
    else if (fig->y1 > fig->y2 && fig->x1 == fig->x2) { // mesmo x e y diferente
        return fig->y1 - fig->y2;
    }
    else {
        double result = sqrt(pow(fig->x2 - fig->x1, 2) + pow(fig->y2 - fig->y1, 2));
        return result;
    }
}

void changeX(Figura Fig, double novoX) {

    figura* fig = (figura*)Fig;
    fig->x = novoX;
}

void changeY(Figura Fig, double novoY) {

    figura* fig = (figura*)Fig;
    fig->y = novoY;
}

void changeX1(Figura Fig, double novoX1) {

    figura* fig = (figura*)Fig;
    fig->x1 = novoX1;
}

void changeY1(Figura Fig, double novoY1) {

    figura* fig = (figura*)Fig;
    fig->y1 = novoY1;
}

void changeX2(Figura Fig, double novoX2) {

    figura* fig = (figura*)Fig;
    fig->x2 = novoX2;
}

void changeY2(Figura Fig, double novoY2) {

    figura* fig = (figura*)Fig;
    fig->y2 = novoY2;
}

void changeProtecao(Figura Fig, float reducao) {
    
    figura* fig = (figura*)Fig;
    fig->protecao = (fig->protecao - reducao);
}

void changeW(Figura Fig, double novoW) {

    figura* fig = (figura*)Fig;
    fig->w = novoW;
}

void changeH(Figura Fig, double novoH) {

    figura* fig = (figura*)Fig;
    fig->h = novoH;
}

void changeBorda(Figura Fig, char novaBorda[]) {

    figura* fig = (figura*)Fig;
    strcpy(fig->corb, novaBorda);
}

float getTextSize(Figura Fig) {
    figura* fig = (figura*)Fig;
    return strlen(fig->txto);
}

void changePreench(Figura Fig, char novoPreench[]) {

    figura* fig = (figura*)Fig;
    strcpy(fig->corp, novoPreench);
}
//void liberaFigura
//free
void remover(Figura Fig) {

    figura* fig = (figura*)Fig;

    fig->x = 999999;
    fig->x1 = 999999;
    fig->x2 = 999999;
    fig->y = 9999999;
    fig->y1 = 999999;
    fig->y2 = 9999999;
    fig->r = 0;
    fig->w = 0;
    fig->h = 0;
    sprintf(fig->corb, "%s", "none");
    sprintf(fig->corp, "%s", "none");
    sprintf(fig->txto, "%s", "none");
    sprintf(fig->ancora, "%s", "none");
}

void setInativacao(Figura Fig, float valor) {

    figura* fig = (figura*)Fig;
    fig->inativacao = valor;

}

void setDestruicao(Figura Fig, float valor) {

    figura* fig = (figura*)Fig;
    //printf("valor recebido = %f\n", valor);
    fig->destruicao = valor;

}

float getInativacao(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->inativacao);
}

float getDestruicao(Figura Fig) {

    figura* fig = (figura*)Fig;
    return(fig->destruicao);
}
