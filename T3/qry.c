#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qry.h"
#include "SRBtree.h"
#include "figures.h"

typedef struct aux {
    int id;
    Figura fig;
    FILE* arqTxt;
    FILE* arqSvg;
    char lado[4];
    double x, y, w, h, dx, dy, energia, dinheiro;
    SRbTree tree;

} AuxId;

void readingQry(FILE* qryFile, SRbTree arvore, FILE* svg, FILE* arqTxt) {

    char comando[500];
    /*
    char lado[4];
    int id; */
    //double dx, dy, e, w, h, d, x, y;

    while (fscanf(qryFile, "%s", comando) != EOF) {

        if (strcmp(comando, "e") == 0) {
            double e;
            fscanf(qryFile, "%lf", &e);
            fprintf(arqTxt, "\n[*] e %lf\n", e);
            AuxId* st = calloc(1, sizeof(AuxId));
            st->energia = e;
            st->arqTxt = arqTxt;
            percursoProfundidade(arvore, Efunc, st);
            free(st);

        } else if (!strcmp(comando, "mv")) {
            double dx, dy;
            int id;
            fscanf(qryFile, "%d %lf %lf", &id, &dx, &dy);
            fprintf(arqTxt, "\n[*] mv %d %lf %lf\n", id, dx, dy);
            AuxId* st = calloc(1, sizeof(AuxId));
            st->id = id;
            percursoProfundidade(arvore, getNau, st);
            MVfunc(arvore, dx, dy, st->fig, arqTxt);
            free(st);

        } else if (!strcmp(comando, "lr")) {
            double d, w, h;
            int id;
            char lado[4];
            fscanf(qryFile, "%d %s %lf %lf %lf", &id, lado, &d, &w, &h);
            fprintf(arqTxt, "\n[*] lr %d %s %lf %lf %lf\n", id, lado, d, w, h);
            AuxId* st = calloc(1, sizeof(AuxId));
            st->id = id;
            strcpy(st->lado, lado);
            st->arqTxt = arqTxt;
            st->arqSvg = svg;
            st->tree = arvore;
            percursoProfundidade(arvore, getNau, st);
            double enArr = energiaArremesso(w, h, d);
            if(st->fig != NULL && getEnergia(st->fig) >= enArr) {
                LRfunc(arvore, d, w, h, st, arqTxt);
                fprintf(st->arqTxt, "\nEnergia da nau ANTES: %.2lf\n", getEnergia(st->fig));
                percursoProfundidade(arvore, LRaux, st);
                perdaEnergia(st->fig, enArr);
                fprintf(st->arqTxt, "Energia da nau DEPOIS: %.2lf\n", getEnergia(st->fig));
                fprintf(st->arqTxt, "Captura do lançamento: M$%.2lf\n", getDinheiro(st->fig));
            } 
            free(st);

        } else if (!strcmp(comando, "d")) {
            double d;
            int id;
            char lado[4];
            fscanf(qryFile, "%d %s %lf", &id, lado, &d);
            fprintf(arqTxt, "\n[*] d %d %s %lf\n", id, lado, d);
            AuxId* st = calloc(1, sizeof(AuxId));
            st->id = id;
            st->tree = arvore;
            strcpy(st->lado, lado);
            st->arqTxt = arqTxt;
            st->arqSvg = svg;
            percursoProfundidade(arvore, getNau, st);
            if(st->fig != NULL && getEnergia(st->fig) >= d) {
                fprintf(st->arqTxt, "\nEnergia da nau ANTES: %.2lf\n", getEnergia(st->fig));
                Dfunc(arvore, d, st);
                percursoProfundidade(arvore, Daux, st); // 
                perdaEnergia(st->fig, d);
                fprintf(st->arqTxt, "Energia da nau DEPOIS: %.2lf\n", getEnergia(st->fig));
            }
            free(st);

        } else if (!strcmp(comando, "mc")) {
            double dx, dy, x, y, w, h;
            fscanf(qryFile, "%lf %lf %lf %lf %lf %lf", &dx, &dy, &x, &y, &w, &h);
            fprintf(arqTxt, "\n[*] mc %lf %lf %lf %lf %lf %lf\n", dx, dy, x, y, w, h);
            AuxId* st = calloc(1, sizeof(AuxId));
            st->x = x;
            st->y = y;
            st->w = w;
            st->h = h;
            st->dx = dx;
            st->dy = dy;
            st->arqTxt = arqTxt;
            percursoProfundidade(arvore, MCfunc, st);
            free(st);

        }

        strcpy(comando, " ");
    }
    fprintf(arqTxt, "\n================ RELATORIO FINAL ================\n");
    percursoProfundidade(arvore, printResultados, arqTxt);
    
}

