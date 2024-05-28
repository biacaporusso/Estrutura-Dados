#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "geo.h"
#include "figuras.h"
#include "lista.h" 

void createSvg(FILE *svg, List lista) {

    //Item aux = getInicio(lista);
    Cell aux = getInicio(lista);

    char* tipo;

    while (aux != NULL) { // percorrer a lista toda

        tipo = getTipo(getItem(aux));

        // puts(tipo);

        if(strcmp(tipo, "r") == 0) { 
            svgRect(svg, getItem(aux));
        } else if(strcmp(tipo, "c") == 0) {
            svgCirc(svg, getItem(aux));
        } else if(strcmp(tipo, "l") == 0) {
            svgLine(svg, getItem(aux));
        } else if(strcmp(tipo, "t") == 0) {
            svgText(svg, getItem(aux));
        }

        aux = getNext(aux);
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
