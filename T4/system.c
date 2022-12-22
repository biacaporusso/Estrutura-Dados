#include "libs.h"
#include "system.h"
#include "geo.h"
#include "svg.h"
#include "qry.h"

void operations(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, char* arqVia, int leuQry, int leuVia) {

    // criar árvore
    SRbTree tree = createSRb(0);
    Digraph grafo = geoPart(dirEntrada, arqGeo, arqQry, dirSaida, arqVia, leuQry, tree, leuVia);
    qryPart(dirEntrada, arqGeo, arqQry, dirSaida, leuQry, tree, grafo);
    //liberaArv(tree);

}

Digraph geoPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, char* arqVia, int leuQry, SRbTree arvore, int leuVia) {

    // tratamento do diretorio de entrada geo
    char* diretorioEntradaGeo = NULL;
    diretorioEntradaGeo = (char*)malloc(sizeof(char) * (strlen(dirEntrada) + strlen(arqGeo)+2));
    diretorios(dirEntrada, arqGeo, diretorioEntradaGeo);

    // criando o arquivo geo a partir do diretorio de entrada
    FILE *geoFile;
    geoFile = fopen(diretorioEntradaGeo, "r");
    if(geoFile == NULL) {
        printf("Nao foi possivel abrir o arquivo geo.\n");
    }

    // chamar a função de interpretar o geo
    readingGeo(geoFile, arvore);

    // construindo a via
    Digraph grafo = NULL;
    char* diretorioEntradaVia = NULL;
    if (leuVia == 1) {
        diretorioEntradaVia = (char*)malloc(sizeof(char) * (strlen(dirEntrada) + strlen(arqVia)+2));
        diretorios(dirEntrada, arqVia, diretorioEntradaVia);
        grafo = buildingVias(diretorioEntradaVia);
    } 
    // diretorio de saida do svg inicial (apenas do .geo, antes do .qry)
    char* diretorioSvgInicial = NULL;
    diretorioSvgInicial = calloc(strlen(dirSaida) + strlen(arqGeo) + 20, sizeof(char));
    diretorios(dirSaida, arqGeo, diretorioSvgInicial);
    strtok(diretorioSvgInicial, ".");
    strcat(diretorioSvgInicial, ".svg");

    // criando o arquivo svg inicial 
    FILE *svgInicial = fopen(diretorioSvgInicial, "w");
    if(svgInicial == NULL) {
        printf("\nNao foi possivel abrir o svg inicial.");
    }

    fprintf(svgInicial, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">");
    percursoProfundidade(arvore, createSvg, svgInicial);
    fprintf(svgInicial, "\n</svg>");
    fclose(svgInicial);
    free(diretorioEntradaGeo);
    free(diretorioSvgInicial);
    if (diretorioEntradaVia != NULL)
        free(diretorioEntradaVia);

    return grafo;

}

void qryPart(char* dirEntrada, char* arqGeo, char* arqQry, char* dirSaida, int leuQry, SRbTree arvore, Digraph grafo) {

    if (leuQry != 0) {

        // tratamento do diretorio de entrada qry
        char* diretorioEntradaQry = NULL;
        diretorioEntradaQry = calloc(strlen(dirEntrada) + strlen(arqQry)+20, sizeof(char));
        
        diretorios(dirEntrada, arqQry, diretorioEntradaQry);
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

        // tratamento dos diretorio de saída para o .svg 
        diretorios(dirSaida, arqGeo, diretorioSvgFinal);
        diretorioSvgFinal = strtok(diretorioSvgFinal, ".");
        strcat(diretorioSvgFinal, "-");
        char* nomeArqQry = calloc(strlen(arqQry), sizeof(char));
        nomeArqQry = getNomeQry(arqQry);
        diretorioSvgFinal = strcat(diretorioSvgFinal, nomeArqQry);
        diretorioSvgFinal = strcat(diretorioSvgFinal, ".svg");

        // tratamento dos diretorio de saída para o .txt
        diretorios(dirSaida, arqGeo, diretorioTxtFinal);
        diretorioTxtFinal = strtok(diretorioTxtFinal, ".");
        strcat(diretorioTxtFinal, "-");
        diretorioTxtFinal = strcat(diretorioTxtFinal, nomeArqQry);
        diretorioTxtFinal = strcat(diretorioTxtFinal, ".txt");

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
        readingQry(qryFile, arvore, grafo, svgFinal, arqTxt);
        percursoProfundidade(arvore, createSvg, svgFinal);
        fprintf(svgFinal, "\n</svg>");  // fechando o arquivo svg

        free(diretorioEntradaQry);
        free(diretorioSvgFinal);
        free(diretorioTxtFinal); 
        fclose(qryFile);
        fclose(svgFinal);
        fclose(arqTxt);
        killSRb(arvore);
        freeGraph(grafo);

    }
}
