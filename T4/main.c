#include "libs.h"
#include "system.h"
#include "digraph.h"

int main (int argc, char* argv[]) {

    char* dirEntrada = NULL;
    char* arqGeo = NULL;
    char* arqQry = NULL;
    char* dirSaida = NULL;
    char* arqVia = NULL;
    int leuQry = 0;
    int leuVia = 0;

    int i=0;

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

        } else if(strcmp("-v", argv[i]) == 0) { //
            ++i;
            arqVia = (char*)malloc(sizeof(char) * (strlen(argv[i])+5));
            strcpy(arqVia, argv[i]);
            leuVia++;
            
        }
        i++;
    }

    operations(dirEntrada, arqGeo, arqQry, dirSaida, arqVia, leuQry, leuVia);
    free(dirEntrada);
    free(arqGeo);
    free(arqQry);
    free(dirSaida);
    free(arqVia);
    
    return 0;
}