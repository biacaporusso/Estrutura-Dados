#ifndef svg_h
#define svg_h

#include "SRBtree.h"

void createSvg(Info i, void *aux);
/*
    Cria o svg a partir da árvore (passada em *aux) que contem as figuras
*/
void svgRect(FILE *svg, Info aux);  // linha de comando de retangulo no svg
void svgCirc(FILE *svg, Info aux);  // linha de comando de circulo no svg
void svgLine(FILE *svg, Info aux);  // linha de comando de linha no svg
void svgText(FILE *svg, Info aux);  // linha de comando de texto no svg
void svgQuadra(FILE *svg, Info aux);    // linha de comando de quadra (que é um retângulo) no svg

#endif 