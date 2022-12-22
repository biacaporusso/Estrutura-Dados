#include "digraph.h"
#include "list.h"
#include "qry.h"
#include "fila.h"

// typedef struct no {
//   int vertex;
//   struct node* next;
// }NodeLocal;
// struct node* createNode(int);

typedef struct Graph {
  int numVertices;
  List *adjacents;
  int tempo;
}graphLocal;

// // Cria no
// Node createNode(Node no,int v) {
//     NodeLocal *newNode;
//     newNode = malloc(sizeof(newNode));
//     newNode->vertex = v;
//     newNode->next = NULL;
//     return newNode;
// }

// Cria grafo
Digraph createGraph(int vertices) {
    graphLocal *graph = malloc(sizeof(graphLocal));

    graph->numVertices = vertices;
    graph->adjacents = malloc(vertices*sizeof(List));

    int i;
    for (i = 0; i < vertices; i++)
      graph->adjacents[i] = criaLista();

    return graph;
}

// Add aresta
Edge addEdge(Digraph g, Node from, Node to, InfoEdge info) {
    graphLocal *grafo = g;
    Edge e;
    if (grafo->adjacents[from] != NULL) {
      e = insertAresta(grafo->adjacents[from], info, from, to);
    }
    return e;
}

void setNodeName(Digraph g, Node n, char *nome) {
  graphLocal *grafo = g;
  setNomeVert(grafo->adjacents[n], nome);
}

void setNodeInfo(Digraph g, Node node, InfoNode info) {
  graphLocal *grafo = g;
  setInfoVert(grafo->adjacents[node], info);
}

InfoNode getNodeInfo(Digraph g, Node node) {
  graphLocal *grafo = g;
  return getInfoVert(grafo->adjacents[node]);
}

Node getFromNode(Digraph g, Edge e) {
  
  return getArestaFrom(e);
}

Node getToNode(Digraph g, Edge e) {
  
  return getArestaTo(e);
}

Node getNode(Digraph g,  char *nome){
  graphLocal *grafo = g;
  int i;
  for(i=0; i < grafo->numVertices; i++){
    if (strcmp(nome, getNomeVert(grafo->adjacents[i])) == 0){
      return i; 
    }
  }
  return -1;
  
}

Edge getEdge(Digraph g, Node from, Node to) {

  graphLocal* grafo = (graphLocal*) g;
  Edge aresta = searchEdge(grafo->adjacents[from], from, to);
  return aresta;
}

InfoEdge getEdgeInfo(Digraph g, Edge e) {
  InfoEdge info = getItem(e);
  return info;
  
}

int graphSize(Digraph g) {
  graphLocal* grafo = (graphLocal*) g;
  return grafo->numVertices;
}

void* adjacentEdges(Digraph g, Node node, List arestasAdjacentes) {
  graphLocal* grafo = (graphLocal*) g;
  return grafo->adjacents[node];
}

void adjacentNodes(Digraph g, Node node, List nosAdjacentes) {

  graphLocal* grafo = (graphLocal*) g;

  for(int i=0; i<grafo->numVertices; i++) {
    if (isAdjacent(grafo, node, i)) {
      insertAresta(nosAdjacentes, &i, 0, 0);
    }
  }
}

void  getNodeNames(Digraph g, List nomesNodes) {
  graphLocal* grafo = (graphLocal*) g;

  for(int i=0; i<grafo->numVertices; i++) {
      insertAresta(nomesNodes, getNomeVert(grafo->adjacents[i]), 0, 0);
  }
}

void getEdges(Digraph g, List arestas) {
  graphLocal* grafo = (graphLocal*) g;

  // vetor
  for(int i=0; i<grafo->numVertices; i++) {
    Edge aresta = getInicio(grafo->adjacents[i]);
    while(aresta != NULL) {
      insertAresta(arestas, getEdgeInfo(grafo, aresta), 0, 0);
      aresta = getNext(aresta);
    }
  }
}


