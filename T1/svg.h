#ifndef svg_h
#define svg_h

#include "lista.h"

void createSvg(FILE *svg, List lista);  // cria o svg a partir da lista que contem as figuras
void svgRect(FILE *svg, Cell aux);  // linha de comando de retangulo no svg
void svgCirc(FILE *svg, Cell aux);  // linha de comando de circulo no svg
void svgLine(FILE *svg, Cell aux);  // linha de comando de linha no svg
void svgText(FILE *svg, Cell aux);  // linha de comando de texto no svg

#endif 