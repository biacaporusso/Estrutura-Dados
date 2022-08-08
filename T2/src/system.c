#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system.h"
#include "arvore.h"
#include "geo.h"
#include "parametros.h"
#include "svg.h"
#include "qry.h"

void operacoes(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry) {

    // criar árvore
    Tree arvore = criaArvore();
    geoPart(dirEntrada, arqGeo, arqQry, dirSaida, leuQry, arvore);
    qryPart(dirEntrada, arqGeo, arqQry, dirSaida, leuQry, arvore);
    liberaArv(arvore);

}

void geoPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, Tree arvore) {

    // tratamento do diretorio de entrada geo
    char* diretorioEntradaGeo = NULL;
    diretorioEntradaGeo = (char*)malloc(sizeof(char) * (strlen(dirEntrada) + strlen(arqGeo)+2));
    diretorios(dirEntrada, arqGeo, diretorioEntradaGeo);
    printf("diretorioEntradaGeo: %s\n", diretorioEntradaGeo);

    // criando o arquivo geo a partir do diretorio de entrada
    FILE *geoFile;
    geoFile = fopen(diretorioEntradaGeo, "r");
    if(geoFile == NULL) {
        printf("Nao foi possivel abrir o arquivo geo.\n");
    }

    // chamar a função de interpretar o geo
    interpretandoGeo(geoFile, arvore);

    // diretorio de saida do svg inicial (apenas do .geo, antes do .qry)
    char* diretorioSvgInicial = NULL;
    diretorioSvgInicial = calloc(strlen(dirSaida) + strlen(arqGeo) + 20, sizeof(char));
    diretorios(dirSaida, arqGeo, diretorioSvgInicial);
    strtok(diretorioSvgInicial, ".");
    strcat(diretorioSvgInicial, ".svg");
    printf("diretorioSvgInicial: %s\n", diretorioSvgInicial);

    // criando o arquivo svg inicial 
    FILE *svgInicial = fopen(diretorioSvgInicial, "w");
    if(svgInicial == NULL) {
        printf("\nNao foi possivel abrir o svg inicial.");
    }

    fprintf(svgInicial, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">");
    createSvg(svgInicial, arvore);  // insere as figuras que estão na lista no arquivo svg inicial
    fprintf(svgInicial, "\n</svg>");
    fclose(svgInicial);

}

void qryPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, Tree arvore) {

    if (leuQry != 0) {

        // tratamento do diretorio de entrada qry
        char* diretorioEntradaQry = NULL;
        diretorioEntradaQry = calloc(strlen(dirEntrada) + strlen(arqQry)+20, sizeof(char));
        
        diretorios(dirEntrada, arqQry, diretorioEntradaQry);
        printf("diretorioEntradaQry: %s\n", diretorioEntradaQry);
        // criando o arquivo qry a partir do diretorio de entrada
        FILE *qryFile;
        qryFile = fopen(diretorioEntradaQry, "r");
        if(qryFile == NULL) {
            printf("\nNao foi possivel abrir o arquivo qry.");
        }
        
        // criando o arquivo svg e txt final (depois de sofrer as consultas do qry)
        char* diretorioSvgFinal = NULL;
        diretorioSvgFinal = calloc(strlen(dirSaida) + strlen(arqGeo) + strlen(arqQry), sizeof(char));
        char* diretorioTxtFinal = NULL;
        diretorioTxtFinal = calloc(strlen(dirSaida) + strlen(arqGeo) + strlen(arqQry) + 20, sizeof(char));

        // tratamento dos diretorios de saída para o .svg e .txt
        leuQry++;
        diretorios(dirSaida, arqGeo, diretorioSvgFinal);
        concatenarSvg(diretorioSvgFinal, arqQry, leuQry);
        printf("diretorioSvgFinal: %s\n", diretorioSvgFinal);

        concatenarTxt(diretorioTxtFinal, diretorioSvgFinal);
        printf("diretorioTxtFinal: %s\n", diretorioTxtFinal);

        // criando o arquivo .svg final , ou seja, após o qry
        FILE *svgFinal = fopen(diretorioSvgFinal, "w");
        if(svgFinal == NULL) {
            printf("\nNao foi possivel abrir o arquivo svg final.");
        }
        FILE *arqTxt = fopen(diretorioTxtFinal, "w");
        if(arqTxt == NULL) {
            printf("\nNao foi possivel criar o arquivo txt final.");
        }

        fprintf(svgFinal, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");   // inicializando o arquivo svg
        leituraQry(qryFile, arvore, svgFinal, arqTxt);
        createSvg(svgFinal, arvore); // cria o svg final a partir da lista que foi alterada conforme os queries
        fprintf(svgFinal, "\n</svg>");  // fechando o arquivo svg

        free(diretorioEntradaQry);
        free(diretorioSvgFinal);
        free(diretorioTxtFinal);
        fclose(qryFile);
        fclose(svgFinal);
        fclose(arqTxt);

    }
}