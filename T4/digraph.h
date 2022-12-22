#ifndef _DIGRAPH__
#define _DIGRAPH__
#include "libs.h"
#include "list.h"

/*
Um Grafo Direcionado (Digraph) G é constituído por um conjunto de vértices V e 
um conjunto de arestas E, denotado por G=(V,E). 

Pode-se associar um dado (tipo Info) a arestas e a vertices de G.
Os nomes dos vértices são valores inteiros entre $0$ e |V|-1. É possível
associar nomes simbolicos a vertices e referencia-los através desses nomes.
Existem tres formas de fazer tal associacao: setNodeName associa explicitamente um nome a um no identificado
por seu numero; addVertex e addVertices associam nomes a vertices ainda nao nomeados (sem associacao explicita
ao seu numero).

Arestas de um grafo podem ser temporariamente desabilitadas. Uma aresta quando desabilitada parece ter 
sido removida (ou seja, parece nao existir no grafo). Porem, as informacoes associadas a tal aresta
sao mantidas (apesar de inacessiveis). Posteriormente, a aresta pode ser habilitada novamente, retornando
ao estado que estava antes da desabilitacao.

Um grafo pode ser clonado por meio de 3 operacoes: cloneOnlyVertices, cria um novo grafo contendo apenas copias dos
vertices do grafo original; cloneOnlyEnabled, clona os vertices e as arestas habilitadas (ou seja, o novo grafo nao
contem nenhuma aresta desabilitada); cloneAll, clona todos os vertices e arestas do grafo.

O modulo tambem oferece duas operacoes de percurso sobre o grafo: busca em largura (bfs) e busca em profundidade (dfs).
Estes percursos tem por parametros funcoes que sao invocadas quando arestas do grafo sao "descobertas"
durante o percurso. Caso alguma dessas funcoes retornar TRUE, o percurso é interrompido.
*/


/*
  "e" e' a aresta "descoberta"/"percorrida"/"classificada". td e' o tempo da descoberta (quando pintado de cinza).
  tf e' tempo de finalizacao (quando pintado de preto).
 */
typedef bool (*procEdge)(Digraph g, Edge e, int td, int tf, void *extra); 

typedef bool (*dfsRestarted)(Digraph g, void *extra);

/*
    Cria um grafo orientado contendo "nVert" vertices.
 */
Digraph createGraph(int nVert); // ok

/*
    Cria um novo grafo contendo apenas copias dos vertices de g.
    Caso o vertice original contenha uma informacao e keepInfo for TRUE, a informacao é
copiada para o novo vértice. 
 */
Digraph cloneOnlyVertices(Digraph g, bool keepInfo); // ok

/*
    Dado g=(V,E), produz G'=(V,E'), tal que, e'=(u,v) eh aresta de E', se e=(u,v) eh aresta de E
    e e esta' habilitada.
    Se keepInfo = TRUE, copia também as informaçoes associadas aos vertices e arestas clonados.
 */
Digraph cloneOnlyEnabled(Digraph g, bool keepInfo); // ok

/*
    Cria uma copia exata do grafo g.
    Se keepInfo = TRUE, copia também as informaçoes associadas aos vertices e arestas clonados
 */
Digraph cloneAll(Digraph g, bool keepInfo); // ok

/*
    Associa o nome "nome" ao vertice n. Substitui o nome pre-existente.
    O vertice n deve ser um vertice existente em G.
 */
void setNodeName(Digraph g, Node n, char *nome); // ok

/*
    Associa nNomes contidos no vetor nomes a vertices de g.
    nNomes deve ser menor ou igual ao numero de vertices do 
    grafo g (idealmente, deve ser igual)
 */
void addVerticesNames(Digraph g, char *nomes[], int nNomes); // ok

/*
    Retorna no' cujo de nome e' "nome". Retorna -1, caso o nao
    exista no com o nome especificado.
 */
Node getNode(Digraph g,  char *nome); // ok

/*
    Retorna informacao associada ao no' node.
    node deve ser um no' existente no grafo.
 */
