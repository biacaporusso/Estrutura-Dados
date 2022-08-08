#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parametros.h"

char* getNomeQry(char* arquivoQry) {

    char* nomeQry = strrchr(arquivoQry, '/'); 
    nomeQry++;
    nomeQry = strtok(nomeQry, ".");
    return nomeQry;

}

void diretorios(char* diretorio, char* arquivoGeo, char* arqCompleto) { //tratamentos no endereço

    if (diretorio[strlen(diretorio)-1] == '/' || arquivoGeo[0] == '/') {

        if(diretorio[strlen(diretorio)-1] == '/' && arquivoGeo[0] == '/') {

            strcat(arqCompleto, diretorio);
            strcat(arqCompleto, ".");
            strcat(arqCompleto, arquivoGeo);
        } else {

            strcat(arqCompleto, diretorio);
            strcat(arqCompleto, arquivoGeo);
        }
    } else {

        strcat(arqCompleto, diretorio);
        strcat(arqCompleto, "/");
        strcat(arqCompleto, arquivoGeo);
    }
}
