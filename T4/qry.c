#include "libs.h"
#include "qry.h"
#include "SRBtree.h"
#include "figures.h"
#include "list.h"
#include "via.h"
#include "digraph.h"
#include "dijkstra.h"

typedef struct aux {
    
    char cep[30];
    void* quadra;
    FILE* txt;
    FILE* svg;
    double x, y, w, h;
    SRbTree tree;
    double fator;
    Node node;
    char cepO[30], faceO[3];
    double xO, yO, numO;

} Aux;

void readingQry(FILE* qryFile, SRbTree arvore, Digraph grafo, FILE* svg, FILE* arqTxt) {

    char comando[300];
    Aux* aux = calloc(1, sizeof(Aux));

    while (fscanf(qryFile, "%s", comando) != EOF) {

        if (strcmp(comando, "@o?") == 0) {
            char cep[30], face[2];
            double num;
            fscanf(qryFile, "%s %s %lf", cep, face, &num);
            fprintf(arqTxt, "\n[*] @o? %s %s %lf\n", cep, face, num);
            aux->svg = svg;
            aux->txt = arqTxt;
            oFunc(cep, face, num, arvore, svg, aux);

        } else if (strcmp(comando, "catac") == 0) {
            double x, y, w, h;
            fscanf(qryFile, "%lf %lf %lf %lf", &x, &y, &w, &h);
            fprintf(arqTxt, "\n[*] catac %lf %lf %lf %lf\n", x, y, w, h);
            catac(x, y, w, h, arqTxt, svg, arvore, grafo);

        } else if (strcmp(comando, "pnt") == 0) {
            char cep[30], cfill[20], cstrk[20];
            fscanf(qryFile, "%s %s %s", cep, cfill, cstrk);
            fprintf(arqTxt, "\n[*] pnt %s %s %s\n", cep, cfill, cstrk);
            pnt(cep, cfill, cstrk, arvore, arqTxt);

        } else if (strcmp(comando, "blq") == 0) {
            char nome[30], sentido[10];
            double x, y, w, h;
            fscanf(qryFile, "%s %s %lf %lf %lf %lf", nome, sentido, &x, &y, &w, &h);
            fprintf(arqTxt, "\n[*] blq %s %s %lf %lf %lf %lf\n", nome, sentido, x, y, w, h);
            blq(nome, sentido, x, y, w, h, grafo, arqTxt);

        } else if (strcmp(comando, "rbl") == 0) {
            char nome[50];
            fscanf(qryFile, "%s", nome);
            fprintf(arqTxt, "\n[*] rbl %s\n", nome);
            rbl(nome, grafo, arqTxt);

        } else if (strcmp(comando, "rf") == 0) {
            char cep[30], face[2];
            double fator;
            fscanf(qryFile, "%s %s %lf", cep, face, &fator);
            fprintf(arqTxt, "\n[*] rf %s %s %lf\n", cep, face, fator);
            rf(cep, face, fator, grafo, arqTxt, svg);

        } else if (strcmp(comando, "b") == 0) {
            double x, y, fator;
            fscanf(qryFile, "%lf %lf %lf", &x, &y, &fator);
            fprintf(arqTxt, "\n[*] b %lf %lf %lf\n", x, y, fator);
            bFunc(x, y, fator, arqTxt, svg, grafo);
            
        } else if (strcmp(comando, "p?") == 0) {
            char cep[30], face[2], cmc[20], cmr[20];
            double num;
            fscanf(qryFile, "%s %s %lf %s %s", cep, face, &num, cmc, cmr);
            fprintf(arqTxt, "\n[*] p? %s %s %lf %s %s\n", cep, face, num, cmc, cmr);
            aux->txt = arqTxt;
            aux->svg = svg;
            pFunc(cep, face, num, cmc, cmr, aux, arvore, grafo);

        }

        strcpy(comando, " ");
    }
    free(aux);
    
}

// ========================================= QUERIES =============================================================

void buscaCep(void* i, void* aux) {

    // i = quadra
    // aux = aux
    Aux* a = (Aux*) aux;
    if (strcmp(a->cep, getCep(i)) == 0) {
        a->quadra = i;
    }
}

void buscaRegiaoRetangular(void* i, void* aux) {

    Aux* a = (Aux*) aux;

    if (getX(i) >= (a->x)) {
        if (getX(i) + getW(i) <= (a->x) + (a->w)) {
            if (getY(i) >= (a->y)) {
                if (getY(i) + getH(i) <= (a->y) + (a->h)) {
                    a->quadra = i;
                    fprintf(a->txt, "\tfigura removida: x = %.2f y = %.2f cor borda = %s cor preenchimento = %s\n", getX(a->quadra), getY(a->quadra), getCorb(a->quadra), getCorp(a->quadra));
                    void* fig = getNodeSRb(a->tree, getX(a->quadra), getY(a->quadra), 0, 0, 0 ,0);
                    free(getInfoSRb(a->tree, fig));
                    setInfoSrb(a->tree, fig, NULL);

                }
            }
        }
    }

}

