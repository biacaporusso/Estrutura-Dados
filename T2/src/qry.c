#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qry.h"
#include "arvore.h"
#include "svg.h"
#include "figuras.h"

void leituraQry(FILE* qryFile, Tree arv, FILE* svg, FILE* arqTxt) {

    char comando[500], id[10];
    float x, y, dx, dy, w, h, agress, scoreInat=0, scoreDest=0;
    int qtdAtaques=0;

    while (fscanf(qryFile, "%s", comando) != EOF) {

        if (!strcmp(comando, "na")) {

            fscanf(qryFile, "%f ", &agress);

        }
        else if (!strcmp(comando, "tp")) {

            fscanf(qryFile, "%f %f", &x, &y);
            funcaoTP(getRaiz(arv), svg, arqTxt, x, y, &scoreDest);
            qtdAtaques++;

        }
        else if (!strcmp(comando, "tr")) {

            fscanf(qryFile, "%f %f %f %f %s", &x, &y, &dx, &dy, id);
            funcaoTR(getRaiz(arv), svg, arqTxt, x, y, dx, dy, id);
        }
        else if (!strcmp(comando, "be")) {

            fscanf(qryFile, "%f %f %f %f", &x, &y, &w, &h);
            svgRectArea(svg, x, y, w, h);
            funcaoBE(getRaiz(arv), svg, arqTxt, x, y, w, h, agress, &scoreInat);
            qtdAtaques++;
        }
        strcpy(comando, " ");
    }
    fprintf(arqTxt, "\n========== RESULTADOS FINAIS ==========\n");
    fprintf(arqTxt, "- Pontos de destruição: %f\n", scoreDest);
    fprintf(arqTxt, "- Pontos de inativação: %f\n", scoreInat);
    fprintf(arqTxt, "- Pontuação total: %f\n", scoreDest+scoreInat);
    fprintf(arqTxt, "- Proporção entre pontos obtidos e número de agressões: %f\n", (scoreDest+scoreInat)/qtdAtaques);

}

void funcaoTP(Node no, FILE* svg, FILE* arqTxt, float x, float y, float* scoreDest) {

    //printf("entrou TP\n");
    Item item;

    char tipo[2];
    int verificador;    // se verificador = 0 está dentro da coordenada , se = 1 não está dentro

    if (no == NULL) { // percorrer a arvore toda
        return;
    }

    item = getItem(no);

    strcpy(tipo, getTipo(item));

    if (strcmp(tipo, "r") == 0) {
        verificador = rectInside(x, y, item);
    }
    else if (strcmp(tipo, "c") == 0) {
        verificador = circInside(x, y, item);
    }
    else if (strcmp(tipo, "l") == 0) {
        verificador = lineInside(x, y, item);
    }
    else if (strcmp(tipo, "t") == 0) {
        verificador = textInside(x, y, item);
    }

    if (verificador == 0) {     // figura dentro da coordenada
        fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"red\">*</text>", x, y);

        if (strcmp(tipo, "c") == 0)
            fprintf(arqTxt, "circulo, id = %s, x = %f, y = %f, raio = %f, cor preenchimento = %s, cor borda = %s\n", getID(item), getX(item), getY(item), getR(item), getCorp(item), getCorb(item));
        else if (strcmp(tipo, "r") == 0)
            fprintf(arqTxt, "retangulo, id = %s, x = %f, y = %f, altura = %f, largura = %f, cor preenchimento = %s, cor borda = %s\n", getID(item), getX(item), getY(item), getH(item), getW(item), getCorp(item), getCorb(item));
        else if (strcmp(tipo, "t") == 0)
            fprintf(arqTxt, "texto, id = %s, x = %f, y = %f, ancora = %s, cor preenchimento = %s, cor borda = %s, texto = %s\n", getID(item), getX(item), getY(item), getAncora(item), getCorp(item), getCorb(item), getText(item));
        else if (strcmp(tipo, "l") == 0)
            fprintf(arqTxt, "linha, id = %s, x1 = %f, y1 = %f, x2 = %f, y2 = %f, cor = %s\n", getID(item), getX1(item), getY1(item), getX2(item), getY2(item), getCorp(item));

        *scoreDest = *scoreDest + getDestruicao(item);
        remover(item);
    }
    else {                    // figura fora da coordenada
        fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"grey\">*</text>", getX(item), getY(item));
        fprintf(arqTxt, "AGUA\n");
    }

    // recursão
    funcaoTP(getEsquerda(no), svg, arqTxt, x, y, scoreDest);
    funcaoTP(getMeio(no), svg, arqTxt, x, y, scoreDest);
    funcaoTP(getDireita(no), svg, arqTxt, x, y, scoreDest);

}

