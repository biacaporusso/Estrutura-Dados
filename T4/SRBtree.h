#ifndef _SRB_Tree_H
#define _SRB_Tree_H
#include "libs.h"
#include "list.h"

typedef void (*FvisitaNo) (void* i, void *aux);
/*
 * Processa a informacao i associada a um no' da arvore, cuja ancora
 * e' o ponto (x,y), bounding box (mbbX1,mbbY1) -- (mbbX2,mbbY2). 
 * O parametro aux aponta para conjunto de dados 
 * (provavelmente um registro) que sao compartilhados entre as 
 * sucessivas invocacoes a esta funcao.
 */

SRbTree createSRb(double epsilon);
/*
  Retorna uma ´arvore vazia, com precisao epsilon.
  Retorna NULL caso nao tenha conseguido criar a arvore.
 */

void* insertSRb(SRbTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* info);
/*
  Insere a informacao info na arvore t, associada a coordenada (x,y), sendo delimitada pelo retangulo definido
  pela diagonal (mbbX1,mbbY1) -- (mbbX2,mbbY2).
  Retorna o no´ onde foi inserida a informacao; NULL, caso ja exista informacao com a mesma chave (veja acima)
  inserida.
 */
void setInfoSrb(SRbTree T, void *n, void *i);

void* getNodeSRb(SRbTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2);

void* getInfoSRb(SRbTree t, void* n);
/*
  Retorna a informacao associada ao no´ n, sua ancora (xa,ya) e o retangulo envolvente (mbbX1,mbbY1) -- (mbbX2,mbbY2). 
  Este no´ deve ser um no´ valido (veja acima).
 */

// void* getInfoSRb(SRbTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2);
/*
  Retorna o no da arvore associado a ancora (xa,ya) e o retangulo envolvente; NULL, se tal ancora nao existir.
 */

void* removeSRb(SRbTree t,double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2);
/*
  Remove o no' da arvore cuja chave e´ a coordenada (xa,ya). Qualquer no' da arvore retornado por operacoes anteriores
  deve ser considerado invalido.
  Retorna a informacao que estava associada a tal no' (ou NULL, se nao encontrado), bem como o seu retangulo envolvente.
 */

/*
  As proximas operacoes percorrem a arvore em largura/profundidade/simetrico.
  Invoca a funcao fVisita (veja descricao acima) em cada no´ visitado
 */

void percursoLargura(SRbTree t, FvisitaNo fVisita, void *aux);

void percursoSimetrico(SRbTree t, FvisitaNo fVisita, void *aux);

void percursoProfundidade(SRbTree t, FvisitaNo fVisita, void *aux);

/*
  Desaloca todos os recursos usados pela arvore t.
 */
void killSRb(SRbTree t);

#endif