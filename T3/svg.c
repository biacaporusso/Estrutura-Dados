#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "geo.h"
#include "figures.h"
#include "SRBtree.h" 

void createSvg(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {

    //No* no = (No*) i;

    FILE *svg = aux;

    switch(getTipo(i)) {
        case 1:
            svgCirc(svg, i);
            break;
        case 2:
            svgRect(svg, i);
            break;
        case 3:
            svgLine(svg, i);
            break;
        case 4:
            svgText(svg, i);
            break;
        default:
            break;
                
    }

}

void svgRect(FILE *svg, Info aux) {

    char contorno[12];
    double e = getEnergia(aux);
    if (e == 0) {
        strcpy(contorno, "#484537");
    } else if (e > 0 && e < 10) {
        strcpy(contorno, "#FFCC00");
    } else if (e >= 10 && e <= 30) {
        strcpy(contorno, "#217821");
    } else {
        strcpy(contorno, "#800066");
    }
    fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"0.8%%\"/>", getX(aux), getY(aux), getW(aux), getH(aux), getCorp(aux), contorno);
}

void svgCirc(FILE *svg, Info aux) {

    fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(aux), getY(aux), getR(aux), getCorp(aux), getCorb(aux));
}

void svgLine(FILE *svg, Info aux) {

    fprintf(svg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", getX1(aux), getY1(aux), getX2(aux), getY2(aux), getCorp(aux));
}

void svgText(FILE *svg, Info aux) {

    fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\"><![CDATA[%s]]></text>", getX(aux), getY(aux), getCorp(aux), getCorb(aux), getText(aux));
}