void pnt(char* cep, char* cfill, char* cstrk, SRbTree tree, FILE* txt) {

    Aux* structAux = malloc(sizeof(Aux));
    strcpy(structAux->cep, cep);
    percursoProfundidade(tree, buscaCep, structAux);
    setBorda(structAux->quadra, cstrk);
    setPreench(structAux->quadra, cfill);
    fprintf(txt, "\t quadra de cep %s - x: %.2lf, y: %.2lf\n", getCep(structAux->quadra), getX(structAux->quadra), getY(structAux->quadra));
    free(structAux);
}

// armazena a posição geográfica do endereço cep/face/num
void oFunc(char* cep, char* face, double num, SRbTree tree, FILE* svg, void* aux) {

    Aux* structAux = aux;
    strcpy(structAux->cep, cep);
    percursoProfundidade(tree, buscaCep, structAux);
    double xPosic, yPosic;
    xPosic = getX(structAux->quadra);
    yPosic = getY(structAux->quadra);
    
    if (strcmp(face, "S") == 0) {
        xPosic = xPosic + num;
    } else if (strcmp(face, "O") == 0) {
        xPosic = xPosic + getW(structAux->quadra);
        yPosic = yPosic + num;
    } else if (strcmp(face, "N") == 0) {
        xPosic = xPosic + num;
        yPosic = yPosic + getH(structAux->quadra);
    } else if (strcmp(face, "L") == 0) {
        yPosic = yPosic + num;
    }

    fprintf(svg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1.2%%\" stroke=\"%s\"/>", xPosic, yPosic, xPosic, yPosic+100, "red");
    //free(structAux);
    strcpy(structAux->cepO, cep);
    strcpy(structAux->faceO, face);
    structAux->xO = xPosic;
    structAux->yO = yPosic;
    structAux->svg = svg;
}

void arestaDentroRetangulo(Digraph grafo, void* aux) {

    Aux* stAux = aux;

    for (int i=0; i<graphSize(grafo); i++) {
        List lista = adjacentEdges(grafo, i, NULL);
        Edge aresta = getInicio(lista);
        while (aresta != NULL) {

            InfoNode v1 = getNodeInfo(grafo, i);
            Node to = getArestaTo(aresta);
            InfoNode v2 = getNodeInfo(grafo, to);
            double x1 = getXvia(v1);
            double x2 = getXvia(v2);
            double y1 = getYvia(v1);
            double y2 = getYvia(v2);

            Edge arestaAux = getNext(aresta);

            if (x1 >= stAux->x && x2 <= (stAux->x + stAux->w)) {
                if (y1 >= stAux->y && y2 <= (stAux->y + stAux->h)) {
                    fprintf(stAux->txt, "\taresta removida: x1, y1 = (%.2lf, %.2lf) e x2, y2 = (%.2lf, %.2lf)\n", x1, y1, x2, y2); 

                    removeEdge(grafo, aresta);
                }
            }

            aresta = arestaAux;
        }


    }
}

void catac(double x, double y, double w, double h, FILE* arqTxt, FILE* arqSvg, SRbTree tree, Digraph grafo) {

    Aux* structAux = calloc(1, sizeof(Aux));
    structAux->x = x;
    structAux->y = y;
    structAux->w = w;
    structAux->h = h;
    structAux->txt = arqTxt;
    structAux->tree = tree;
    percursoProfundidade(tree, buscaRegiaoRetangular, structAux);
    fprintf(arqSvg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"#AB37C8\" stroke=\"#AA0044\" fill-opacity=\"%f\"/>", x, y, w, h, 0.5);

    arestaDentroRetangulo(grafo, structAux);
    free(structAux);
}

