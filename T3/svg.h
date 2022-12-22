#ifndef svg_h
#define svg_h

#include "SRBtree.h"

void createSvg(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
/*
    Cria o svg a partir da árvore (passada em *aux) que contem as figuras
*/
void svgRect(FILE *svg, Info aux);  // linha de comando de retangulo no svg
void svgCirc(FILE *svg, Info aux);  // linha de comando de circulo no svg
void svgLine(FILE *svg, Info aux);  // linha de comando de linha no svg
void svgText(FILE *svg, Info aux);  // linha de comando de texto no svg

#endif 