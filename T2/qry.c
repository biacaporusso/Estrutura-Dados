#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "yxxtree.h"
#include "figuras.h"
#include "parametros.h"
#include "lista.h"
#include "paramqry.h"
#include "svg.h"
#include "fila.h"

bool figuraDentro(Info i, double x1, double y1 , double x2, double y2) {

    // retangulo
    if (strcmp(getTipo(i), "r") == 0) {
        if (getX(i) >= x1 && getX(i)+getW(i) <= x2) {
            if (getY(i) >= y1 && getY(i)+getH(i) <= y2) {
	        //printf("***** RETANGULO DENTRO DA REGIAO ****\n*******\n");
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    // circulo
    if (strcmp(getTipo(i), "c") == 0) {
        if (getX(i)-getR(i) >= x1 && getX(i)+getR(i) <= x2) {
            if (getY(i)-getR(i) >= y1 && getY(i)+getR(i) <= y2) {
	        //printf("***** CIRCULO DENTRO DA REGIAO ****\n*******\n");
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    // linha
    if (strcmp(getTipo(i), "l") == 0) {
        if (x2 >= getX1(i) && y2 >= getY1(i)) {
            if (x2 >= getX2(i) && y2 >= getY2(i)) {
                if (x1 <= getX1(i) && y1 <= getY1(i) && x1 <= getX2(i) && y1 <= getY2(i)) {
		        //  printf("***** LINHA DENTRO DA REGIAO ****\n*******\n");
                    return true;
                }
            }
        }
        return false;
    }

    // texto
    if (strcmp(getTipo(i), "t") == 0) {
        if (getX(i) >= x1 && getX(i) <= x2) {
            if (getY(i) >= y1 && getY(i) <= y2) {
	            //printf("***** TEXTO DENTRO DA REGIAO ****\n*******\n");
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return false;
}

void interpretandoQry(FILE *qryFile, YxxTree arvore, FILE *svg, FILE *arqTxt) {
    char comando[500], corb[30], corp[30], id[10];
    int n, idINP;
    float d, e, x, y, w, h, dx, dy;

    Fila_Circular fila = criaFila(200);
    void* param = createParamQry();
    setSvg(svg, param);
    setTxt(arqTxt, param);
    setArv(arvore, param);
    setFila(fila, param);

    while (fscanf(qryFile, "%s", comando) != EOF) {

        if (!strcmp(comando, "inp")) {

            fscanf(qryFile, "%d", &idINP);
            setId(idINP, param);
            fprintf(arqTxt, "\n[*] inp %d\n", idINP);
            visitaProfundidadeYxxT(arvore, funcaoINP, param);

        }
        else if (!strcmp(comando, "rmp")) {

            funcaoRMP(fila, arqTxt);
        }
        else if (!strcmp(comando, "pol")) {

            fscanf(qryFile, "%s %f %f %s %s", id, &d, &e, corb, corp);
            funcaoPOL(atoi(id), d, e, corb, corp, svg, arqTxt, arvore, fila);

        }
        else if (!strcmp(comando, "clp")) {

            funcaoCLP(fila, arqTxt);

        }
        else if (!strcmp(comando, "sel")) {

            fscanf(qryFile, "%f %f %f %f", &x, &y, &w, &h);

            fprintf(arqTxt, "\n[*] sel %f %f %f %f\n", x, y, w, h);
            fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" fill-opacity=\"0.1\" stroke=\"red\" stroke-dasharray=\"5\"/>", x, y, w, h);
            setXsel(x, param);
            setYsel(y, param);
            setWsel(w, param);
            setHsel(h, param);
            List selecionados = getInfosDentroRegiaoYxxT(arvore, x, y, x+w, y+h, figuraDentro);
            setListasel(selecionados, param);
	        funcaoSEL(param);
            
        }
        else if (!strcmp(comando, "sel+")) {

            fscanf(qryFile, "%f %f %f %f", &x, &y, &w, &h);
            fprintf(arqTxt, "\n[*] sel+ %f %f %f %f\n", x, y, w, h);
            fprintf(svg, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"white\" fill-opacity=\"0.1\" stroke=\"red\" stroke-dasharray=\"5\"/>", x, y, w, h);
            setXsel(x, param);
            setYsel(y, param);
            setWsel(w, param);
            setHsel(h, param);
            List selecionadosPlus = getInfosDentroRegiaoYxxT(arvore, x, y, x+w, y+h, figuraDentro);
            setListasel(selecionadosPlus, param);
            //appendListasel(selecionados, param);
            funcaoSELplus(param);
           
        }
        else if (!strcmp(comando, "dels")) {

            fprintf(arqTxt, "\n[*] dels\n");
            void* selecionados = getListasel(param);
            funcaoDELS(arvore, arqTxt, selecionados);

        }
        else if (!strcmp(comando, "dps")) {

            fscanf(qryFile, "%s %f %f %s %s", id, &dx, &dy, corb, corp);
            fprintf(arqTxt, "\n[*] dps %s %f %f %s %s\n", id, dx, dy, corb, corp);
            setDx(dx, param);
            setDy(dy, param);
            setCorbQry(corb, param); 
            setCorpQry(corp, param);
            setId(atoi(id), param);
            funcaoDPS(arvore, param);

        }
        else if (!strcmp(comando, "ups")) {

            fscanf(qryFile, "%s %s %f %f %d", corb, corp, &dx, &dy, &n);
            fprintf(arqTxt, "\n[*] ups %s %s %f %f %d\n", corb, corp, dx, dy, n);
            setCorbQry(corb, param);
            setCorpQry(corp, param);
            setDx(dx, param);
            setDy(dy, param);
            setN(n, param);
            funcaoUPS(arvore, param);
        }
        strcpy(comando, " ");
    }
    // free(getListasel(param));
    dumpTree(arvore, getTxt(param));
    destroi_fila(fila);
    free(param);
}

void funcaoSEL(void *aux) {

    FILE* arqTxt = getTxt(aux);
    FILE* svg = getSvg(aux);
    char tipo[3];
    Item node;
    Node treeNode;
    List selecs = getListasel(aux);
    Info i;
    double x,y;
    
    for(node = getInicio(selecs); node != NULL ; node = getNext(node)){
      treeNode = getItem(node);
       i = getInfoYxxT(NULL,treeNode);
       getCoordXyyT(NULL,treeNode,&x,&y);
       //printf("****** funsel x: %f y:%f tipo: %s  *******\n",x,y,getTipo(i));
      strcpy(tipo, getTipo(i));
      fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", x, y);
      fprintf(arqTxt, "id %d: %s\n", getID(i), getTipo(i));
    }
}


void funcaoDELS(YxxTree arvore, FILE* arqTxt, List selecionados) {

    Cell cell = getInicio(selecionados);

    while(cell != NULL) {

        Node no = getItem(cell);
        Item item = getInfoYxxT(arvore, no);

        fprintf(arqTxt, "id: %d, x: %f, y: %f, cor borda: %s, cor preenchimento: %s\n", getID(item), getX(item), getY(item), getCorb(item), getCorp(item));
        removeNoYxxT(arvore, no);
        cell = getNext(cell);
    }
}

void funcaoDPS(YxxTree arvore, void *aux) {
    FILE *arqTxt = getSvg(aux);
    float dx = getDx(aux);
    float dy = getDy(aux);
    int id = getID(aux);
    char corb[20], corp[20];
    strcpy(corb, getCorbQry(aux));
    strcpy(corp, getCorpQry(aux));
    List selecionados = getListasel(aux);

    Cell cell = getInicio(selecionados);
    while(cell != NULL) {

        //void* item = getItem(cell);
        Node no = getItem(cell);
        Item item = getInfoYxxT(arvore, no);

        if(strcmp(getTipo(item), "r") == 0) {

            Info rect = criarFig("r", id, getX(item)+dx, 99999, 99999, getY(item)+dy, 99999, 99999, 99999, getW(item), getH(item), corb, corp, NULL, NULL);
            insertYxxT(arvore, getX(rect), getY(rect), rect);
            fprintf(arqTxt, "retangulo %d criado, ancora em (%f, %f)\n", id, getX(item)+dx, getY(item)+dy);
            id++;
            setId(id, aux);

        } else if(strcmp(getTipo(item), "c") == 0) {

            Info circ = criarFig("c", id, getX(item)+dx, 99999, 99999, getY(item)+dy, 99999, 99999, getR(item), 99999, 99999, corb, corp, NULL, NULL);
            insertYxxT(arvore, getX(circ), getY(circ), circ);
            fprintf(arqTxt, "circulo %d criado, ancora em (%f, %f)\n", id, getX(item)+dx, getY(item)+dy);
            id++;
            setId(id, aux);

        } else if(strcmp(getTipo(item), "l") == 0) {

            Info linha = criarFig("l", id, 99999, getX1(item)+dx, getX2(item)+dx, 99999, getY1(item)+dy, getY2(item)+dy, 99999, 99999, 99999, corb, corp, NULL, NULL);
            insertYxxT(arvore, getX1(linha), getY1(linha), linha);
            fprintf(arqTxt, "linha %d criado, ancora em (%f, %f)\n", id, getX1(item)+dx, getY1(item)+dy);
            id++;
            setId(id, aux);

        } else if(strcmp(getTipo(item), "t") == 0) {

            Info texto = criarFig("t", id, getX(item)+dx, 99999, 999999, getY(item)+dy, 99999, 99999, 99999, 99999, 99999, corb, corp, getText(item), getAncora(item));
            insertYxxT(arvore, getX(texto), getY(texto), texto);
            fprintf(arqTxt, "texto %d criado, ancora em (%f, %f)\n", id, getX(item)+dx, getY(item)+dy);
            id++;
            setId(id, aux);
        }
        cell = getNext(cell);
    }
}

void funcaoINP(Info i, double x, double y, void *aux) {
    FILE* arqTxt = getTxt(aux);
    FILE* svg = getSvg(aux);
    void* fila = getFila(aux);
    int id = getId(aux);
    Item ponto;
    float x1, y1;
    int idItem;

    idItem = getID(i);

    if(idItem == id) {

        // insere na fila as coordenadas do item dessa celula 
        if(strcmp(getTipo(i), "r")==0) {
            x1 = getX(i);
            y1 = getY(i);
            ponto = criaPonto(x1, y1);
            insereFila(fila, ponto);
            fprintf(arqTxt, "retangulo\nancora em (%f, %f)\nlargura: %f\naltura: %f\npreenchimento: %s\nborda: %s\n", getX(i), getY(i), getW(i), getH(i), getCorp(i), getCorb(i));
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
        } else if (strcmp(getTipo(i), "c")==0) {
            x1 = getX(i);
            y1 = getY(i);
            ponto = criaPonto(x1, y1);
            insereFila(fila, ponto);
            fprintf(arqTxt, "circulo\nancora em (%f, %f)\nraio: %f\npreenchimento: %s\nborda: %s\n", getX(i), getY(i), getR(i), getCorp(i), getCorb(i));
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
        } else if (strcmp(getTipo(i), "l")==0) {
            x1 = getX1(i);
            y1 = getY1(i);
            ponto = criaPonto(x1, y1);
            insereFila(fila, ponto);
            fprintf(arqTxt, "linha\n(x1, y1) = (%f, %f)\n(x2, y2) = (%f, %f)\ncor: %s\n", getX1(i), getY1(i), getX2(i), getY2(i), getCorp(i));
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
        } else if(strcmp(getTipo(i), "t")==0) {
            x1 = getX(i);
            y1 = getY(i);
            ponto = criaPonto(x1, y1);
            insereFila(fila, ponto);
            fprintf(arqTxt, "texto\nancora em (%f, %f)\npreenchimento: %s\nborda: %s\ntexto: %s\n", getX(i), getY(i), getCorp(i), getCorb(i), getText(i));
            fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", getXponto(ponto), getYponto(ponto));
        }
    } 
}


void funcaoRMP(Fila_Circular fila, FILE* arqTxt) {

    fprintf(arqTxt, "\n[*] rmp\n");
    removeDaFila(fila);

}

void funcaoPOL(int id, float d, float e, char corb[], char corp[], FILE* svg, FILE* arqTxt, YxxTree arvore, Fila_Circular fila) {

    fprintf(arqTxt, "\n[*] pol %d %f %f %s %s\n", id, d, e, corb, corp);
    int tamanho = getSize(fila);
    int aux=0, aux2=1;
    float menorY = 99999, maiorY = -1;
    float menorX = 99999, maiorX = -1;
    float x1, x2, y1, y2;
    Item p1, p2;
    Item linha;
    //Node no;

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
        insertYxxT(arvore, x1, y1, linha);

        fprintf(arqTxt, "linha criada para borda do poligono: id = %d, x1 = %f, y1 = %f, x2 = %f, y2 = %f, stroke = %s\n", id, x1, y1, x2, y2, corb);
        id++;
    
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
    insertYxxT(arvore, x1, y1, linha);

    fprintf(arqTxt, "linha criada para borda do poligono: id = %d, x1 = %f, y1 = %f, x2 = %f, y2 = %f, stroke = %s\n", id, x1, y1, x2, y2, corb);
    id++;

    float Nlinhas = (maiorY - menorY) / d;
    float cont = 0;

    while (cont <= Nlinhas) {
        //fprintf(txt, "Criada linha de preenchimento: x1 = %lf, y1 = %lf, x2 = %lf, y2 = %lf, stroke = %s\n", menorX, menorY, maiorX, menorY, corp);
        fprintf(svg, "\t<line id=\"%d\" x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"%f\" />\n", id, menorX, menorY, maiorX, menorY, corp, e);

        //id++;
        menorY = menorY + d;
        cont++;
    }

}
 
void funcaoCLP(Fila_Circular fila, FILE* arqTxt) {

    fprintf(arqTxt, "\n[*] clp\n");
    removeTudoFila(fila);

}

void funcaoSELplus(void *aux) {

    FILE* arqTxt = getTxt(aux);
    FILE* svg = getSvg(aux);
    char tipo[3];
    Item node;
    Node treeNode;
    List selecs = getListasel(aux);
    Info i;
    double x,y;
    
    for(node = getInicio(selecs); node != NULL ; node = getNext(node)){
        treeNode = getItem(node);
        i = getInfoYxxT(NULL,treeNode);
        getCoordXyyT(NULL,treeNode,&x,&y);
        strcpy(tipo, getTipo(i));
        fprintf(svg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"1.5\" fill=\"white\" fill-opacity=\"0.3\" stroke=\"red\"/>", x, y);
        fprintf(arqTxt, "id %d: %s\n", getID(i), getTipo(i));
    }
}

void funcaoUPS(YxxTree arvore, void *aux) {

    FILE* arqTxt = getTxt(aux);
    float dx = getDx(aux);
    float dy = getDy(aux);
    int n = getN(aux);
    char corb[20], corp[20];
    strcpy(corb, getCorbQry(aux));
    strcpy(corp, getCorpQry(aux));
    List selecionados = getListasel(aux);

    int i=0;
    Cell celula = getLast(selecionados);
    //Item item;
    char tipo[2];

    while (celula != NULL && i != n) {
        
        Node no = getItem(celula);
        Item item = getInfoYxxT(arvore, no);
        //item = getItem(celula);
        strcpy(tipo, getTipo(item));


        if(strcmp(getTipo(item), "r") == 0) { 
            i--;
            changeX(item, getX(item)+dx);
            changeY(item, getY(item)+dy);
            changeBorda(item, corb);
            changePreench(item, corp);
            fprintf(arqTxt, "retangulo %d alterado. Novos valores: x,y = %f, %f borda: %s preenchimento: %s\n", getID(item), getX(item), getY(item), getCorb(item), getCorp(item));

        } else if(strcmp(getTipo(item), "c") == 0) {
            i--;
            changeX(item, getX(item)+dx);
            changeY(item, getY(item)+dy);
            changeBorda(item, corb);
            changePreench(item, corp);
            fprintf(arqTxt, "circulo %d alterado. Novos valores: x,y = %f, %f borda: %s preenchimento: %s\n", getID(item), getX(item), getY(item), getCorb(item), getCorp(item));

        } else if(strcmp(getTipo(item), "l") == 0) {
            i--;
            changeX1(item, getX1(item)+dx);
            changeY1(item, getY1(item)+dy);
            changeX2(item, getX2(item)+dx);
            changeY2(item, getY2(item)+dy);
            changeBorda(item, corb);
            changePreench(item, corp);
            fprintf(arqTxt, "linha %d alterada. Novos valores: x1,y1 = %f, %f x2,y2 = %f, %f borda: %s preenchimento: %s\n", getID(item), getX1(item), getY1(item), getX2(item), getY2(item), getCorb(item), getCorp(item));
    
        } else if(strcmp(getTipo(item), "t") == 0) {
            i--;
            changeX(item, getX(item)+dx);
            changeY(item, getY(item)+dy);
            changeBorda(item, corb);
            changePreench(item, corp);
            fprintf(arqTxt, "texto %d alterado. Novos valores: x,y = %f, %f borda: %s preenchimento: %s\n", getID(item), getX(item), getY(item), getCorb(item), getCorp(item));

        }
        celula = getPrevious(celula);
    }
}


