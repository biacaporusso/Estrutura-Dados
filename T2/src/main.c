#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parametros.h"
#include "system.h"

int main (int argc, char* argv[]) {

    char* dirEntrada = NULL;
    char* arqGeo = NULL;
    char* arqQry = NULL;
    char* dirSaida = NULL;
    int leuQry = 0;

    printf("iniciando o for\n");
    int i;
    for(i=0; i<argc; i++) {
        printf("i = %d ", i);
        printf("%s\n", argv[i]);
    }

    i=0;
    while(i<argc) {

        if(strcmp("-e", argv[i]) == 0) { // diretorio de entrada (opcional)
            ++i; // a proxima string vai ser o caminho para o diretorio da base de entrada
            dirEntrada = (char*)malloc((strlen(argv[i])+5)*sizeof(char));
            strcpy(dirEntrada, argv[i]);

        } else if(strcmp("-f", argv[i]) == 0) { // arquivo geo (obrigatorio)
            ++i;
            arqGeo = (char*)malloc(sizeof(char) * (strlen(argv[i])+5));
            strcpy(arqGeo, argv[i]);

        } else if(strcmp("-q", argv[i]) == 0) { // arquivo qry (opcional)
            ++i;
            arqQry = (char*)malloc(sizeof(char) * (strlen(argv[i])+5));
            strcpy(arqQry, argv[i]);
            leuQry++;

        } else if(strcmp("-o", argv[i]) == 0) { // diretorio saida (obrigatorio)
            ++i;
            dirSaida = (char*)malloc((strlen(argv[i])+5)*sizeof(char));
            strcpy(dirSaida, argv[i]);

        } 
        i++;
    }
    operacoes(dirEntrada, arqGeo, arqQry, dirSaida, leuQry);
    printf("fim da main\n");

    return 0;
}