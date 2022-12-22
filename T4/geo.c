#include "libs.h"
#include "via.h"
#include "geo.h"
#include "SRBtree.h" 
#include "figures.h"

void readingGeo(FILE* geoFile, SRbTree tree) {

    //andar linha por linha do geo interpretando cada comando
    char comando[300];  // uma linha inteira do geo
    char partesComando[7][30]; // linha dividida entre partes
    char corContorno[30];
    char corPreench[30]; 
    float espessuraBorda=0.5;

    while(!feof(geoFile)) { // Lê uma linha (inclusive com o '\n') enquanto nao chega ao fim do arquivo

        fgets(comando, 300, geoFile);
        //Node no;

        if(comando[0] == 'c' && comando[1] == ' ') {
            //                                              c               id                 x                 y                raio            
            sscanf(comando, "%s %s %s %s %s %s %s", partesComando[0], partesComando[1], partesComando[2], partesComando[3], partesComando[4], corContorno, corPreench);
            Figura circ = criarFig(partesComando[0], atoi(partesComando[1]), atof(partesComando[2]), 9999, 9999, atof(partesComando[3]), 9999, 9999, atof(partesComando[4]), 9999, 9999, corContorno, corPreench, NULL, NULL, NULL, -1);
            insertSRb(tree, getX(circ), getY(circ), getX(circ)-getR(circ), getY(circ)-getR(circ), getX(circ)+getR(circ), getY(circ)+getR(circ), circ);

        } else if(comando[0] == 'r') {
            //                                               r                 id                x                  y                 w                 h           
            sscanf(comando, "%s %s %s %s %s %s %s %s", partesComando[0], partesComando[1], partesComando[2], partesComando[3], partesComando[4], partesComando[5], corContorno, corPreench);
            Figura rect = criarFig(partesComando[0], atoi(partesComando[1]), atof(partesComando[2]), 9999, 9999, atof(partesComando[3]), 9999, 9999, 9999, atof(partesComando[4]), atof(partesComando[5]), corContorno, corPreench, NULL, NULL, NULL, -1);
            insertSRb(tree, getX(rect), getY(rect), getX(rect), getY(rect), getX(rect)+getW(rect), getY(rect)+getH(rect), rect);

        } else if(comando[0] == 'l') {
            //                                             l                 id                x1                y1                x2                 y2         cor da linha
            sscanf(comando, "%s %s %s %s %s %s %s", partesComando[0], partesComando[1], partesComando[2], partesComando[3], partesComando[4], partesComando[5], corPreench);
            // criarFig(char tipo[],char id[], double x, double x1, double x2, double y, double y1, double y2, double r, double w, double h, char borda[], char preench[], char textoGeo[], char ancora[])
            Figura line = criarFig(partesComando[0], atoi(partesComando[1]), atof(partesComando[2]), atof(partesComando[2]), atof(partesComando[4]), atof(partesComando[3]), atof(partesComando[3]), atof(partesComando[5]), 9999, 9999, 9999, NULL, corPreench, NULL, NULL, NULL, -1);
            insertSRb(tree, getX1(line), getY1(line), getX1(line), getY1(line), getX2(line), getY2(line), line);

        } else if(comando[0] == 't') {
            //                                                    t                id                 x                 y                                        ancora            texto
            sscanf(comando, "%s %s %s %s %s %s %s %[^\n]", partesComando[0], partesComando[1], partesComando[2], partesComando[3], corContorno, corPreench, partesComando[4], partesComando[5]);        
            //                            tipo[]               id                       x             x1    x2              y             y1    y2    r     w     h      borda[]    preench[]     textoGeo[]          ancora[]     cep[]  float espessura
            Figura text = criarFig(partesComando[0], atoi(partesComando[1]), atof(partesComando[2]), 9999, 9999, atof(partesComando[3]), 9999, 9999, 9999, 9999, 9999, corContorno, corPreench, partesComando[5], partesComando[4], NULL, -1);
            insertSRb(tree, getX(text), getY(text), getX(text), getY(text), getX(text), getY(text), text);

        } else if(comando[0] == 'q') {
            //                                         q                 cep               x                y                   w                  h
            sscanf(comando, "%s %s %s %s %s %s", partesComando[0], partesComando[1], partesComando[2], partesComando[3], partesComando[4], partesComando[5]);
            
            //                              tipo[]     id            x              x1  x2          y              y1   y2  r         w                         h             borda[]    preench[] textoGeo[] ancora[] cep[] float espessura
            Figura quadra = criarFig(partesComando[0], -1, atof(partesComando[2]), -1, -1, atof(partesComando[3]), -1, -1, -1, atof(partesComando[4]), atof(partesComando[5]), corPreench, corContorno, NULL, NULL, partesComando[1], espessuraBorda);
            insertSRb(tree, getX(quadra), getY(quadra), getX(quadra), getY(quadra), getX(quadra)+getW(quadra), getY(quadra)+getH(quadra), quadra);
        //} else if(strcmp(comando[0], "cq")==0) {
        } else if (comando[0] == 'c' && comando[1] == 'q') {
            //                                   cq             espessura        preench     contorno
            sscanf(comando, "%s %s %s %s", partesComando[0], partesComando[1], corPreench, corContorno);
            espessuraBorda = atof(partesComando[1]);
        }
        strcpy(comando, " ");
    }
}

Digraph buildingVias(char* arqVia) {

    FILE *via = fopen(arqVia, "r");
    //Node n;
    int n;
    char vert1[30], vert2[30], rua[30], lesq[30], ldir[30];
    double x, y, cmp, vm;
    char comando[3];
    fscanf(via, "%d", &n);
    Digraph grafo = createGraph(n);
    int i=0;
    

    while (!feof(via)) {
        fscanf(via, "%s", comando);
        if (!strcmp("v", comando)) {
            fscanf(via, "%s %lf %lf", vert1, &x, &y);
            InfoNode infoVertice = criaVerticeVia(vert1, x, y);
            setNodeInfo(grafo, i, infoVertice);
            setNodeName(grafo, i, vert1);
            i++;

        } else if (!strcmp("e", comando)) {
            fscanf(via, "%s %s %s %s %lf %lf %s", vert1, vert2, ldir, lesq, &cmp, &vm, rua);
            InfoEdge infoAresta = criaArestaVia(rua, ldir, lesq, cmp, vm);
    
            // calcular sentido da aresta
            InfoNode v1 = getNodeInfo(grafo, getNode(grafo, vert1));
            InfoNode v2 = getNodeInfo(grafo, getNode(grafo, vert2));
            // ns (norte-sul) : x1 == x2 e y1 < y2
            // sn (sul-norte) : x1 == x2 e y1 > y2
            // ol (oeste-leste) : x1 < x2 e y1 == y2
            // lo (leste-oeste) : x1 > x2 e y1 == y2
            setSentido(infoAresta, "");
            if(getXvia(v1) == getXvia(v2) && getYvia(v1) < getYvia(v2)) {
                setSentido(infoAresta, "ns");
            } else if (getXvia(v1) == getXvia(v2) && getYvia(v1) > getYvia(v2)) {
                setSentido(infoAresta, "sn");
            } else if (getXvia(v1) < getXvia(v2) && getYvia(v1) == getYvia(v2)) {
                setSentido(infoAresta, "ol");
            } else if (getXvia(v1) == getXvia(v2) && getYvia(v1) < getYvia(v2)) {
                setSentido(infoAresta, "lo");
            }

            addEdge(grafo, getNode(grafo, vert1), getNode(grafo, vert2), infoAresta);

        }
        strcpy(comando, "");
    } 
    return grafo;
}
