#ifndef figuras_h
#define figuras_h

#include <stdbool.h>

typedef void* Figura;
typedef void* Quadra;

// cria a figura de acordo com seus respectivos parametros, retorna um void* Figura 
Figura criarFig(char tipo[], int id, double x, double x1, double x2, double y, double y1, double y2, double r, double w, double h, char borda[], char preench[], char textoGeo[], char ancora[], char cep[], float espessura);

// ==== GETTERS ====
int getTipo(Figura fig);  // retorna o tipo da figura (retangulo = r, circulo = c, linha = l, texto = t)
int getID(Figura fig);    // retorna o id da figura
double getX(Figura fig);    // retorna o X da figura
double getX1(Figura fig);   // retorna o X1 da linha
double getX2(Figura fig);   // retorna o X2 da linha
double getY(Figura fig);    // retorna o Y da figura
double getY1(Figura fig);   // retorna o Y1 da linha
double getY2(Figura fig);   // retorna o Y2 da linha
double getR(Figura fig);    // retorna o raio do círculo
double getW(Figura fig);    // retorna a largura do retângulo 
double getH(Figura fig);    // retorna a altura do retângulo 
char* getCorb(Figura fig);  // retorna a cor da borda da figura 
char* getCorp(Figura fig);  // retorna a cor do preenchimento da figura 
char* getText(Figura fig);  // retorna o texto 
char* getAncora(Figura Fig);// retorna a âncora do texto
float getEspessura(Figura Fig); // retorna a espessura da borda da figura
char* getCep(Figura Fig); // retorna o cep da figura (quadra)

// ========== SETTERS ==========
void setX(Figura fig, double novoX);     // altera o valor do X da figura
void setY(Figura fig, double novoY);     // altera o valor do Y da figura
void setX1(Figura Fig, double novoX1);   // altera o valor do X1 da linha
void setY1(Figura Fig, double novoY1);   // altera o valor do Y1 da linha
void setX2(Figura Fig, double novoX2);   // altera o valor do X2 da linha
void setY2(Figura Fig, double novoY2);   // altera o valor do Y2 da linha
void setW(Figura fig, double novoW);     // altera o valor da largura do retângulo
void setH(Figura fig, double novoH);     // altera o valor da altura do retângulo
void setBorda(Figura fig, char novaBorda[]); // altera a cor da borda da figura
void setPreench(Figura fig, char novoPreench[]); // altera a cor do preenchimento da figura
void setFillOpacity(Figura fig);        // seta a opacidade da cor de preenchimento da figura
void setStrokeOpacity(Figura fig);      // seta a opacidade da cor de contorno da figura

#endif 