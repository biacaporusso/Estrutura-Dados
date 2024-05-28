#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parametros.h"
#include "lista.h"
#include "geo.h"
#include "svg.h"
#include "figuras.h"
#include "qry.h"
#include "fila.h"
#include "yxxtree.h"

int main(int argc, char* argv[]) {

    int i;
    int leuQry = 0;

    char* diretorioEnt = NULL;
    char* nomeGeo = NULL;
    char* nomeQry = NULL;
    char* diretorioOut = NULL;
    float fatorDegradacao = 0.5;

    // ------------------------ LEITURA DOS PARÂMETROS PASSADOS NO TERMINAL -----------------------------------
    i=0;
    while(i<argc) {

        if(strcmp("-e", argv[i]) == 0) { // diretorio de entrada (opcional)

            ++i; // a proxima string vai ser o caminho para o diretorio da base de entrada
            diretorioEnt = (char*)malloc((strlen(argv[i])+5)*sizeof(char));
            strcpy(diretorioEnt, argv[i]);

        } else if(strcmp("-f", argv[i]) == 0) { // arquivo geo (obrigatorio)

            ++i;
            nomeGeo = (char*)malloc(sizeof(char) * (strlen(argv[i])+5));
            strcpy(nomeGeo, argv[i]);

        } else if(strcmp("-q", argv[i]) == 0) { // arquivo qry (opcional)

            ++i;
            nomeQry = (char*)malloc(sizeof(char) * (strlen(argv[i])+5));
            strcpy(nomeQry, argv[i]);
            leuQry++;

        } else if(strcmp("-o", argv[i]) == 0) { // diretorio saida (obrigatorio)

            ++i;
            diretorioOut = (char*)malloc((strlen(argv[i])+5)*sizeof(char));
            strcpy(diretorioOut, argv[i]);

        } else if(strcmp("-fd", argv[i]) == 0) { // diretorio saida (obrigatorio)

            ++i;
            fatorDegradacao = atof(argv[i]);

        }
        i++;
    }

    //======================================== GEO =========================================================

    // tratamento do diretorio de entrada geo
    char* diretorioEntradaGeo = NULL;
    diretorioEntradaGeo = (char*)malloc(sizeof(char) * (strlen(diretorioEnt) + strlen(nomeGeo)+2));
    diretorios(diretorioEnt, nomeGeo, diretorioEntradaGeo);
    printf("\ndiretorioEntradaGeo: %s\n", diretorioEntradaGeo);

    // criando o arquivo geo a partir do diretorio de entrada
    FILE *geoFile;
    geoFile = fopen(diretorioEntradaGeo, "r");
    if(geoFile == NULL) {
        printf("\nNao foi possivel abrir o arquivo geo."); return -1;
    }
    
    YxxTree arvore;
    arvore = newYxxTree(fatorDegradacao);
    interpretandoGeo(geoFile, arvore);   // lê o arquivo geo, cria as figuras passadas e as insere na arvore
    
    // diretorio de saida do svg inicial (apenas do .geo, antes do .qry)
    char* diretorioSvgInicial = NULL;
    diretorioSvgInicial = calloc(strlen(diretorioOut) + strlen(nomeGeo) + 20, sizeof(char));
    diretorios(diretorioOut, nomeGeo, diretorioSvgInicial);
    diretorioSvgInicial = strtok(diretorioSvgInicial, ".");
    diretorioSvgInicial = strcat(diretorioSvgInicial, ".svg");
    printf("diretorioSvgInicial: %s\n", diretorioSvgInicial);

    // criando o arquivo svg inicial 
    FILE *svgInicial = fopen(diretorioSvgInicial, "w+");
    if(svgInicial == NULL) {
        printf("\nNao foi possivel abrir o svg inicial.");
    }

    fprintf(svgInicial, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">");
    visitaProfundidadeYxxT(arvore, createSvg, svgInicial);
    fprintf(svgInicial, "\n</svg>");


    //========================================== QRY ===================================================

    if (leuQry != 0) {
        // tratamento do diretorio de entrada qry
        char* diretorioEntradaQry = NULL;
        diretorioEntradaQry = calloc(strlen(diretorioEnt) + strlen(nomeQry)+20, sizeof(char));
        
        diretorios(diretorioEnt, nomeQry, diretorioEntradaQry);
        printf("diretorioEntradaQry: %s\n", diretorioEntradaQry);
        // criando o arquivo qry a partir do diretorio de entrada
        FILE *qryFile;
        qryFile = fopen(diretorioEntradaQry, "r");
        if(qryFile == NULL) {
	  printf("\nNao foi possivel abrir o arquivo qry."); return -1;
        }
        
        // criando o arquivo svg e txt final (depois de sofrer as consultas do qry)
        char* diretorioSvgFinal = NULL;
        diretorioSvgFinal = calloc(strlen(diretorioOut) + strlen(nomeGeo) + strlen(nomeQry), sizeof(char));
        char* diretorioTxtFinal = NULL;
        diretorioTxtFinal = calloc(strlen(diretorioOut) + strlen(nomeGeo) + strlen(nomeQry) + 20, sizeof(char));

        // tratamento dos diretorio de saída para o .svg 
        diretorios(diretorioOut, nomeGeo, diretorioSvgFinal);
        diretorioSvgFinal = strtok(diretorioSvgFinal, ".");
        strcat(diretorioSvgFinal, "-");
        char* nomeArqQry = calloc(strlen(nomeQry), sizeof(char));
        nomeArqQry = getNomeQry(nomeQry);
        diretorioSvgFinal = strcat(diretorioSvgFinal, nomeArqQry);
        diretorioSvgFinal = strcat(diretorioSvgFinal, ".svg");

        // tratamento dos diretorio de saída para o .txt
        diretorios(diretorioOut, nomeGeo, diretorioTxtFinal);
        diretorioTxtFinal = strtok(diretorioTxtFinal, ".");
        strcat(diretorioTxtFinal, "-");
        diretorioTxtFinal = strcat(diretorioTxtFinal, nomeArqQry);
        diretorioTxtFinal = strcat(diretorioTxtFinal, ".txt");

        printf("diretorioSvgFinal: %s\n", diretorioSvgFinal);
        printf("diretorioTxtFinal: %s\n", diretorioTxtFinal);

        // criando o arquivo .svg final , ou seja, após o qry
        FILE *svgFinal = fopen(diretorioSvgFinal, "w");
        if(svgFinal == NULL) {
            printf("\nNao foi possivel abrir o arquivo svg final."); return -1;
        }
        FILE *arqTxt = fopen(diretorioTxtFinal, "w");
        if(arqTxt == NULL) {
            printf("\nNao foi possivel criar o arquivo txt final."); return -1;
        }


        // PAREI AQUI ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨
        fprintf(svgFinal, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">");
        interpretandoQry(qryFile, arvore, svgFinal, arqTxt); // le o .qry, chama as funções do qry e preenche os arquivos finais
        visitaProfundidadeYxxT(arvore, createSvg, svgFinal);
        fprintf(svgFinal, "\n</svg>");  // fechando o arquivo svg

        free(diretorioEntradaQry);
        free(diretorioSvgFinal);
        free(diretorioTxtFinal);
        fclose(qryFile);
        fclose(svgFinal);
        fclose(arqTxt);
    }

    // =========== LIBERANDO MEMÓRIA ==================

    free(diretorioEnt);
    free(nomeGeo);
    free(nomeQry);
    free(diretorioOut);
    free(diretorioEntradaGeo);
    free(diretorioSvgInicial);
    fclose(geoFile);
    fclose(svgInicial);

    printf("fim da main\n");

}