Digraph cloneOnlyVertices(Digraph g, bool keepInfo) {

  graphLocal* grafoRef = (graphLocal*) g;
  graphLocal* novoGrafo = createGraph(grafoRef->numVertices);
  int tam = grafoRef->numVertices;
  for(int i=0; i<tam; i++) {

    InfoNode infoVert = getNodeInfo(grafoRef, i);
    setNodeName(novoGrafo, i, getNomeVert(grafoRef->adjacents[i]));
    if (keepInfo == true) {
      setNodeInfo(novoGrafo, i, infoVert);
    }
  }
  return novoGrafo;
}

Digraph cloneOnlyEnabled(Digraph g, bool keepInfo) {

  graphLocal* grafoRef = (graphLocal*) g;
  graphLocal* novoGrafo = createGraph(grafoRef->numVertices);
  int tam = grafoRef->numVertices;

  // primeiro for: clonando vértices
  for(int i=0; i<tam; i++) {

    InfoNode infoVert = getNodeInfo(grafoRef, i);
    setNodeName(novoGrafo, i, getNomeVert(grafoRef->adjacents[i]));
    setNodeInfo(novoGrafo, i, infoVert);
  }

  // segundo for: clonando arestas
  for(int i=0; i<tam; i++) {

    Edge aresta = getInicio(grafoRef->adjacents[0]);
    while(aresta != NULL) {
      if (getStatusAresta(aresta) == true) {
        InfoEdge infoAresta = getEdgeInfo(grafoRef, aresta);
        if(keepInfo == true)
          addEdge(novoGrafo, getArestaFrom(aresta), getArestaTo(aresta), infoAresta);
        else  
          addEdge(novoGrafo, getArestaFrom(aresta), getArestaTo(aresta), NULL);
      }
      aresta = getNext(aresta);
    }
  }
  return novoGrafo;
}

Digraph cloneAll(Digraph g, bool keepInfo) {

  graphLocal* grafoRef = (graphLocal*) g;
  graphLocal* novoGrafo = createGraph(grafoRef->numVertices);
  int tam = grafoRef->numVertices;

  // primeiro for: clonando vértices
  for(int i=0; i<tam; i++) {

    InfoNode infoVert = getNodeInfo(grafoRef, i);
    setNodeName(novoGrafo, i, getNomeVert(grafoRef->adjacents[i]));
    setNodeInfo(novoGrafo, i, infoVert);
  }

  // segundo for: clonando arestas
  for(int i=0; i<tam; i++) {

    Edge aresta = getInicio(grafoRef->adjacents[0]);
    while(aresta != NULL) {
      InfoEdge infoAresta = getEdgeInfo(grafoRef, aresta);
      addEdge(novoGrafo, getArestaFrom(aresta), getArestaTo(aresta), infoAresta);
      aresta = getNext(aresta);
    }
  }
  return novoGrafo;
}

void setEdgeInfo(Digraph g, Edge e, InfoEdge info) {
  setInfoAresta(e, info);
}

void removeEdge(Digraph g, Edge e) {

  graphLocal* grafo = (graphLocal*) g;
  List lista = grafo->adjacents[getArestaFrom(e)];
  RemoveElemento(lista, e);
  
}

void disableEdge(Digraph g, Edge e) {
  
  setArestaDesativada(e);
}

void enableEdge(Digraph g, Edge e) {
  
  setArestaAtivada(e);
}

void enableAllEdges(Digraph g) {
  graphLocal* grafo = (graphLocal*) g;
  int i;
  for (i=0; i < grafo->numVertices; i++) {
    List vertice = adjacentEdges(grafo, i, NULL);
    Edge aresta = getInicio(vertice);
    while (aresta != NULL) {
      if(getStatusAresta(aresta) == false) {
        setArestaAtivada(aresta);
      }
      aresta = getNext(aresta);
    }
  }
} 

bool isDisabled(Digraph g, Edge e) {
  if (getStatusAresta(e) == false) {
    return true;
  }
  return false;
}

bool isAdjacent(Digraph g, Node from, Node to) {

  graphLocal* grafo = (graphLocal*) g;
  Edge aresta = getEdge(grafo, from, to);
  if (aresta != NULL) {
    return true;
  } else {
    return false;
  }
}

void dfsVisit(Digraph g, Node node, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, void* extra);

