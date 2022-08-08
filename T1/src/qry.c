#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "lista.h"
#include "figuras.h"
#include "parametros.h"
#include "svg.h"
#include "fila.h"

void interpretandoQry(FILE *qryFile, List lista, FILE *svg, FILE *arqTxt) {
    char comando[500], corb[30], corp[30], id[10];
    int n;
    float d, e, x, y, w, h, idINP, dx, dy;

    Fila_Circular fila = criaFila(200);

    while (fscanf(qryFile, "%s", comando) != EOF) {

        if (!strcmp(comando, "inp")) {

            fscanf(qryFile, "%f", &idINP);
            funcaoINP(lista, svg, arqTxt, idINP, fila);
        }
        else if (!strcmp(comando, "rmp")) {

            funcaoRMP(fila, arqTxt);
        }
        else if (!strcmp(comando, "pol")) {

            fscanf(qryFile, "%s %f %f %s %s", id, &d, &e, corb, corp);
            funcaoPOL(id, d, e, corb, corp, svg, arqTxt, lista, fila);
        }
        else if (!strcmp(comando, "clp")) {

            funcaoCLP(fila, arqTxt);
        }
        else if (!strcmp(comando, "sel")) {

            fscanf(qryFile, "%f %f %f %f", &x, &y, &w, &h);
            funcaoSEL(x, y, w, h, svg, arqTxt, lista);
        }
        else if (!strcmp(comando, "sel+")) {

            fscanf(qryFile, "%f %f %f %f", &x, &y, &w, &h);
            funcaoSELplus(x, y, w, h, svg, arqTxt, lista);
        }
        else if (!strcmp(comando, "dels")) {

            funcaoDELS(x, y, w, h, svg, arqTxt, lista);
        }
        else if (!strcmp(comando, "dps")) {

            fscanf(qryFile, "%s %f %f %s %s", id, &dx, &dy, corb, corp);
            funcaoDPS(lista, svg, arqTxt, id, dx, dy, corb, corp, x, y, w, h);
        }
        else if (!strcmp(comando, "ups")) {

            fscanf(qryFile, "%s %s %f %f %d", corb, corp, &dx, &dy, &n);
            funcaoUPS(corb, corp, dx, dy, n, lista, svg, arqTxt, x, y, w, h);
        }
    }
}

void funcaoINP(List lista, FILE* svg, FILE* arqTxt, float id, Fila_Circular fila) {

    // 1 passo: percorrer a lista procurando o item com o identificador passado de parametro
    fprintf(arqTxt, "\n[*] inp %f\n", id);
    Cell celula = getInicio(lista);
    Item item = getItem(celula);
    //Item ponto = NULL;
    Item ponto;
    float x, y;
    float idItem;

    while(celula != NULL) {

        item = getItem(celula);
        idItem = atof(getID(item));

        if(idItem == id) {

            // insere na fila as coordenadas do item dessa celula 
            if(strcmp(getTipo(item), "r")==0) {
                x = getX(item);
                y = getY(item);
                ponto = criaPonto(x, y);
                insereFila(fila, ponto);
                fprintf(arqTxt, "retangulo\nancora em (%f, %f)\nlargura: %f\naltura: %f\npreenchimento: %s\nborda: %s\n", getX(item), getY(item), getW(item), getH(item), getCorp(item), getCorb(item));
                fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
            } else if (strcmp(getTipo(item), "c")==0) {
                x = getX(item);
                y = getY(item);
                ponto = criaPonto(x, y);
                insereFila(fila, ponto);
                fprintf(arqTxt, "circulo\nancora em (%f, %f)\nraio: %f\npreenchimento: %s\nborda: %s\n", getX(item), getY(item), getR(item), getCorp(item), getCorb(item));
                fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
            } else if (strcmp(getTipo(item), "l")==0) {
                x = getX1(item);
                y = getY1(item);
                ponto = criaPonto(x, y);
                insereFila(fila, ponto);
                fprintf(arqTxt, "linha\n(x1, y1) = (%f, %f)\n(x2, y2) = (%f, %f)\ncor: %s\n", getX1(item), getY1(item), getX2(item), getY2(item), getCorp(item));
                fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
            } else if(strcmp(getTipo(item), "t")==0) {
                x = getX(item);
                y = getY(item);
                ponto = criaPonto(x, y);
                insereFila(fila, ponto);
                fprintf(arqTxt, "texto\nancora em (%f, %f)\npreenchimento: %s\nborda: %s\ntexto: %s\n", getX(item), getY(item), getCorp(item), getCorb(item), getText(item));
                fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
            }
        }
        celula = getNext(celula);
    }
}

