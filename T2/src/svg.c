#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "figuras.h"
#include "arvore.h" 

void createSvg(FILE *svg, Tree arvore) {

    //Item aux = getInicio(lista);
    //Tree* arv = (Tree*) arvore;
    Node raiz = getRaiz(arvore);
    percorrerSvg(svg, raiz);

}

void percorrerSvg(FILE* svg, Node raiz) {
    
    if(raiz == NULL) {
        return;
        //return NULL;
    } 
    // else:
    char* tipo;
    //char tipo[5];
    tipo = getTipo(getItem(raiz));

    if(strcmp(tipo, "r") == 0) { 
        svgRect(svg, getItem(raiz));
    } else if(strcmp(tipo, "c") == 0) {
        svgCirc(svg, getItem(raiz));
    } else if(strcmp(tipo, "l") == 0) {
        svgLine(svg, getItem(raiz));
    } else if(strcmp(tipo, "t") == 0) {
        svgText(svg, getItem(raiz));
    }

    percorrerSvg(svg, getEsquerda(raiz));
    percorrerSvg(svg, getMeio(raiz));
    percorrerSvg(svg, getDireita(raiz));


}

void svgRect(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(aux), getY(aux), getW(aux), getH(aux), getCorp(aux), getCorb(aux));
}

void svgRectArea(FILE *svg, double x, double y, double w, double h) {

    fprintf(svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\"/>", x, y, w, h, "transparent", "red");
}

void svgCirc(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(aux), getY(aux), getR(aux), getCorp(aux), getCorb(aux));
}

void svgLine(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", getX1(aux), getY1(aux), getX2(aux), getY2(aux), getCorp(aux));
}

void svgAnchor(FILE *svg, double x, double y) {
    fprintf(svg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%f\" fill=\"%s\" stroke=\"%s\"/>", x, y, 2.5, "red", "red");
}

void svgText(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\">%s</text>", getX(aux), getY(aux), getCorp(aux), getCorb(aux), getText(aux));
}