InfoNode getNodeInfo(Digraph g, Node node); // ok

/*
    Atribui ao no' "node" a informacao "info"
 */
void setNodeInfo(Digraph g, Node node, InfoNode info); // ok

/*
    Adiciona a aresta (from,to) ao grafo. Atribui
    a informacao info `a aresta.
 */
Edge addEdge(Digraph g, Node from, Node to, InfoEdge info); // ok

/*
    Retorna a aresta (from,to). Se a aresta não existe,
    retorna NULL.
 */
Edge getEdge(Digraph g, Node from, Node to); // ok

/*
   Retorna o no' de origem na aresta "e".
 */
Node getFromNode(Digraph g, Edge e); // ok

/*
    Retorna o no' de destino da aresta "e".
 */  
Node getToNode(Digraph g, Edge e); // ok

/*
    Retorna a informacao associada 'a aresta "e".
    A informacao deve ter sido anteriormente associada 'a
    aresta pela operacao setEdgeInfo.
 */
InfoEdge getEdgeInfo(Digraph g, Edge e); // ok

/*
   Associa a informacao "info" 'a aresta "e".
 */
void setEdgeInfo(Digraph g, Edge e, InfoEdge info); // ok

/*
    Dado g=(V,E) tal que "e" pertence a E,
    retira "e" de E (E = E - {e}).
 */
void removeEdge(Digraph g, Edge e); // ok

/*
   Desabilita a aresta "e".
   A aresta "e" deve existir no grafo g.
 */
void disableEdge(Digraph g, Edge e); // ok

/*
   Reabilita a aresta "e" (que supostamente foi anteriormente
   desabilitada.
 */
void enableEdge(Digraph g, Edge e); // ok

/*
   Reabilita todas as aresta do grafo que, por ventura,
   tenham sido desabilitadas.
 */
void enableAllEdges(Digraph g); // ok

/*
   Retorna verdadeiro, se a aresta "e" esteja desabilitada;
   falso, caso contrario.
 */
bool isDisabled(Digraph g, Edge e); // ok

/*
   Retorna a quantidade 
   de nós do grafo
 */
int graphSize(Digraph g); // ok

/*
   Retorna verdadeiro se existe a aresta (from,to)
   no grafo g; falso, caso contrario.
 */
bool isAdjacent(Digraph g, Node from, Node to); // ok

/* 
   Adiciona 'a List "nosAdjacentes" os nos adjacentes ao no "node".
 */
void adjacentNodes(Digraph g, Node node, List nosAdjacentes); // ok

/*
   Adiciona 'a List "arestaAdjacentes" as arestas (x,y), tal que,
   x == node.
 */
void* adjacentEdges(Digraph g, Node node, List arestasAdjacentes); // ok

/*
   Insere na List "nomesNodes" os nomes atribuidos aos nos do grafo.
 */
void  getNodeNames(Digraph g, List nomesNodes); // ok

/*
   Insere na List "arestas", as arestas (Edge) do grafo g.
 */
void getEdges(Digraph g, List arestas); // ok

/*
   Faz percurso em profundidade sobre o grafo g, a partir do no' node, classificando 
   as arestas do grafo em aresta de arvore, aresta de avanco, de retorno e cruzada. 
   No momento da classificacao, a respectiva funcao e' invocada (caso nao seja NULL).
   "extra" e' um apontador que pode ser usado por qualquer uma das funcoes.
   A busca em profundidade, eventualmente, pode produzir uma floresta. Neste caso,
   a funçao newTree e' invocada sempre que o percurso for retomado.
 */  
bool dfs(Digraph g, Node node, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra); // ok

/*
   Percorre o grafo g em largura, a partir do no' node. Invoca a funcao discoverNode (se != NULL)
   para a aresta (x,y) usada para "descobrir" o no' y.
   "extra" e' um apontador que pode ser usado por qualquer uma das funcoes.
 */
bool bfs(Digraph g, Node node, procEdge discoverNode, void *extra); // ok

/*
   Libera a memória alocada pelo grafo
*/
void freeGraph(Digraph g); // ok

#endif