void funcaoRMP(Fila_Circular fila, FILE* arqTxt) {

    fprintf(arqTxt, "\n[*] rmp\n");
    removeDaFila(fila);

}

void funcaoPOL(char id[], float d, float e, char corb[], char corp[], FILE* svg, FILE* arqTxt, List lista, Fila_Circular fila) {

    fprintf(arqTxt, "\n[*] pol %s %f %f %s %s\n", id, d, e, corb, corp);
    int tamanho = getSize(fila);
    int aux=0, aux2=1;
    float menorY = 99999, maiorY = -1;
    float menorX = 99999, maiorX = -1;
    float x1, x2, y1, y2;
    Item p1, p2;
    Item linha;
    float idFloat = atof(id);

    while (aux2 != tamanho) {

        p1 = getElement(fila, aux);   // 0 1 2
        p2 = getElement(fila, aux2);  // 1 2 3
        aux = aux2;
        aux2++;
        x1 = getXponto(p1);
        x2 = getXponto(p2);
        y1 = getYponto(p1);
        y2 = getYponto(p2);

        linha = criarFig("l", id, 99999, x1, x2, 99999, y1, y2, 99999, 99999, 99999, corb, corp, NULL, NULL);
        inserirLista(lista, linha);

        fprintf(arqTxt, "linha criada para borda do poligono: id = %f, x1 = %f, y1 = %f, x2 = %f, y2 = %f, stroke = %s\n", idFloat, x1, y1, x2, y2, corb);
        idFloat++;
    
        if (x1 < menorX) 
            menorX = x1;
        if (x2 < menorX) 
            menorX = x2;
        if (x1 > maiorX) 
            maiorX = x2;
        if (x2 > maiorX) 
            maiorX = x2;
        if (y1 < menorY) 
            menorY = y1;
        if (y2 < menorY) 
            menorY = y2;
        if (y1 > maiorY) 
            maiorY = y2;
        if (y2 > maiorY) 
            maiorY = y2;

    }
    
    p1 = getElement(fila, 0);
    x1 = getXponto(p1);
    y1 = getYponto(p1);

    linha = criarFig("l", id, 99999, x1, x2, 99999, y1, y2, 99999, 99999, 99999, corb, corp, NULL, NULL);
    inserirLista(lista, linha);

    fprintf(arqTxt, "linha criada para borda do poligono: id = %f, x1 = %f, y1 = %f, x2 = %f, y2 = %f, stroke = %s\n", idFloat, x1, y1, x2, y2, corb);
    idFloat++;

    float Nlinhas = (maiorY - menorY) / d;
    float cont = 0;

    while (cont <= Nlinhas) {
        //fprintf(txt, "Criada linha de preenchimento: x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, stroke = %s\n", menorX, menorY, maiorX, menorY, corp);
        fprintf(svg, "\t<line id=\"%s\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%f\" />\n", id, menorX, menorY, maiorX, menorY, corp, e);

        //id++;
        menorY = menorY + d;
        cont++;
    }

}
 
void funcaoCLP(Fila_Circular fila, FILE* arqTxt) {

    fprintf(arqTxt, "\n[*] clp\n");
    removeTudoFila(fila);
    //fprintf(txt, "coordenadas do poligono corrente: %f, %f\n", getXponto())
}

