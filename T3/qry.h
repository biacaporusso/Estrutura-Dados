#ifndef qry_h
#define qry_h
#include <stdio.h>
#include <stdbool.h>
#include "SRBtree.h"

void readingQry(FILE *qryFile, SRbTree arvore, FILE *svg, FILE *arqTxt);
/*
    Faz a leitura do arquivo .qry passado de parâmetro
    e chama todas as funções passadas no arquivo.
*/

void Efunc(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);
/*
    Realiza todas as operações da consulta "e".
*/

void MVfunc(SRbTree tree, double dx, double dy, Info fig, FILE* arqTxt);
/*
    Realiza todas as operações da consulta "mv".
*/

void LRfunc(SRbTree tree, double d, double w, double h, void* aux, FILE* arqTxt);
/*
    Realiza todas as operações da consulta "lr".
*/

void Dfunc(SRbTree tree, double d, void* aux);
/*
    Realiza todas as operações da consulta "d".
*/

void MCfunc (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
/*
    Realiza todas as operações da consulta "mc".
*/

void getNau(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);
/*
    Procura a nau que contem o id "i" e seta o *aux com a figura dela.
*/

void LRaux (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
/*
    Função auxiliar para a LRfunc.
*/

void Daux (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux);
/*
    Função auxiliar para a Dfunc.
*/

bool figuraDentro(Info i, void* aux);
/*
    Retorna true ou false se a figura "i" estiver contida na região do *aux ou não.
*/

bool pontoDentro(Info i, void* aux);
/*
    Retorna true ou false se o ponto "i" estiver contida na região do *aux ou não.
*/

bool circuloDentro(Info i, void* aux);
/*
    Retorna true ou false se o círculo "i" estiver contida na região do *aux ou não.
*/

void printResultados (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux);
/*
    Printa no .txt final todos os resultados obtidos com as consultas.
*/

#endif