#ifndef lista_h
#define lista_h 

typedef void* List;
typedef void* Cell;
typedef void* Item;

List criaLista();                       // cria uma lista vazia  
void inserirLista(List L, Item info);   // insere um elemento no fim da lista
void RemoveElemento(List L, Cell C);    // remove a célula passada de parâmetro 
Cell getInicio(List L);                 // retorna a primeira célula da lista
Cell getNext(Cell C);                   // retorna a próxima celula da célula passada de parâmetro
Cell getPrevious(Cell C);               // retorna a célula anterior à célula passada de parâmetro
Cell getLast(List L);                   // retorna a última célula da lista
Item getItem(Cell C);                   // retorna o item contido na célula passada de parâmetro
void liberaLista(List lista);           // percorre toda a lista e libera todas as células e, ao fim, a lista

#endif