void funcaoSEL(double x, double y, double w, double h, FILE *svg, FILE *arqTxt, List lista) {

    fprintf(arqTxt, "\n[*] sel %f %f %f %f\n", x, y, w, h);
    Cell celula = getInicio(lista);
    Item item = getItem(celula);

    char tipo[2];
    int verificador;    // se verificador = 0 está dentro do retangulo , se = 1 não está dentro do retangulo

    while (celula != NULL) { // percorrer a lista toda

        item = getItem(celula);
        strcpy(tipo, getTipo(item));

        if(strcmp(tipo, "r") == 0) { 
            verificador = rectInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(tipo, "c") == 0) {
            verificador = circInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(tipo, "l") == 0) {
            verificador = lineInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(tipo, "t") == 0) {
            verificador = textInside(x, y, w, h, item, svg, arqTxt);
        }
        celula = getNext(celula);

        if(verificador == 0 && strcmp(tipo, "l") != 0) {
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getX(item), getY(item));
            fprintf(arqTxt, "id %s: %s\n", getID(item), getTipo(item));
        }
        if (verificador == 0 && strcmp(tipo, "l") == 0) {
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getX1(item), getY1(item));
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getX2(item), getY2(item));
            fprintf(arqTxt, "id %s: linha\n", getID(item));
        }

    }
    fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" fill-opacity=\"0.1\" stroke=\"red\" stroke-dasharray=\"5\"/>", x, y, w, h);
}

void funcaoSELplus(double x, double y, double w, double h, FILE *svg, FILE *arqTxt, List lista) {

    fprintf(arqTxt, "\n[*] sel+ %f %f %f %f\n", x, y, w, h);
    Cell celula = getInicio(lista);
    Item item = getItem(celula);

    char tipo[2];
    int verificador;    // se verificador = 0 está dentro do retangulo , se = 1 não está dentro do retangulo

    while (celula != NULL) { // percorrer a lista toda

        item = getItem(celula);
        strcpy(tipo, getTipo(item));

        if(strcmp(tipo, "r") == 0) { 
            verificador = rectInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(tipo, "c") == 0) {
            verificador = circInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(tipo, "l") == 0) {
            verificador = lineInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(tipo, "t") == 0) {
            verificador = textInside(x, y, w, h, item, svg, arqTxt);
        }
        celula = getNext(celula);

        if(verificador == 0 && strcmp(tipo, "l") != 0) {
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getX(item), getY(item));
            fprintf(arqTxt, "id %s: %s\n", getID(item), getTipo(item));
        }
        if (verificador == 0 && strcmp(tipo, "l") == 0) {
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getX1(item), getY1(item));
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getX2(item), getY2(item));
            fprintf(arqTxt, "id %s: linha\n", getID(item));
        }

    }
    fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" fill-opacity=\"0.1\" stroke=\"red\" stroke-dasharray=\"5\"/>", x, y, w, h);

}

void funcaoDELS(double x, double y, double w, double h, FILE *svg, FILE *arqTxt, List lista) {

    fprintf(arqTxt, "\n[*] dels\n");
    Cell celula = getInicio(lista);
    Item item = getItem(celula);
    int verificador;
    Cell celulaRemovida;

    while (celula != NULL) { // percorrer a lista toda
        item = getItem(celula);

        // se o item estiver dentro do retangulo passado de parametro, tem que removê-lo
        if(strcmp(getTipo(item), "r") == 0) { 
            verificador = rectInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(getTipo(item), "c") == 0) {
            verificador = circInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(getTipo(item), "l") == 0) {
            verificador = lineInside(x, y, w, h, item, svg, arqTxt);
        } else if(strcmp(getTipo(item), "t") == 0) {
            verificador = textInside(x, y, w, h, item, svg, arqTxt);
        }

        // se verificador = 0, significa que está dentro do retangulo, então nao copia a linha do svg dele
        if (verificador==0) {
            
            fprintf(arqTxt, "id: %s, x: %f, y: %f, cor borda: %s, cor preenchimento: %s\n", getID(item), getX(item), getY(item), getCorb(item), getCorp(item));
            celulaRemovida = celula;
            celula = getNext(celula);
            RemoveElemento(lista, celulaRemovida);
        } else {
            celula = getNext(celula);
        }
    }
}

