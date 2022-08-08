#ifndef figuras_h
#define figuras_h

typedef void* Figura;
typedef void* Ponto;

// cria a figura de acordo com seus respectivos parametros, retorna um void* Figura 
Figura criarFig(char tipo[], char id[], double x, double x1, double x2, double y, double y1, double y2, double r, double w, double h, char borda[], char preench[], char textoGeo[], char ancora[]);
char* getTipo(Figura fig);  // retorna o tipo da figura (retangulo = r, circulo = c, linha = l, texto = t)
char* getID(Figura fig);    // retorna o id da figura
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

Ponto criaPonto(double x, double y);    // cria um ponto com as coordenadas x,y passadas, retorna um void* Ponto
float getXponto(Ponto pnt); // retorna o X do ponto
float getYponto(Ponto pnt); // retorna o Y do ponto

void changeX(Figura fig, double novoX);     // altera o valor do X da figura
void changeY(Figura fig, double novoY);     // altera o valor do Y da figura
void changeX1(Figura Fig, double novoX1);   // altera o valor do X1 da linha
void changeY1(Figura Fig, double novoY1);   // altera o valor do Y1 da linha
void changeX2(Figura Fig, double novoX2);   // altera o valor do X2 da linha
void changeY2(Figura Fig, double novoY2);   // altera o valor do Y2 da linha
void changeW(Figura fig, double novoW);     // altera o valor da largura do retângulo
void changeH(Figura fig, double novoH);     // altera o valor da altura do retângulo
void changeBorda(Figura fig, char novaBorda[]); // altera a cor da borda da figura
void changePreench(Figura fig, char novoPreench[]); // altera a cor do preenchimento da figura

#endif 