// ========================================= QUERIES =============================================================

void Efunc(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux) {
    
    AuxId* nau = aux;

    if (getTipo(i) == 2) {
        setEnergia(i, nau->energia);
        fprintf(nau->arqTxt, "\nNau - id: %d\nAncora = %.2lf, %.2lf\nLargura = %.2lf\nAltura = %.2lf\nCor borda = %s\nCor preenchimento = %s\n", getID(i), getX(i), getY(i), getW(i), getH(i), getCorb(i), getCorp(i));
    }
} 

void MVfunc(SRbTree tree, double dx, double dy, Info fig, FILE* arqTxt) {

    // primeiro: remover o nó, vai retornar a figura contida nesse nó
    Figura st = removeSRb(tree, getX(fig), getY(fig), NULL, NULL, NULL, NULL);

    // fazer as mudanças na figura
    if (!st) return;
    switch (getTipo(st)) {
        case 1:  // circulo
            fprintf(arqTxt, "Circulo - id: %d\nPosição inicial: (%.2lf, %.2lf)\n", getID(st), getX(st), getY(st));
            changeX(st, getX(st) + dx);
            changeY(st, getY(st) + dy);
            insertSRb(tree, getX(st), getY(st), getX(st) - getR(st), getY(st) - getR(st), getX(st) + getR(st), getY(st) + getR(st), st);
            fprintf(arqTxt, "Posição final: (%.2lf, %.2lf)\n", getX(st), getY(st));
            break;
        case 2:  // retangulo
            fprintf(arqTxt, "Retangulo - id: %d\nPosição inicial: (%.2lf, %.2lf)\n", getID(st), getX(st), getY(st));
            changeX(st, getX(st) + dx);
            changeY(st, getY(st) + dy);
            insertSRb(tree, getX(st), getY(st), getX(st), getY(st), getX(st) + getW(st), getY(st) + getH(st), st);
            fprintf(arqTxt, "Posição final: (%.2lf, %.2lf)\n", getX(st), getY(st));
            break;
        case 3:  // linha
            fprintf(arqTxt, "Linha - id: %d\nPosição inicial: (%.2lf, %.2lf), (%.2lf, %.2lf)\n", getID(st), getX1(st), getY1(st), getX2(st), getY2(st));
            changeX1(st, getX1(st) + dx);
            changeX2(st, getX2(st) + dx);
            changeY1(st, getY1(st) + dy);
            changeY2(st, getY2(st) + dy);
            insertSRb(tree, getX(st), getY(st), getX1(st), getY1(st), getX2(st), getY2(st), st);
            fprintf(arqTxt, "Posição final: X(%.2lf, %.2lf) , Y(%.2lf, %.2lf)\n", getX1(st), getX2(st), getY1(st), getY2(st));
            break;
        case 4:  // texto
            fprintf(arqTxt, "Texto - id: %d\nPosição inicial: (%.2lf, %.2lf)\nTexto: %s\n", getID(st), getX(st), getY(st), getText(st));
            changeX(st, getX(st) + dx);
            changeY(st, getY(st) + dy);
            insertSRb(tree, getX(st), getY(st), getX(st), getY(st), getX(st), getY(st), st);
            fprintf(arqTxt, "Posição final: (%.2lf, %.2lf)\n", getX(st), getY(st));
            break;
        default:
            break;
    }
}