void funcaoDPS(List lista, FILE* svg, FILE* arqTxt, char id[], float dx, float dy, char corb[], char corp[], double x, double y, double w, double h) {

    Cell celula = getInicio(lista);
    Item item = getItem(celula);
    float idFloat = atof(id);
    int verificador;

    fprintf(arqTxt, "\n[*] dps %s %f %f %s %s\n", id, dx, dy, corb, corp);

    while (celula != NULL) {

        item = getItem(celula);

        if(strcmp(getTipo(item), "r") == 0) { 
            verificador = rectInside(x, y, w, h, item, svg, arqTxt);
            if(verificador == 0) {

                fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(item)+dx, getY(item)+dy, getW(item), getH(item), corp, corb);
                fprintf(arqTxt, "retangulo %1.f criado, ancora em (%f, %f)\n", idFloat, getX(item)+dx, getY(item)+dy);
                idFloat++;
            }
        } else if(strcmp(getTipo(item), "c") == 0) {
            verificador = circInside(x, y, w, h, item, svg, arqTxt);
            if (verificador == 0) {

                fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX(item)+dx, getY(item)+dy, getR(item), corp, corb);
                fprintf(arqTxt, "circulo %1.f criado, ancora em (%f, %f)\n", idFloat, getX(item)+dx, getY(item)+dy);
                idFloat++;
            }
        } else if(strcmp(getTipo(item), "l") == 0) {
            verificador = lineInside(x, y, w, h, item, svg, arqTxt);
            if (verificador == 0) {

                fprintf(svg, "\n\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" fill=\"%s\" stroke=\"%s\"/>", getX1(item)+dx, getY1(item)+dy, getX2(item)+dx, getY2(item)+dy, corp, corb);
                fprintf(arqTxt, "linha %1.f criado, ancora em (%f, %f)\n", idFloat, getX(item)+dx, getY(item)+dy);
                idFloat++;
            }
        } else if(strcmp(getTipo(item), "t") == 0) {
            verificador = textInside(x, y, w, h, item, svg, arqTxt);
            if (verificador == 0) {

                fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\">%s</text>", getX(item)+dx, getY(item)+dy, corp, corb, getText(item));
                fprintf(arqTxt, "texto %1.f criado, ancora em (%f, %f)\n", idFloat, getX(item)+dx, getY(item)+dy);
                idFloat++;
            }
        }
        celula = getNext(celula);
    }
}

