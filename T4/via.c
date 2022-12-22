#include "via.h"

typedef struct va {

    char rua[60];
    char ldir[30];
    char lesq[30];
    double cmp;
    double vm;
    char sentido[3];
    char nomeBloqueio[30];

} ViaAresta;

typedef struct vv {

    char id[15];
    double x, y;

} ViaVertice;

InfoEdge criaArestaVia(char* rua, char* ldir, char* lesq, double cmp, double vm) {

    ViaAresta* via = calloc(1, sizeof(ViaAresta));
    strcpy(via->rua, rua);
    strcpy(via->ldir, ldir);
    strcpy(via->lesq, lesq);
    via->cmp = cmp;
    via->vm = vm;

    return via;
}

InfoNode criaVerticeVia(char* id, double x, double y) {

    ViaVertice* via = calloc(1, sizeof(ViaVertice));
    strcpy(via->id, id);
    via->x = x;
    via->y = y;

    return via;
}

double getXvia(InfoNode V) {

    ViaVertice* vertice = (ViaVertice*) V;
    return vertice->x;
}

double getYvia(InfoNode V) {

    ViaVertice* vertice = (ViaVertice*) V;
    return vertice->y;
}

void setSentido(InfoEdge A, char* sentido) {

    ViaAresta* aresta = (ViaAresta*) A;
    strcpy(aresta->sentido, sentido);
}

char* getSentido(InfoEdge A) {
    ViaAresta* aresta = (ViaAresta*) A;
    return aresta->sentido;
}

void setNomeBloqueio(InfoEdge E, char* nome) {
    ViaAresta* aresta = (ViaAresta*) E;
    strcpy(aresta->nomeBloqueio, nome);
}

char* getNomeBloqueio(InfoEdge E) {
    ViaAresta* aresta = (ViaAresta*) E;
    return aresta->nomeBloqueio;
}

char* getNomeRua(InfoEdge E) {
    ViaAresta* aresta = (ViaAresta*) E;
    return aresta->rua;
}

double getVelocidadeAresta(InfoEdge E) {
    ViaAresta* aresta = (ViaAresta*) E;
    return aresta->vm;
}

void setVelocidadeAresta(InfoEdge E, double v) {
    ViaAresta* aresta = (ViaAresta*) E;
    aresta->vm = v;
}

double getComprimento(InfoEdge E) {
    ViaAresta* aresta = (ViaAresta*) E;
    return aresta->cmp;
}