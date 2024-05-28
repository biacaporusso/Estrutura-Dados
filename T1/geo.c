#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "figuras.h"
#include "lista.h" 

void interpretandoGeo(FILE* geoFile, List lista) {

    //andar linha por linha do geo interpretando cada comando
    char comando[300];  // uma linha inteira do geo
    char partesComando[6][30]; // linha dividida entre partes
    char corContorno[30];
    char corPreench[30]; 

    while(!feof(geoFile)) { // Lê uma linha (inclusive com o '\n') enquanto nao chega ao fim do arquivo

        fgets(comando, 300, geoFile);

        if(comando[0] == 'c') {

            // para char poe null
            // para double poe 0
            //                                              c               id                 x                 y                raio            
            sscanf(comando, "%s %s %s %s %s %s %s", partesComando[0], partesComando[1], partesComando[2], partesComando[3], partesComando[4], corContorno, corPreench);
            Figura circ = criarFig(partesComando[0], partesComando[1], atof(partesComando[2]), 9999, 9999, atof(partesComando[3]), 9999, 9999, atof(partesComando[4]), 9999, 9999, corContorno, corPreench, NULL, NULL);
            inserirLista(lista, circ);

        } else if(comando[0] == 'r') {
            //                                               r                 id                x                  y                 w                 h           
            sscanf(comando, "%s %s %s %s %s %s %s %s", partesComando[0], partesComando[1], partesComando[2], partesComando[3], partesComando[4], partesComando[5], corContorno, corPreench);
            Figura rect = criarFig(partesComando[0], partesComando[1], atof(partesComando[2]), 9999, 9999, atof(partesComando[3]), 9999, 9999, 9999, atof(partesComando[4]), atof(partesComando[5]), corContorno, corPreench, NULL, NULL);
            inserirLista(lista, rect);

        } else if(comando[0] == 'l') {
            //                                             l                 id                x1                y1                x2                 y2         cor da linha
            sscanf(comando, "%s %s %s %s %s %s %s", partesComando[0], partesComando[1], partesComando[2], partesComando[3], partesComando[4], partesComando[5], corPreench);
            // criarFig(char tipo[],char id[], double x, double x1, double x2, double y, double y1, double y2, double r, double w, double h, char borda[], char preench[], char textoGeo[], char ancora[])
            Figura line = criarFig(partesComando[0], partesComando[1], 9999, atof(partesComando[2]), atof(partesComando[4]), 9999, atof(partesComando[3]), atof(partesComando[5]), 9999, 9999, 9999, NULL, corPreench, NULL, NULL);
            inserirLista(lista, line);

        } else if(comando[0] == 't') {
            //                                                    t                id                 x                 y                                        ancora            texto
            sscanf(comando, "%s %s %s %s %s %s %s %[^\n]", partesComando[0], partesComando[1], partesComando[2], partesComando[3], corContorno, corPreench, partesComando[4], partesComando[5]);        
            Figura text = criarFig(partesComando[0], partesComando[1], atof(partesComando[2]), 9999, 9999, atof(partesComando[3]), 9999, 9999, 9999, 9999, 9999, corContorno, corPreench, partesComando[5], partesComando[4]);
            inserirLista(lista, text);
            
        }
    }
}