void funcaoUPS(char corb[], char corp[], float dx, float dy, int n, List lista, FILE* svg, FILE* arqTxt,double x, double y, double w, double h) {

    fprintf(arqTxt, "\n[*] ups %s %s %f %f %d\n", corb, corp, dx, dy, n);
    Cell celula = getLast(lista);
    Item item = getItem(celula);
    int verificador, i=0;

    while (celula != NULL && i != n) {

        item = getItem(celula);

        if(strcmp(getTipo(item), "r") == 0) { 
            verificador = rectInside(x, y, w, h, item, svg, arqTxt);
            if (verificador == 0) {     // figura está dentro então troca a cor
                i--;
                changeX(item, getX(item)+dx);
                changeY(item, getY(item)+dy);
                changeBorda(item, corb);
                changePreench(item, corp);
                fprintf(arqTxt, "retangulo %1.f alterado. Novos valores: x,y = %f, %f borda: %s preenchimento: %s\n", atof(getID(item)), getX(item), getY(item), getCorb(item), getCorp(item));
            }
        } else if(strcmp(getTipo(item), "c") == 0) {
            verificador = circInside(x, y, w, h, item, svg, arqTxt);
            if (verificador == 0) {     // figura está dentro então troca a cor
                i--;
                changeX(item, getX(item)+dx);
                changeY(item, getY(item)+dy);
                changeBorda(item, corb);
                changePreench(item, corp);
                fprintf(arqTxt, "circulo %1.f alterado. Novos valores: x,y = %f, %f borda: %s preenchimento: %s\n", atof(getID(item)), getX(item), getY(item), getCorb(item), getCorp(item));
            }
        } else if(strcmp(getTipo(item), "l") == 0) {
            verificador = lineInside(x, y, w, h, item, svg, arqTxt);
            if (verificador == 0) {     // figura está dentro então troca a cor
                i--;
                changeX1(item, getX1(item)+dx);
                changeY1(item, getY1(item)+dy);
                changeX2(item, getX2(item)+dx);
                changeY2(item, getY2(item)+dy);
                changeBorda(item, corb);
                changePreench(item, corp);
                fprintf(arqTxt, "linha %1.f alterada. Novos valores: x1,y1 = %f, %f x2,y2 = %f, %f borda: %s preenchimento: %s\n", atof(getID(item)), getX1(item), getY1(item), getX2(item), getY2(item), getCorb(item), getCorp(item));
            }
        } else if(strcmp(getTipo(item), "t") == 0) {
            verificador = textInside(x, y, w, h, item, svg, arqTxt);
            if (verificador == 0) {     // figura está dentro então troca a cor
                i--;
                changeX(item, getX(item)+dx);
                changeY(item, getY(item)+dy);
                changeBorda(item, corb);
                changePreench(item, corp);
                fprintf(arqTxt, "texto %1.f alterado. Novos valores: x,y = %f, %f borda: %s preenchimento: %s\n", atof(getID(item)), getX(item), getY(item), getCorb(item), getCorp(item));
            }
        }
        celula = getPrevious(celula);
    }
}

int rectInside(double x, double y, double w, double h, Item rect, FILE *svg, FILE* txt) {

    if (getX(rect) >= x) {
        if (getX(rect) + getW(rect) <= x+w) {
            if (getY(rect) >= y) {
                if (getY(rect) + getH(rect) <= y+h)     // se chegou até esse if é pq está dentro do retangulo
                    return 0;   // retorna 0 se estiver dentro do retangulo
                else
                    return 1;   // retorna 1 se estiver fora do retangulo
            } else  
                return 1;
        } else 
            return 1;
    } else 
        return 1;
}

int circInside(double x, double y, double w, double h, Item circ, FILE *svg, FILE* txt) {

    if (getX(circ) - getR(circ) >= x) {
        if (getX(circ) + getR(circ) <= x+w) {
            if (getY(circ) - getR(circ) >= y) {
                if (getY(circ) + getR(circ) <= y+h)     // se chegou até esse if é pq está dentro do retangulo
                    return 0;   // retorna 0 se estiver dentro do retangulo
                else
                    return 1;   // retorna 1 se estiver fora do retangulo
            } else  
                return 1;
        } else 
            return 1;
    } else 
        return 1;
}

int lineInside(double x, double y, double w, double h, Item line, FILE *svg, FILE* txt) {

    if (getX2(line) >= x) {
        if (getX1(line) <= x+w) {
            if (getY1(line) >= y) {
                if (getY2(line) <= y+h)     // se chegou até esse if é pq está dentro do retangulo
                    return 0;   // retorna 0 se estiver dentro do retangulo
                else
                    return 1;   // retorna 1 se estiver fora do retangulo
            } else 
                return 1;
        } else
            return 1;
    } else 
        return 1;
}

int textInside(double x, double y, double w, double h, Item text, FILE *svg, FILE* txt) {

    if (getX(text) >= x) {
        if (getX(text) <= x+w) {
            if (getY(text) >= y) {
                if (getY(text) <= y+h)     // se chegou até esse if é pq está dentro do retangulo
                    return 0;   // retorna 0 se estiver dentro do retangulo
                else
                    return 1;   // retorna 1 se estiver fora do retangulo
            } else  
                return 1;
        } else 
            return 1;
    } else 
        return 1;
}
