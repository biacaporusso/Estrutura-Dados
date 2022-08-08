#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "geo.h"
#include "figuras.h"
#include "yxxtree.h" 

void createSvg(Info i, double x, double y, void *aux) {

    //No* no = (No*) i;

    FILE *svg = aux;
    char tipo[3];
    strcpy(tipo, getTipo(i));

    if(strcmp(tipo, "r") == 0) { 
        svgRect(svg, i);
    } else if(strcmp(tipo, "c") == 0) {
        svgCirc(svg, i);
    } else if(strcmp(tipo, "l") == 0) {
        svgLine(svg, i);
    } else if(strcmp(tipo, "t") == 0) {
        svgText(svg, i);
    }
}

void svgRect(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(aux), getY(aux), getW(aux), getH(aux), getCorp(aux), getCorb(aux));
}

void svgCirc(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(aux), getY(aux), getR(aux), getCorp(aux), getCorb(aux));
}

void svgLine(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", getX1(aux), getY1(aux), getX2(aux), getY2(aux), getCorp(aux));
}

void svgText(FILE *svg, Item aux) {

    fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\">%s</text>", getX(aux), getY(aux), getCorp(aux), getCorb(aux), getText(aux));
}