void LRfunc(SRbTree tree, double d, double w, double h, void* aux, FILE* arqTxt) {
    // comparar os lados da nau
    AuxId* st = aux;
    void* fig = st->fig;

    double xRede, yRede;

    if (strcmp(st->lado, "PP") == 0) {
        xRede = getX(fig);
        yRede = getY(fig) - d - h;

    } else if (strcmp(st->lado, "BB") == 0) {
        xRede = getX(fig) + getW(fig) + d;
        yRede = getY(fig);

    } else if (strcmp(st->lado, "PR") == 0) {
        xRede = getX(fig);
        yRede = getY(fig) + getH(fig) + d;

    } else if (strcmp(st->lado, "EB") == 0) {
        xRede = getX(fig) - d - w;
        yRede = getY(fig);
    }
    // criar rede no svg
    fprintf(st->arqSvg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" fill-opacity=\"2%%\" stroke=\"%s\"/>", xRede, yRede, w, h, "white", "red");

    st->x = xRede;
    st->y = yRede;
    st->w = w;
    st->h = h;
}

void Dfunc(SRbTree tree, double d, void* aux) {
    
    AuxId* nau = aux;
    void* fig = nau->fig;

    double xTiro, yTiro;

    if (strcmp(nau->lado, "PP") == 0) {
        xTiro = getX(fig) + (getW(fig) / 2);
        yTiro = getY(fig) - d;

    } else if (strcmp(nau->lado, "BB") == 0) {
        xTiro = getX(fig) + getW(fig) + d;
        yTiro = getY(fig) + (getH(fig) / 2);

    } else if (strcmp(nau->lado, "PR") == 0) {
        xTiro = getX(fig) + (getW(fig) / 2);
        yTiro = getY(fig) + getH(fig) + d;

    } else if (strcmp(nau->lado, "EB") == 0) {
        xTiro = getX(fig) - d;
        yTiro = getY(fig) + (getH(fig) / 2);
    }
    // printando a bomba no svg
    fprintf(nau->arqSvg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\"><![CDATA[%s]]></text>", xTiro, yTiro, "red", "black", "*");
    fprintf(nau->arqTxt, "PONTO DE IMPACTO: %.2lf, %.2lf\n", xTiro, yTiro);
    
    nau->x = xTiro;
    nau->y = yTiro;

}

