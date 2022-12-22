#include "libs.h"
#include "dijkstra.h"
#include "digraph.h"
#include "via.h"
#include <float.h>

void iniciaDijkstra(Digraph grafo, double* distancia, int* pai, int noInicial) {
    
    for(int i = 0; i < graphSize(grafo); i++) {
        distancia[i] = DBL_MAX;
        pai[i] = -1;
    }
    distancia[noInicial] = 0.0;
}

void relaxaComprimento(Digraph grafo, double* distancia, int* pai, int no1, int no2) {

    List listaArestas = adjacentEdges(grafo, no1, NULL);
    
    Edge aresta = getInicio(listaArestas);
    while (aresta != NULL && getArestaTo(aresta) != no2) {
        aresta = getNext(aresta);
    }

    if(aresta) {
        if(distancia[no2] > distancia[no1] + getComprimento(getEdgeInfo(grafo, aresta))) {
            distancia[no2] = distancia[no1] + getComprimento(getEdgeInfo(grafo, aresta));
            pai[no2] = no1;
        }
    }
}

void relaxaVelocidade(Digraph grafo, double* distancia, int* pai, int no1, int no2) {

    List listaArestas = adjacentEdges(grafo, no1, NULL);
    
    Edge aresta = getInicio(listaArestas);
    while (aresta != NULL && getArestaTo(aresta) != no2) {
        aresta = getNext(aresta);
    }

    if(aresta) {
        if(distancia[no2] > distancia[no1] + getVelocidadeAresta(getEdgeInfo(grafo, aresta))) {
            distancia[no2] = distancia[no1] + getVelocidadeAresta(getEdgeInfo(grafo, aresta));
            pai[no2] = no1;
        }
    }
}

bool existeAberto(Digraph grafo, int* aberto) {
    
    for(int i = 0; i < graphSize(grafo); i++) {
        if(aberto[i])
            return true;
    }
    return false;
}

int menorDistancia(Digraph grafo, int* aberto, double* distancia) {
    
    int i = 0, menor;

    while(i < graphSize(grafo)) {
        if(aberto[i])
            break;
        i++;
    }

    if(i == graphSize(grafo))
        return -1;

    menor = i;

    for(i = i+1; i < graphSize(grafo); i++) {
        if(aberto[i] && distancia[menor] > distancia[i])
            menor = i;
    }
    return menor;
}

