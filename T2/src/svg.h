#ifndef svg_h
#define svg_h

#include "arvore.h"

void createSvg(FILE *svg, Tree arvore);  // cria o svg a partir da lista que contem as figuras
void percorrerSvg(FILE* svg, Node N);
void svgRect(FILE *svg, Node aux);  // linha de comando de retangulo no svg
void svgCirc(FILE *svg, Node aux);  // linha de comando de circulo no svg
void svgLine(FILE *svg, Node aux);  // linha de comando de linha no svg
void svgText(FILE *svg, Node aux);  // linha de comando de texto no svg
void svgRectArea(FILE *svg, double x, double y, double w, double h); // linha de comando de área de impacto
void svgAnchor(FILE *svg, double x, double y); // linha de comando de ancora
#endif 