void MCfunc (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {

    AuxId* st = aux;

    // se for um peixe e se estiver dentro da regiao
    if (getTipo(i) == 1 && circuloDentro(i, st)) {
        fprintf(st->arqTxt, "\nPeixe id %d transladado\nRaio: %.2lf\nPosição inicial: %.2lf, %.2lf\n", getID(i), getR(i), getX(i), getY(i));
        changeX(i, getX(i) + st->dx);
        changeY(i, getY(i) + st->dy);
        fprintf(st->arqTxt, "Posição final: %.2lf, %.2lf\n", getX(i), getY(i));
    }

}
// ============================= FUNÇÕES AUXILIARES =================================================

void printResultados (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux) {

    FILE* txt = aux;
    if (getTipo(i) == 2) {
        fprintf(txt, "\nNau - id %d\nSoma das capturas = %.2lf\nEnergia final = %.2lf\n", getID(i), getDinheiro(i), getEnergia(i));
    }
}

void getNau(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void* aux) {
    
    AuxId* nau = aux;

    // procurar o nó
    if (getID(i) == nau->id) {
        nau->fig = i;
    }
}

void LRaux (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {

    AuxId* nau = aux;

    if(figuraDentro(i, nau)) {
        Info fig = removeSRb(nau->tree, getX(i), getY(i), &mbbX1, &mbbY1, &mbbX2, &mbbY2);
        // circulo
        if (getTipo(fig) == 1) {
            fprintf(nau->arqTxt, "Peixe - id: %d\nAncora = (%.2lf, %.2lf)\nValor monetario: M$5,00\n", getID(fig), getX(fig), getY(fig));
            setDinheiro(nau->fig, 5);
        }
        // linha
        if (getTipo(fig) == 3) {
            fprintf(nau->arqTxt, "Camarao - id: %d\nAncora = X(%.2lf, %.2lf) , Y(%.2lf, %.2lf)\nValor monetario: M$1,00\n", getID(fig), getX(fig), getX2(fig), getY(fig), getY2(fig));
            setDinheiro(nau->fig, 1);
        }
        // texto
        if (getTipo(fig) == 4) {
            if(strcmp(getText(fig), ">-|-<") == 0) { // lagosta
                fprintf(nau->arqTxt, "Lagosta - id: %d\nAncora = (%.2lf, %.2lf)\nValor monetario: M$20,00\n", getID(fig), getX(fig), getY(fig));
                setDinheiro(nau->fig, 20);
            } else if(strcmp(getText(fig), "$") == 0) {
                fprintf(nau->arqTxt, "Moeda - id: %d\nAncora = (%.2lf, %.2lf)\n", getID(fig), getX(fig), getY(fig));
                setEnergia(nau->fig, 0.5); 
            } else {
                fprintf(nau->arqTxt, "Algas/detritos - id: %d\nAncora = (%.2lf, %.2lf)\n", getID(fig), getX(fig), getY(fig));
            }
        }
    }
}

void Daux (Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux) {

    AuxId* nau = aux; // st
    if(i && getTipo(i) == 2) {
    // se for uma nau e estiver dentro do ponto
        if(pontoDentro(i, nau)) {
            Info atingida = removeSRb(nau->tree, getX(i), getY(i), &mbbX1, &mbbY1, &mbbX2, &mbbY2);
            if (!atingida) return;
            fprintf(nau->arqTxt, "Nau %d atingida:\nx: %.2lf\ny: %.2lf\n", getID(atingida), getX(atingida), getY(atingida));
        }    
    }
}

bool figuraDentro(Info i, void* aux) {
    AuxId* st = aux;
    double x1 = st->x;
    double x2 = st->x + st->w;
    double y1 = st->y;
    double y2 = st->y + st->h;

    switch (getTipo(i)) {
        case 1:  // circulo
            if (getX(i) - getR(i) >= x1 && getX(i) + getR(i) <= x2) {
                if (getY(i) - getR(i) >= y1 && getY(i) + getR(i) <= y2) {
                    return true;
                }
            }
            return false;
            break;

        case 2:  // retangulo
            return false;
            break;

        case 3:
            if (x2 >= getX1(i) && y2 >= getY1(i)) {
                if (x2 >= getX2(i) && y2 >= getY2(i)) {
                    if (x1 <= getX1(i) && y1 <= getY1(i) && x1 <= getX2(i) && y1 <= getY2(i)) {
                        return true;
                    }
                }
            }
            return false;
            break;

        case 4: // texto
            if (getX(i) >= x1 && getX(i) <= x2) {
                if (getY(i) >= y1 && getY(i) <= y2) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
            break;
    }
    return false;
}

bool pontoDentro(Info i, void* aux) {

    AuxId* st = aux;


    double xPonto = st->x; // x do tiro
    double yPonto = st->y; // y do tiro

    // i com crtz é um retangulo
    if (xPonto >= getX(i) && xPonto <= getX(i) + getW(i)) {
        if (yPonto >= getY(i) && yPonto <= getY(i) + getH(i)) {
            return true;
        }
    }
    return false;
}

bool circuloDentro(Info i, void* aux) {
    AuxId* st = aux;
    double x1 = st->x;
    double x2 = st->x + st->w;
    double y1 = st->y;
    double y2 = st->y + st->h;

    if (getX(i) - getR(i) >= x1 && getX(i) + getR(i) <= x2) {
        if (getY(i) - getR(i) >= y1 && getY(i) + getR(i) <= y2) {
            return true;
        }
    }
    return false;

}

