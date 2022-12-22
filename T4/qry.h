#ifndef qry_h
#define qry_h
#include "libs.h"
#include "SRBtree.h"
#include "digraph.h"

void readingQry(FILE *qryFile, SRbTree arvore, Digraph grafo, FILE *svg, FILE *arqTxt);
/*
    Faz a leitura do arquivo .qry passado de parâmetro
    e chama todas as funções passadas no arquivo.
*/

// ==================================== PRINCIPAIS =========================================
void pnt(char* cep, char* cfill, char* cstrk, SRbTree tree, FILE* txt);
/*
    Modifica as cores de preenchimento e borda da quadra identificada por cep
*/
void oFunc(char* cep, char* face, double num, SRbTree tree, FILE* svg, void* aux);
/*
    Armazena a posição geográfica do endereço cep/face/num
*/
void catac(double x, double y, double w, double h, FILE* arqTxt, FILE* arqSvg, SRbTree tree, Digraph grafo);
/*
    Remove quadras contidas no retângulo x, y, w, h.
*/
void blq(char* nome, char* sentido, double x, double y, double w, double h, Digraph grafo, FILE* txt);
/*
    Bloqueia um fluxo num determinado sentido em todas as arestas que estiverem dentro da região especificada
*/
void rbl(char* nome, Digraph grafo, FILE* txt);
/*
    Desbloqueia as arestas que foram bloqueadas pelo comando blq
*/
void rf(char* cep, char* face, double fator, Digraph grafo, FILE* txt, FILE* svg);
/*
    Faz percurso em profundidade no mapa viário classificando as arestas conforme classificação usual.
*/
void bFunc(double x, double y, double fator, FILE* txt, FILE* svg, Digraph grafo);
/*
    Faz o percurso em largura no grafo, a partir do nó mais próximo da coordenada (x,y), 
    multiplicando a velocidade média pelo fator especificado.
*/
void pFunc(char* cep, char* face, double num, char* cmc, char* cmr, void* aux, SRbTree tree, Digraph grafo);
/*
    Determina o melhor trajeto entre a origem (@o) e o destino especificado pelo endereço cep/face/num.
*/

// ==================================== AUXILIARES =========================================
void buscaCep(void* i, void* aux);
/*
    Auxiliar para encontrar o cep associado ao aux
*/
void buscaRegiaoRetangular(void* i, void* aux);
/*
    Auxiliar para encontrar figuras contidas na região retangular e removê-las
*/
void setNoFloresta(void* aux, Node i);
/*
    Pedida no .h
*/
bool arestaDeArvore(Digraph g, Edge e, int td, int tf, void *extra);
/*
    Relacionada ao percurso em profundidade, faz as ações necessárias para quando temos aresta de árvore (nó branco)
*/
bool arestaDeAvanco(Digraph g, Edge e, int td, int tf, void *extra);
/*
    Relacionada ao percurso em profundidade, faz as ações necessárias para quando temos aresta de avanço (nó cinza)
*/
bool arestaDeRetorno(Digraph g, Edge e, int td, int tf, void *extra);
/*
    Relacionada ao percurso em profundidade, faz as ações necessárias para quando temos aresta de retorno (nó preto)
*/
bool arestaCruzada(Digraph g, Edge e, int td, int tf, void *extra);
/*
    Relacionada ao percurso em profundidade, faz as ações necessárias para quando temos aresta cruzada
*/
bool criaFloresta(Digraph g, void *extra);
/*
    Cria uma floresta a partir do grafo
*/
void setNoFloresta(void* aux, Node i);
/*
    Seta o nó da floresta
*/
Node localizaVerticeMaisProximo(Digraph grafo, double xRef, double yRef);
/*
    Busca o vértice mais próximo às coordenadas xRef e yRef passadas
*/
bool discoverNode(Digraph g, Edge e, int td, int tf, void *extra);
/*
    Relacionada ao percurso em largura, realiza as ações necessárias para esse caso
*/

#endif