void blq(char* nome, char* sentido, double x, double y, double w, double h, Digraph grafo, FILE* txt) {

    int i;
    int tam = graphSize(grafo);
    for (i=0; i < tam; i++) {
        List vertice = adjacentEdges(grafo, i, NULL);
        Edge aresta = getInicio(vertice);
        while(aresta != NULL) {

            Node nodeFrom = getFromNode(grafo, aresta);
            Node nodeTo = getToNode(grafo, aresta);
            InfoNode v1 = getNodeInfo(grafo, nodeFrom);
            InfoNode v2 = getNodeInfo(grafo, nodeTo);
            // comparação se a aresta está dentro da região retangular
            
            InfoEdge infoAresta = getEdgeInfo(grafo, aresta);

            char sentidoAresta[3] = "--";

            strcpy(sentidoAresta, getSentido(infoAresta));
            if(strcmp(sentidoAresta, sentido) == 0) {
                if (getXvia(v1) >= x && getXvia(v2) <= x+w) {
                    if (getYvia(v1) >= y && getYvia(v2) <= y+h) {
                        setArestaDesativada(aresta);
                        setNomeBloqueio(infoAresta, nome);
                        fprintf(txt, "\taresta %s desabilitada: x1, y1 = (%.2lf, %.2lf) e x2, y2 = (%.2lf, %.2lf)\n", getNomeBloqueio(infoAresta), getXvia(v1), getYvia(v1), getXvia(v2), getYvia(v2));
                    }
                } 
            }
            aresta = getNext(aresta);
        }
    }
}

void rbl(char* nome, Digraph grafo, FILE* txt) {
    int i;
    int tam = graphSize(grafo);
    for (i=0; i < tam; i++) {
        List vertice = adjacentEdges(grafo, i, NULL);
        Edge aresta = getInicio(vertice);

        while(aresta != NULL) {

        InfoEdge infoAresta = getEdgeInfo(grafo, aresta);

            if(strcmp(nome, getNomeBloqueio(infoAresta)) == 0) {
                setArestaAtivada(aresta);
                fprintf(txt, "\taresta %s reabilitada\n", getNomeRua(getEdgeInfo(grafo, aresta)));
            }
            aresta = getNext(aresta);
        }
    }

}

void rf(char* cep, char* face, double fator, Digraph grafo, FILE* txt, FILE* svg) {
    
    Aux* extra = calloc(1, sizeof(Aux));
    extra->txt = txt;
    extra->svg = svg;
    dfs(grafo, 0, arestaDeArvore, arestaDeAvanco, arestaDeRetorno, arestaCruzada, criaFloresta, extra);

}

void bFunc(double x, double y, double fator, FILE* txt, FILE* svg, Digraph grafo) {
    
    Aux* extra = calloc(1, sizeof(Aux));
    extra->txt = txt;
    extra->svg = svg;
    extra->x = x;
    extra->y = y;
    extra->fator = fator;
    Node noProximo = localizaVerticeMaisProximo(grafo, x, y);
    bfs(grafo, noProximo, discoverNode, extra);

}

void pFunc(char* cep, char* face, double num, char* cmc, char* cmr, void* aux, SRbTree tree, Digraph grafo) {

    Aux* stAux = aux;
    // 1ª PARTE: ACHAR QUAL O VÉRTICE DE ORIGEM (MAIS PRÓXIMO DA LOCALIZAÇÃO PASSADA NO @o)
    double xOrig = stAux->xO;
    double yOrig = stAux->yO;
    Node verticeOrigem = localizaVerticeMaisProximo(grafo, xOrig, yOrig);


    // 2ª PARTE: ACHAR QUAL O VÉRTICE DE DESTINO (MAIS PRÓXIMO DA LOCALIZAÇÃO PASSADA NESSA FUNÇÃO p?)
    stAux->tree = tree;
    strcpy(stAux->cep, cep);
    percursoProfundidade(tree, buscaCep, stAux);
    double xPosic = getX(stAux->quadra);
    double yPosic = getY(stAux->quadra);

    if (strcmp(face, "S") == 0) {
        xPosic = xPosic + num;
    } else if (strcmp(face, "O") == 0) {
        xPosic = xPosic + getW(stAux->quadra);
        yPosic = yPosic + num;
    } else if (strcmp(face, "N") == 0) {
        xPosic = xPosic + num;
        yPosic = yPosic + getH(stAux->quadra);
    } else if (strcmp(face, "L") == 0) {
        yPosic = yPosic + num;
    }
    Node verticeDestino = localizaVerticeMaisProximo(grafo, xPosic, yPosic);

    // Dijkstra p calcular o percurso entre o vértice de origem e o de destino
    dijkstra(grafo, verticeOrigem, verticeDestino, stAux->txt, stAux->svg, cmc, cmr, 1);  // comprimento
    dijkstra(grafo, verticeOrigem, verticeDestino, stAux->txt, stAux->svg, cmc, cmr, 2);  // velocidade
}

Node localizaVerticeMaisProximo(Digraph grafo, double xRef, double yRef) {

    Node vertMaisProximo = -1;
    for(int i=0; i<graphSize(grafo); i++) {
        InfoNode info = getNodeInfo(grafo, i);
        double xV = getXvia(info);
        double yV = getYvia(info);

        if (fabs(xRef - xV) <= 30 && fabs(yRef - yV) <= 30) {
            vertMaisProximo = i;
            return vertMaisProximo;
        } 
    }
    return -1;
}