bool dfs(Digraph g, Node node, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra) {

  graphLocal* grafo = (graphLocal*) g;
  grafo->tempo = 0;
  for (int i=0; i<grafo->numVertices; i++) {

    List listaVertices = grafo->adjacents[i];
    setCorVertice(listaVertices, 'b');
  }
  for (int i=0; i<grafo->numVertices; i++) {
    if (getCorVertice(grafo->adjacents[i]) == 'b') {
      setNoFloresta(extra, i);
      newTree(grafo, extra);  
      dfsVisit(grafo, i, treeEdge, forwardEdge, returnEdge, crossEdge, extra);
    }
  }
  
  return false;
}


// no branco = aresta de árvore (treeEdge)
// no cinza = aresta de avanço (forwardEdge)
// no preto visitado depois do nó atual = aresta de retorno (returnEdge)

void dfsVisit(Digraph g, Node node, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, void* extra) {
  graphLocal* grafo = (graphLocal*) g;
  grafo->tempo++;
  List listaVertices = grafo->adjacents[node];
  setCorVertice(listaVertices, 'c');
  setTempoDescoberta(listaVertices, grafo->tempo);

  Edge aresta = getInicio(listaVertices);
  while(aresta != NULL) {
    Node vertAdj = getArestaTo(aresta); // v
    if(getCorVertice(grafo->adjacents[vertAdj]) == 'b') {
      treeEdge(grafo, aresta, getTempoDescoberta(listaVertices), getTempoFinalizacao(listaVertices), extra);
      dfsVisit(grafo, vertAdj, treeEdge, forwardEdge, returnEdge, crossEdge, extra);

    } else if(getCorVertice(grafo->adjacents[vertAdj]) == 'c') {
      forwardEdge(grafo, aresta, getTempoDescoberta(listaVertices), getTempoFinalizacao(listaVertices), extra);

    }  else if(getCorVertice(grafo->adjacents[vertAdj]) == 'p') {
      if(getTempoDescoberta(grafo->adjacents[node]) > getTempoDescoberta(grafo->adjacents[vertAdj])) 
        returnEdge(grafo, aresta, getTempoDescoberta(listaVertices), getTempoFinalizacao(listaVertices), extra);
      else
        crossEdge(grafo, aresta, getTempoDescoberta(listaVertices), getTempoFinalizacao(listaVertices), extra);

    }
    aresta = getNext(aresta);
  }
  grafo->tempo++;
  setCorVertice(listaVertices, 'p');
  setTempoFinalizacao(listaVertices, grafo->tempo);
}

bool bfs(Digraph g, Node node, procEdge discoverNode, void *extra) {

  graphLocal* grafo = (graphLocal*) g;
  for(int i=0; i<grafo->numVertices; i++) {

    List listaVertices = grafo->adjacents[i];
    setCorVertice(listaVertices, 'b');
    setDistancia(grafo->adjacents[i], -1);
  }

  setCorVertice(grafo->adjacents[node], 'c');
  setDistancia(grafo->adjacents[node], 0);

  Fila fila = criaFila();
  insereFila(fila, node);

  while(isEmpty(fila) == false) {

    Node u = removeFila(fila);
    List lista = grafo->adjacents[u];
    Edge aresta = getInicio(lista);

    while (aresta != NULL) {

      Node item = getArestaTo(aresta);
      if (getCorVertice(grafo->adjacents[item]) == 'b') {

        if (getEdge(grafo, u, item) != NULL) {

          discoverNode(grafo, getEdge(grafo, u, item), 0, 0, extra);
          setCorVertice(grafo->adjacents[item], 'c');
          setDistancia(grafo->adjacents[item], getDistancia(grafo->adjacents[u])+1);
          insereFila(fila, item);

        }

      }
      aresta = getNext(aresta);
    }
  }
  free(fila);
  return false;
  
}

void addVerticesNames(Digraph g, char *nomes[], int nNomes) {

  graphLocal* grafo = (graphLocal*) g;
  for (int i = 0; i < nNomes; i++) {
    setNomeVert(grafo->adjacents[i], nomes[i]);
  }

}

void freeGraph(Digraph g) {

  graphLocal* grafo = (graphLocal*) g;
  for(int i=0; i<grafo->numVertices; i++) {
    free(getNodeInfo(grafo, i));
    liberaLista(grafo->adjacents[i]);
  }

  free(grafo->adjacents);
  free(grafo);

}