void funcaoTR(Node no, FILE* svg, FILE* arqTxt, float x, float y, float dx, float dy, char id[]) {

    Item item;
    float idFloat = atof(id);
    int verificador;

    // colocando um @ no ponto x,y
    fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"red\">@</text>", x, y);

    if (no == NULL) {
        return;
    }

    item = getItem(no);

    if (strcmp(getTipo(item), "r") == 0) {
        verificador = rectInside(x, y, item);
        if (verificador == 0) {

            fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(item) + dx, getY(item) + dy, getW(item), getH(item), getCorb(item), getCorp(item));
            fprintf(arqTxt, "\nATINGIDO: retangulo, id = %s\nx, y = %f, %f\naltura = %f\nlargura = %f\ncor preenchimento = %s\ncor borda = %s\n", getID(item), getX(item), getY(item), getH(item), getW(item), getCorp(item), getCorb(item));
            fprintf(arqTxt, "\nCLONE: retangulo, id = %f\nx, y = %f, %f\naltura = %f\nlargura = %f\ncor preenchimento = %s\ncor borda = %s\n\n-----------------------\n", idFloat, getX(item) + dx, getY(item) + dy, getH(item), getW(item), getCorb(item), getCorp(item));
            idFloat++;
        }
    }
    else if (strcmp(getTipo(item), "c") == 0) {
        verificador = circInside(x, y, item);
        if (verificador == 0) {

            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(item) + dx, getY(item) + dy, getR(item), getCorb(item), getCorp(item));
            fprintf(arqTxt, "\nATINGIDO: circulo, id = %s\nx, y = %f, %f\nraio = %f\ncor preenchimento = %s\ncor borda = %s\n", getID(item), getX(item), getY(item), getR(item), getCorp(item), getCorb(item));
            fprintf(arqTxt, "\nCLONE: circulo, id = %f\nx,y = %f, %f\nraio = %f\ncor preenchimento = %s\ncor borda = %s\n\n-----------------------\n", idFloat, getX(item) + dx, getY(item) + dy, getR(item), getCorb(item), getCorp(item));
            idFloat++;
        }
    }
    else if (strcmp(getTipo(item), "l") == 0) {
        verificador = lineInside(x, y, item);
        if (verificador == 0) {

            fprintf(svg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX1(item) + dx, getY1(item) + dy, getX2(item) + dx, getY2(item) + dy, getCorb(item), getCorp(item));
            fprintf(arqTxt, "\nATINGIDO: linha, id = %s\nx1, y1 = %f, %f\nx2, y2 = %f, %f\ncor preenchimento = %s\ncor borda = %s\n", getID(item), getX1(item), getY1(item), getX2(item), getY2(item), getCorp(item), getCorb(item));
            fprintf(arqTxt, "\nCLONE: linha, id = %f\nx1, y1 = %f, %f\nx2, y2 = %f, %f\ncor preenchimento = %s\ncor borda = %s\n\n-----------------------\n", idFloat, getX1(item) + dx, getY1(item) + dy, getX2(item) + dx, getY2(item) + dy, getCorb(item), getCorp(item));
            idFloat++;
        }
    }
    else if (strcmp(getTipo(item), "t") == 0) {
        verificador = textInside(x, y, item);
        if (verificador == 0) {

            fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\">%s</text>", getX(item) + dx, getY(item) + dy, getCorb(item), getCorp(item), getText(item));
            fprintf(arqTxt, "\nATINGIDO: texto, id = %s\nx, y = %f, %f\nancora = %s\ncor preenchimento = %s\ncor borda = %s\ntexto = %s\n", getID(item), getX(item), getY(item), getAncora(item), getCorp(item), getCorb(item), getText(item));
            fprintf(arqTxt, "\nCLONE: texto, id = %f\nx, y = %f, %f\nancora = %s\ncor preenchimento = %s\ncor borda = %s\ntexto = %s\n\n-----------------------\n", idFloat, getX(item) + dx, getY(item) + dy, getAncora(item), getCorb(item), getCorp(item), getText(item));
            idFloat++;
        }
    }

    // recursão
    funcaoTR(getEsquerda(no), svg, arqTxt, x, y, dx, dy, id);
    funcaoTR(getMeio(no), svg, arqTxt, x, y, dx, dy, id);
    funcaoTR(getDireita(no), svg, arqTxt, x, y, dx, dy, id);

}