int* dijkstra(Digraph grafo, Node noInicial, Node noFinal, FILE* txt, FILE* svg, char* cmc, char* cmr, int tipo) {

    if(noInicial == -1 || noFinal == -1) {
        return NULL;
    }

    double* distancia = (double*) malloc(graphSize(grafo)*sizeof(double));
    int* caminho = (int*) malloc(graphSize(grafo)*sizeof(int));
    int pai[graphSize(grafo)];
    int menor, aux, i;
    char direcao[20], direcaoAnterior[20];
    int aberto[graphSize(grafo)];
    Edge aresta;

    iniciaDijkstra(grafo, distancia, pai, noInicial);

    for(i = 0; i < graphSize(grafo); i++){
        aberto[i] = true;
    }

        while (existeAberto(grafo, aberto))
        {
            menor = menorDistancia(grafo, aberto, distancia);
            aberto[menor] = false;

            aresta = getInicio(adjacentEdges(grafo, menor, NULL));
            while(aresta && getStatusAresta(aresta) == true) {
                if(tipo == 2)
                    relaxaVelocidade(grafo, distancia, pai, menor, getArestaTo(aresta));
                else
                    relaxaComprimento(grafo, distancia, pai, menor, getArestaTo(aresta));

                aresta = getNext(aresta);
            }
        }
        aux = noFinal;

        for(i = 0; i < graphSize(grafo); i++) {
            caminho[i] = -1;
        }

        i = graphSize(grafo)-1;

        while(aux != -1 && i >= 0) {
            caminho[i] = aux;
            i--;
            aux = pai[aux];
        }

        // svg part
        double x0=0, y0=0, x1=0, y1=0;
        for(i = 0; i < graphSize(grafo) - 1; i++) {

            if(caminho[i] == -1)
                continue;
            if(tipo == 1) {

                x0 = getXvia(getNodeInfo(grafo, caminho[i]));
                y0 = getYvia(getNodeInfo(grafo, caminho[i]));
                x1 = getXvia(getNodeInfo(grafo, caminho[i+1]));
                y1 = getYvia(getNodeInfo(grafo, caminho[i+1]));
                fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: %s; stroke-width:4; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n", x0, y0, x1, y1, cmc, x0, y0, x1, y1);

            } else {

                x0 = getXvia(getNodeInfo(grafo, caminho[i]));
                y0 = getYvia(getNodeInfo(grafo, caminho[i]));
                x1 = getXvia(getNodeInfo(grafo, caminho[i+1]));
                y1 = getYvia(getNodeInfo(grafo, caminho[i+1]));
                fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: %s; stroke-width:4; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"blue\" fill=\"blue\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"3s\" repeatCount=\"indefinite\" /> </circle>\n", x0-10, y0-10, x1-10, y1-10, cmr, x0-10, y0-10, x1-10, y1-10);
            }
        }

        if(tipo == 1) {
            fprintf(txt, "\n\tCaminho mais curto: ");
        } else {
            fprintf(txt, "\n\tCaminho mais rápido: ");
        }

        strcpy(direcaoAnterior, "direcaoAnterior");
        for(i = 0; i < graphSize(grafo) - 1; i++) {

            if(caminho[i] == -1) {
                continue;
            }

            aresta = getEdge(grafo, caminho[i], caminho[i+1]);

            x0 = getXvia(getNodeInfo(grafo, caminho[i]));
            y0 = getYvia(getNodeInfo(grafo, caminho[i]));
            x1 = getXvia(getNodeInfo(grafo, caminho[i+1]));
            y1 = getYvia(getNodeInfo(grafo, caminho[i+1]));

            if(x0 < x1) {
                strcpy(direcao, "Oeste");
            } else if(x0 > x1) {
                strcpy(direcao, "Leste");
            } else if(y0 < y1) {
                strcpy(direcao, "Norte");
            } else if(y0 > y1) {
                strcpy(direcao, "Sul");
            }

            if(strcmp(direcaoAnterior, "direcaoAnterior") == 0) {
                fprintf(txt, "\n\tSiga na direcao %s na Rua %s ", direcao, getNomeRua(getEdgeInfo(grafo, aresta)));
            }else if(strcmp(direcao, direcaoAnterior) != 0) {
                fprintf(txt, "ate o cruzamento com a Rua %s. ", getNomeRua(getEdgeInfo(grafo, aresta)));
                fprintf(txt, "Siga na direcao %s na Rua %s ", direcao, getNomeRua(getEdgeInfo(grafo, aresta)));
            }

            strcpy(direcaoAnterior, direcao);
        }

        if(strcmp(direcaoAnterior, "direcaoAnterior") == 0) {

            fprintf(txt, "\nNao ha caminho entre esses dois pontos.\n");
            fprintf(svg, "\t<path d=\"M%lf,%lf %lf,%lf\" style=\"stroke: #000000; stroke-width:1; stroke-dasharray:2,2\"/> <circle cx=\"0\" cy=\"0\" r=\"5\" stroke=\"red\" fill=\"red\"> <animateMotion path =\"M%lf,%lf %lf,%lf\" begin=\"0s\" dur=\"6s\" repeatCount=\"indefinite\" /> </circle>\n", x0, y0, x1, y1, x0, y0, x1, y1);

        } else {
            fprintf(txt, ". Chegou em seu destino.\n");
        }

        free(distancia);
        free(caminho);

        return NULL;
}