#ifndef arvore_h
#define arvore_h 

typedef void* Tree;
typedef void* Node;
typedef void* Item;

Tree criaArvore();

/* insere uma informação na árvore (seja figura ou qualquer outra ED) 
e guarda os valores x, y passados de parâmetro, que vão servir para análise de 
esquerda, meio ou direita da árvore */
Node inserir(Tree T, Node N, Item info, double xFig, double yFig);

/* imprime a árvore inteira  */
void imprimir(Node N);

/* retorna o tamanho da árvore, ou seja, a quantidade de nós que ela possui */
int tamanho(Node N);

/* percorre a árvore inteira até encontrar a informação passada 
de parâmetro e retorna a informação desejada */
Item buscar(Node N, Item info);

/* remove da árvore o nó passado de parâmetro */
Node removeNo(Node N, Item info);

/* retorna o nó da raiz */
Node getRaiz(Tree T);

/* retorna a informação contida no nó passado de parâmetro */
Item getItem(Node N);

/* retorna o nó da esquerda ao nó passado de parâmetro */
Node getEsquerda(Node N);

/* retorna o nó do meio ao nó passado de parâmetro */
Node getMeio(Node N);

/* retorna o nó da direita ao nó passado de parâmetro */
Node getDireita(Node N);

/* desaloca da memória a árvore */
void liberaArv(Tree T);

#endif