void funcaoBE(Node no, FILE* svg, FILE* arqTxt, float x, float y, float w, float h, float agress, float* scoreInat) {

    Item item;
    int verificador;
    float red;
    float pi = 3.14;
    int raio;

    if (no == NULL) {
        return;
    }

    item = getItem(no);

    if (strcmp(getTipo(item), "r") == 0 && getProtecao(item) > 0) {
        verificador = insideIrradiation(x, y, w, h, 'r', item);
        if (verificador == 0) {
            
            red = (agress * (getW(item) * getH(item)) / (w * h));
            changeProtecao(item, red);

            svgAnchor(svg, getX(item), getY(item));

            if (getProtecao(item) <= 0) {
                fprintf(arqTxt, "Retangulo REMOVIDA:\n");
                fprintf(arqTxt, "X: %lf\n", getX(item));
                fprintf(arqTxt, "Y: %lf\n", getY(item));
                fprintf(arqTxt, "Widh: %lf\n", getW(item));
                fprintf(arqTxt, "Height: %lf\n", getH(item));
                fprintf(arqTxt, "Corb: %s\n", getCorb(item));
                fprintf(arqTxt, "Corp: %s\n\n", getCorp(item));
                *scoreInat = *scoreInat + getInativacao(item);
                remover(item);
            } else {
                fprintf(arqTxt, "Retangulo:\n");
                fprintf(arqTxt, "X: %lf\n", getX(item));
                fprintf(arqTxt, "Y: %lf\n", getY(item));
                fprintf(arqTxt, "Widh: %lf\n", getW(item));
                fprintf(arqTxt, "Height: %lf\n", getH(item));
                fprintf(arqTxt, "Corb: %s\n", getCorb(item));
                fprintf(arqTxt, "Corp: %s\n\n", getCorp(item));
            }
        }
    }
    else if (strcmp(getTipo(item), "c") == 0 && getProtecao(item) > 0) {
        verificador = insideIrradiation(x, y, w, h, 'c', item);
        if (verificador == 0) {

            raio = getR(item);
            red = (agress * (raio * raio * pi)) / (w * h);
            changeProtecao(item, red);

            svgAnchor(svg, getX(item), getY(item));

            if (getProtecao(item) <= 0) {
                fprintf(arqTxt, "Circulo REMOVIDA:\n");
                fprintf(arqTxt, "X: %lf\n", getX(item));
                fprintf(arqTxt, "Y: %lf\n", getY(item));
                fprintf(arqTxt, "Raio: %lf\n", getR(item));
                fprintf(arqTxt, "Corb: %s\n", getCorb(item));
                fprintf(arqTxt, "Corp: %s\n\n", getCorp(item));
                *scoreInat = *scoreInat + getInativacao(item);
                remover(item);
            } else {
                fprintf(arqTxt, "Circulo:\n");
                fprintf(arqTxt, "X: %lf\n", getX(item));
                fprintf(arqTxt, "Y: %lf\n", getY(item));
                fprintf(arqTxt, "Raio: %lf\n", getR(item));
                fprintf(arqTxt, "Corb: %s\n", getCorb(item));
                fprintf(arqTxt, "Corp: %s\n\n", getCorp(item));
            }

        }
    }
    else if (strcmp(getTipo(item), "l") == 0 && getProtecao(item) > 0) {
        verificador = insideIrradiation(x, y, w, h, 'l', item);
        if (verificador == 0) {
            red = (agress * (0.1 * getcomprimentolinha(item)) / ( w * h));
            changeProtecao(item, red);

            svgAnchor(svg, getX1(item), getY1(item));

            if (getProtecao(item) <= 0) {
                fprintf(arqTxt, "Linha REMOVIDA:\n");
                fprintf(arqTxt, "X1: %lf\n", getX1(item));
                fprintf(arqTxt, "Y1: %lf\n", getY1(item));
                fprintf(arqTxt, "X2: %lf\n", getX2(item));
                fprintf(arqTxt, "Y2: %lf\n", getY2(item));
                fprintf(arqTxt, "Cor: %s\n\n", getCorp(item));
                *scoreInat = *scoreInat + getInativacao(item);
                remover(item);
            } else {
                fprintf(arqTxt, "Linha:\n");
                fprintf(arqTxt, "X1: %lf\n", getX1(item));
                fprintf(arqTxt, "Y1: %lf\n", getY1(item));
                fprintf(arqTxt, "X2: %lf\n", getX2(item));
                fprintf(arqTxt, "Y2: %lf\n", getY2(item));
                fprintf(arqTxt, "Cor: %s\n\n", getCorp(item));
            }

        }
    }
    else if (strcmp(getTipo(item), "t") == 0 && getProtecao(item) > 0) {
        verificador = insideIrradiation(x, y, w, h, 't', item);
        if (verificador == 0) {
            red = (agress * 0.1) / (w * h);
            changeProtecao(item, red);

            if (strcmp(getAncora(item), "i") == 0) {
                svgAnchor(svg, getX(item), getY(item));
            } else if (strcmp(getAncora(item), "m") == 0) {
                svgAnchor(svg, (getX(item)+(getTextSize(item)/2)), getY(item));
            } else {
                svgAnchor(svg, (getX(item)+getTextSize(item)), getY(item));
            }
            
            if (getProtecao(item) <= 0) {
                fprintf(arqTxt, "Texto REMOVIDA:\n");
                fprintf(arqTxt, "X: %lf\n", getX(item));
                fprintf(arqTxt, "Y: %lf\n", getY(item));
                fprintf(arqTxt, "Ancora: %s\n", getAncora(item));
                fprintf(arqTxt, "Corb: %s\n", getCorb(item));
                fprintf(arqTxt, "Corp: %s\n", getCorp(item));
                fprintf(arqTxt, "Valor: %s\n\n", getText(item));
                *scoreInat = *scoreInat + getInativacao(item);
                remover(item);
            } else {
                fprintf(arqTxt, "Texto:\n");
                fprintf(arqTxt, "X: %lf\n", getX(item));
                fprintf(arqTxt, "Y: %lf\n", getY(item));
                fprintf(arqTxt, "Ancora: %s\n", getAncora(item));
                fprintf(arqTxt, "Corb: %s\n", getCorb(item));
                fprintf(arqTxt, "Corp: %s\n", getCorp(item));
                fprintf(arqTxt, "Valor: %s\n\n", getText(item));
            }
        }
    }

    // recursão
    funcaoBE(getEsquerda(no), svg, arqTxt, x, y, w, h, agress, scoreInat);
    funcaoBE(getMeio(no), svg, arqTxt, x, y, w, h, agress, scoreInat);
    funcaoBE(getDireita(no), svg, arqTxt, x, y, w, h, agress, scoreInat);


}