bool discoverNode(Digraph g, Edge e, int td, int tf, void *extra) {

    Aux* stAux = (Aux*) extra;
    if (e != NULL && getStatusAresta(e) == true) {
        InfoEdge info = getEdgeInfo(g, e);
        double vmNova = getVelocidadeAresta(info) * stAux->fator;
        fprintf(stAux->txt, "\taresta %s afetada: velocidade antiga = %.2lf velocidade atualizada = %.2lf\n", getNomeRua(info), getVelocidadeAresta(info), vmNova);
        setVelocidadeAresta(info, vmNova);

        double x1 = getXvia(getNodeInfo(g, getFromNode(g, e)));
        double x2 = getXvia(getNodeInfo(g, getToNode(g, e)));
        double y1 = getYvia(getNodeInfo(g, getFromNode(g, e)));
        double y2 = getYvia(getNodeInfo(g, getToNode(g, e)));
        fprintf(stAux->svg, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", x1, y1, x2, y2, "#c83737");

    }

    return false;
}

bool arestaDeArvore(Digraph g, Edge e, int td, int tf, void *extra) {

    Aux* structAux = (Aux*) extra;
    double velocAntiga = getVelocidadeAresta(getEdgeInfo(g, e));
    double velocNova = velocAntiga * structAux->fator;
    fprintf(structAux->txt, "\taresta de árvore: %s, velocidade antiga: %.2lf, velocidade atual: %.2lf\n", getNomeRua(getEdgeInfo(g, e)), velocAntiga, velocNova);
    return false;
}

bool arestaDeAvanco(Digraph g, Edge e, int td, int tf, void *extra) {

    Aux* structAux = (Aux*) extra;
    double velocAntiga = getVelocidadeAresta(getEdgeInfo(g, e));
    double velocNova = velocAntiga * structAux->fator;
    fprintf(structAux->txt, "\taresta de avanço: %s, velocidade antiga: %.2lf, velocidade atual: %.2lf\n", getNomeRua(getEdgeInfo(g, e)), velocAntiga, velocNova);
    Node from = getArestaFrom(e);
    Node to = getArestaTo(e);
    double x1 = getXvia(getNodeInfo(g, from));
    double x2 = getXvia(getNodeInfo(g, to));
    double y1 = getYvia(getNodeInfo(g, from));
    double y2 = getYvia(getNodeInfo(g, to));
    fprintf(structAux->svg, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", x1, y1, x2, y2, "#0000ff");
    return false;
}

bool arestaDeRetorno(Digraph g, Edge e, int td, int tf, void *extra) {

    Aux* structAux = (Aux*) extra;
    double velocAntiga = getVelocidadeAresta(getEdgeInfo(g, e));
    double velocNova = velocAntiga * structAux->fator;
    fprintf(structAux->txt, "\taresta de retorno: %s, velocidade antiga: %.2lf, velocidade atual: %.2lf\n", getNomeRua(getEdgeInfo(g, e)), velocAntiga, velocNova);
    Node from = getArestaFrom(e);
    Node to = getArestaTo(e);
    double x1 = getXvia(getNodeInfo(g, from));
    double x2 = getXvia(getNodeInfo(g, to));
    double y1 = getYvia(getNodeInfo(g, from));
    double y2 = getYvia(getNodeInfo(g, to));
    fprintf(structAux->svg, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", x1, y1, x2, y2, "#ff6600");
    return false;
}

bool arestaCruzada(Digraph g, Edge e, int td, int tf, void *extra) {

    Aux* structAux = (Aux*) extra;
    double velocAntiga = getVelocidadeAresta(getEdgeInfo(g, e));
    double velocNova = velocAntiga * structAux->fator;
    fprintf(structAux->txt, "\taresta cruzada: PONTE %s, velocidade antiga: %.2lf, velocidade atual: %.2lf\n", getNomeRua(getEdgeInfo(g, e)), velocAntiga, velocNova);
    Node from = getArestaFrom(e);
    Node to = getArestaTo(e);
    double x1 = getXvia(getNodeInfo(g, from));
    double x2 = getXvia(getNodeInfo(g, to));
    double y1 = getYvia(getNodeInfo(g, from));
    double y2 = getYvia(getNodeInfo(g, to));
    fprintf(structAux->svg, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\"/>", x1, y1, x2, y2, "magenta");
    return false;
}

bool criaFloresta(Digraph g, void *extra) {
    Aux* a = (Aux*) extra;
    fprintf(a->txt, "\tnó %s inserido na floresta\n", getNomeVert(adjacentEdges(g, a->node, NULL)));
    return false;
}

void setNoFloresta(void* aux, Node i) {

    Aux* a = (Aux*) aux;
    a->node = i;
}
