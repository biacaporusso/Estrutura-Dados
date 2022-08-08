#ifndef yxxtree_h
#define yxxtree_h 

#include "lista.h"
#include <stdio.h>
#include <stdbool.h>

/*
    Uma Arvore Yxx é uma arvore ternaria, espacial, nao balanceada. 
    A cada nó r da Arvore é associado um ponto de 2 dimensoes (r.x e r.y) denominado ancora 
    do nó e uma informacao relacionada tal ponto. 
    Um nó divide o plano em 3 regioes, associadas a tres subarvores:

     - sub-arvore esquerda (se) contem nos (d) cujas abscissas (d.x) sao estritamente
       menores que a abscissa de r, ou seja: d.x < r.x
     - sub-arvore mediana (sm): (d.x >= r.x) & (d.y < r.y)
     - sub-arvore direita (sd): (d.x >= r.x) & (d.y >= r.y)

    A arvore Yxx implementa 2 percursos: em largura e em profundidade. 
    Tais percursos recebem como parametro uma funcao que processa a 
    informacao associada ao nó visitado.

    Tambem sao providas operacoes de selecao espacial. 
    A primeira seleciona os nos da arvore cujas ancoras 
    sao internas a uma regiao retangular. 
    A segunda seleciona os nos da Arvore cujas informacoes associadas 
    podem ser consideradas internas a uma regiao retangular. 
    Esta operacao recebe por parametro uma funcao que decide se 
    tal informacao é considerada (ou nao) interna. 
    A terceira, similarmente, seleciona os nos da arvore cujo um dado 
    ponto é interno à informacao associada ao nó.

    Nos removidos nao sao desalocados imediatamente, mas apenas 
    marcados como delidos.
    Eventualmente, a arvore é re-criada sem os nós removidos. 
    Isto ocorre quando o fator de degradacao fd
        fd = #removidos/#total_nós > limiar. 
    Este limiar é definido no momento da criacao da arvore.
*/

typedef void* YxxTree;
typedef void* Node;
typedef void* Info;

typedef bool (*FdentroDe) (Info i, double x1, double y1 , double x2, double y2);
/*
 * Uma funcao deste tipo deve retornar verdadeiro se a informacao i esta'
 * "dentro" da regiao retangular delimitada pelos pontos opostos (x1,y1) e (x2,y2).
 * Retorna falso, caso contrario.
 */

typedef bool (*FatingidoPor) (Info i, double x, double y);
/*
    Uma funcao deste tipo deve retornar verdadeiro se o ponto (x,y) 
    deva ser considerado "interno" da informacao i.
*/

typedef void (*FvisitaNo) (Info i, double x, double y, void *aux);
/*
    Processa a informacao i associada a um nó da arvore, cuja ancora
    é o ponto (x,y). O parâmetro aux aponta para conjunto de dados 
    (provavelmente um registro) que sao compartilhados entre as 
    sucessivas invocacoes a esta funcao.
*/

YxxTree newYxxTree (double fd);                                                 // ok
/*
    Retorna uma arvore Yxx vazia com fator de degradacao fd.
    0 <= fd < 1.0
*/

Node insertYxxT (YxxTree T, double x, double y, Info i);                        // ok
/*
    Insere a informacao i, associada à ancora (x,y) na Arvore t.
    Retorna um indicador para o nó inserido.
*/

Node getNodeYxxT (YxxTree T, double x, double y, double epsilon);               // ok
/*
    Retorna o nó cuja ancora seja o ponto (x,y). Aceita-se uma pequena discrepância
    entre a coordenada da ancora (anc.x,anc.y) e o ponto (x,y) de epsilon unidades.
    Ou seja, |anc.x - x | < epsilon e |anc.y - y | < epsilon.
    Retorna NULL caso não tenha encontrado o nó.
*/

void removeNoYxxT (YxxTree T, Node N);
/*
    Marca como removido o nó n. Caso, apos a remocao, o fator de degradacao
    superar o limiar definido na criacao, a arvore é recriada sem os nós delidos.
*/

Info getInfoYxxT (YxxTree t, Node n);                                           // ok
/* Retorna a informacao associada ao nó n */

void getCoordXyyT (YxxTree t, Node n, double *x, double *y);
/* Retorna a coordenada associada ao no' n */

List getNodesDentroRegiaoYxxT (YxxTree t, double x1, double y1, double x2, double y2);  // ok
/* Retorna uma lista dos nos da arvore t cujas ancoras estao dentro da regiao delimitada pelos
   pontos (x1,y1) e (x2,y2) */

List getInfosDentroRegiaoYxxT (YxxTree t, double x1, double y1, double x2, double y2, FdentroDe f); // ok
/* Retorna um lista dos nos cujas respectivas informacoes associadas estao dentro da regiao
   delimitada pelos pontos (x1,y1) e (x2,y2). A funcao f é usada para determinar se uma informacao
   armazenada na arvore esta' dentro da regiao.
   Retorna uma lista vazia, caso não existam informacoes internas.
 */

void visitaProfundidadeYxxT (YxxTree t, FvisitaNo f, void *aux);                        // ok
/* 
    Percorre a arvore em profundidade. Invoca a funcao f em cada no visitado.
    O apontador aux é parametro em cada invocacao de f; assim alguns
    dados podem ser compartilhados entre as diversas invocacoes de f.
*/

void visitaLarguraYxxT (YxxTree t, FvisitaNo f, void *aux);                             // ok
/* Similar a visitaProfundidadeYxxT, porem, faz o percurso em largura. */


// desnecessaria
//List getInfosAtingidoPontoYxxT (YxxTree t, double x, double y, FatingidoPor f);
/* 
    Retorna uma lista dos nos para os quais o ponto (x,y) possa ser considerado
    interno às informacoes associadas ao nó. A funcao f é invocada para determinar
    se o ponto (x,y) é interno a uma informacao especifica.
*/

void dumpTree(YxxTree t, FILE* f);
/*
    Libera a memoria alocada pela arvore.
*/

#endif