int rectInside(float x, float y, Item rect) {

    if (x >= getX(rect) && x <= getX(rect) + getW(rect)) {
        if (y >= getY(rect) && y <= getY(rect) + getH(rect)) {
            return 0;   // retorna 0 se estiver dentro do retangulo
        }
        else {
            return 1;   // retorna 1 se estiver fora do retangulo
        }
    }
    else
        return 1;
}

int circInside(float x, float y, Item circ) {

    if (getX(circ) - getR(circ) <= x && getX(circ) + getR(circ) >= x) {
        if (getY(circ) - getR(circ) <= y && getY(circ) + getR(circ) >= y) {
            return 0;   // retorna 0 se estiver dentro do circulo
        }
        else {
            return 1;   // retorna 1 se estiver fora do circulo
        }
    }
    else {
        return 1;
    }
}

int lineInside(float x, float y, Item line) {

    if (getX1(line) == x || getX2(line) == x || getY1(line) == y || getY2(line) == y) {
        return 0;
    }
    else
        return 1;

}

int textInside(float x, float y, Item text) {

    if (getX(text) == x && getY(text) == y)
        return 0;
    else
        return 1;
}

int insideIrradiation(float x, float y, float w, float h, char type, Item item) {
    if (type == 't') {
        if (getX(item) >= x && getX(item) <= w && getY(item) >= y && getY(item) <= h)
            return 0;
        else
            return 1;
    } else if (type == 'l') {
        /* printf("X: %f >= X1: %f && W: %f <= X2: %f \n", x, getX1(item), w, getX2(item));
        printf("Y: %f >= Y1: %f && H: %f <= Y2: %f \n\n", y, getY1(item), w, getY2(item));
 */        if (getX1(item) >= x && getX1(item) <= w 
                && getY1(item) >= y && getY1(item) <= h 
                && getX2(item) >= x && getX2(item) <= w 
                && getY2(item) >= y && getY2(item) <= h ) {
            return 0;
        }
        else
            return 1;
    } else if (type == 'c') {
        if (x >= getX(item)+getR(item) && w <= getX(item)+getR(item)
            && y >= getY(item)+getR(item) && h <= getY(item)+getR(item)) {
            return 0;
        } else {
            return 0;
        }
    }
    else {
        if (getX(item) >= x && getX(item) + getW(item) <= x+w
            && getY(item) >= y && getY(item) + getH(item)<= y+h) {
            return 0;
        }
        else
            return 1;
    }
}