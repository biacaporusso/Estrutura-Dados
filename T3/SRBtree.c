#include "SRBtree.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "figures.h"

#define RED 0
#define BLACK 1

// estrutura nó
typedef struct no {
    Info info;                         // figuras
    double ch1, ch2;                   // ancora do nó
    int color;                         // cor do nó
    double x1, y1, x2, y2;             // MBB da figura
    double xs1, ys1, xs2, ys2;         // MBB da subarvore
    struct no *left, *right, *father;  // ponteiros
} No;

// estrutura árvore com um ponteiro para um nó
typedef struct {
    No *root;
    No *nil;
    int size;
    double epsilon;
} arvRB;

// -------------------------------------------------------------
void rbInsert(SRbTree T, Info info);
void leftRotate(SRbTree T, Node N);
void rightRotate(SRbTree T, Node N);
void fixupTree(SRbTree T, Node Z);
Node getRoot(SRbTree T);
void printTree(Node N);
void corrigeMbbSubArv(Node N);
// FUNÇÕES OBRIGATÓRIAS DO .h

SRbTree createSRb(double epsilon) {
    arvRB *tree;
    tree = (arvRB *)malloc(sizeof(arvRB));
    tree->root = NULL;
    tree->size = 0;
    tree->nil = calloc(1, sizeof(No));
    tree->nil->color = 1;
    tree->epsilon = epsilon;

    return (tree);
}

// ======================================================================================================================================
// ======================================================================================================================================

// FUNÇÕES AUXILIARES
// acessando a cor de um nó
int nodeColor(Node N) {
    No *no = (No *)N;
    if (no == NULL)
        return BLACK;
    else
        return no->color;
}
// inverte a cor do pai e de seus filhos
// É uma operação "administrativa": não altera a estrutura ou conteúdo da árvore
void changeColor(Node N) {
    No *no = (No *)N;
    no->color = !no->color;

    if (no->left != NULL) {
        no->left->color = !no->left->color;
    }

    if (no->right != NULL) {
        no->right->color = !no->right->color;
    }
}

Node getNode(Node N, double x, double y, double epsilon) {
    No *raiz = N;

    if (raiz == NULL) {
        return NULL;
    }
    if (fabs(raiz->ch1 - x) <= epsilon && fabs(raiz->ch2 - y) <= epsilon) {
        return raiz;
    }
    if (x < raiz->ch1 || (x == raiz->ch1 && y < raiz->ch2)) {
        return getNode(raiz->left, x, y, epsilon);
    } else {
        return getNode(raiz->right, x, y, epsilon);
    }
}

Node getNodeSRb(SRbTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2) {
    arvRB *tree = (arvRB *)t;

    return getNode(tree->root, xa, ya, tree->epsilon);
}

Node insertTeste(SRbTree T, Node N, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info);

void RBtransplant(SRbTree T, Node U, Node V) {
    arvRB *tree = (arvRB *)T;
    No *u = (No *)U;
    No *v = (No *)V;

    if (u->father == NULL) {
        tree->root = v;
    } else if (u == u->father->left) {
        u->father->left = v;
    } else {
        u->father->right = v;
    }
    if(v != NULL)
        v->father = u->father;
}

Info getInfoSRb(SRbTree t, Node n, double *xa, double *ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2) {
    No* no = (No*) n;

    return no->info;
}

void removeSRbaux(SRbTree T, Node Z);

Info removeSRb(SRbTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2) {
    arvRB* tree = (arvRB*) t;
    No* noRemovido = getNodeSRb(tree, xa, ya, mbbX1, mbbY1, mbbX2, mbbY2);
    Info infoRemovida = getInfoSRb(tree, noRemovido, &xa, &ya, mbbX1, mbbY1, mbbX2, mbbY2);
    removeSRbaux(tree, noRemovido);
    return infoRemovida;
}

Node treeMinimum(Node N) {
    No* no = (No*) N;

    while (no->left != NULL) {
        no = no->left;
    }
    return no;
}

void RbDeleteFixup(SRbTree T, Node X) {
    arvRB* tree = (arvRB*) T;
    No* x = (No*) X;
    No* w;

    while(x != tree->root && x->color == 1) {
        if (x == x->father->left) {
            w = x->father->right;
            if (w->color == 0) {
                w->color = 1;
                x->father->color = 0;
                leftRotate(tree, x->father);
                w = x->father->right;
            }
            if (w->left->color == 1 && w->right->color ==1) {
                w->color = 0;
                x = x->father;
            } else if (w->right->color == 1) {
                w->left->color = 1;
                w->color = 0;
                rightRotate(tree, w);
                w = x->father->right;
            }
            w->color = x->father->color;
            x->father->color = 1;
            w->right->color = 1;
            leftRotate(tree, x->father);
            x = tree->root;
        } else {
            w = x->father->left;
            if (w->color == 0) {
                w->color = 1;
                x->father->color = 0;
                rightRotate(tree, x->father);
                w = x->father->left;
            }
            if (w->right->color == 1 && w->left->color ==1) {
                w->color = 0;
                x = x->father;
            } else if (w->left->color == 1) {
                w->right->color = 1;
                w->color = 0;
                leftRotate(tree, w);
                w = x->father->left;
            }
            w->color = x->father->color;
            x->father->color = 1;
            w->left->color = 1;
            rightRotate(tree, x->father);
            x = tree->root;
        }
    }
    x->color = 1;
}

void removeSRbaux(SRbTree T, Node Z) {
    arvRB *tree = (arvRB *)T;
    No *z = (No *)Z;
    No *x;
    No *y = z;
    int originalColor = y->color;
    if (z->left == NULL) {
        x = z->right;
        RBtransplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        RBtransplant(tree, z, z->left);
    } else {
        y = treeMinimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->father == z) {
            if (x != NULL)
                x->father = y;
        } else {
            RBtransplant(tree, y, y->right);
            y->right = z->right;
            y->right->father = y;
        }
        RBtransplant(tree, z, y);
        y->left = z->left;
        y->left->father = y;
        y->color = z->color;
    }
    if (originalColor == 1) {
        if (x !=NULL)
            RbDeleteFixup(tree, x);
    }
}

Node insertSRb(SRbTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info) {
    arvRB* rb_tree = t;
    No* x1 = rb_tree->root;
    No* z = calloc(1, sizeof(No));
    z->info = info;
    z->ch1 = x;
    z->ch2 = y;
    z->x1 = mbbX1;
    z->x2 = mbbX2;
    z->y1 = mbbY1;
    z->y2 = mbbY2;
    No* y1 = NULL;

    while (x1) {
        y1 = x1;
        if (z->ch1 < x1->ch1 || (z->ch1 == x1->ch1 && z->ch2 < x1->ch2)) {
            x1 = x1->left;
        } else {
            x1 = x1->right;
        }
    }

    z->father = y1;
    if (!y1) {
        rb_tree->root = z;
    } else if (z->ch1 < y1->ch1 || (z->ch1 == y1->ch1 && z->ch2 < y1->ch2)) {
        y1->left = z;
    } else {
        y1->right = z;
    }

    z->color = 0;
    rb_tree->size++;
    //fixRBinsert(t, z);
    //fixTreeMBB(t, z);
    fixupTree(rb_tree, z);
    corrigeMbbSubArv(z);
    return z;
}

Node insertBbSRb(SRbTree t, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info) {

    return insertSRb(t, mbbX1, mbbY1, mbbX1, mbbY1, mbbX2, mbbY2, info);
}

Node insertTeste(SRbTree T, Node N, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info) {
    arvRB *tree = T;
    No *node = N;
    if (!node) {
        node = calloc(1, sizeof(No));
        node->info = info;
        node->ch1 = x;
        node->ch2 = y;
        node->x1 = mbbX1;
        node->x2 = mbbX2;
        node->y1 = mbbY1;
        node->y2 = mbbY2;
        if (!tree->root) {
            tree->root = node;
        }
        tree->size++;
        return node;
    }

    if (x < node->ch1 || (x == node->ch1 && y < node->ch2)) {
        node->left =
            insertTeste(T, node->left, x, y, mbbX1, mbbY1, mbbX2, mbbY2, info);
        node->left->father = node;

    } else {
        node->right =
            insertTeste(T, node->right, x, y, mbbX1, mbbY1, mbbX2, mbbY2, info);
        node->right->father = node;
    }

    return node;
}

void fixupTree(SRbTree t, Node n) {
    arvRB *rb_tree = t;
    No *z = n;
    No *y = NULL;

    while (z->father && z->father->color == 0) {
        // CASO A: pai de z é filho a esquerda do avô de z
        if (z->father == z->father->father->left) {
            y = z->father->father->right;

            // CASO 1A: o tio de z é vermelho, precisa recolorir
            if (y && y->color == 0) {
                z->father->color = 1;
                y->color = 1;

                z->father->father->color = 0;
                z = z->father->father;

            } else {
                // CASO 2A: tio preto, z é filho a direita de seu pai, precisa rotacionar para a esquerda
                if (z == z->father->right) {
                    z = z->father;
                    leftRotate(t, z);
                }
                // CASO 3A: tio preto, z é filho a esquerda de seu pai, precisa rotacionar para a direita
                z->father->color = 1;
                z->father->father->color = 0;
                rightRotate(t, z->father->father);
            }

            // CASO B: o pai de z é o filho direito do avô de z
        } else {
            if (z->father == z->father->father->right) {
                y = z->father->father->left;

                // CASO 1B: o tio de z é vermelho, precisa recolorir
                if (y && y->color == 0) {
                    z->father->color = 1;
                    y->color = 1;
                    z->father->father->color = 0;
                    z = z->father->father;
              
                } else {
                    // CASO 2B: tio preto, z é filho a esquerda de seu pai, precisa rotacionar para a direita
                    if (z == z->father->left) {
                        z = z->father;
                        rightRotate(t, z);
                    }

                    // CASO 3B: z é filho a direita de seu pai, precisa rotacionar para a esquerda
                    z->father->color = 1;
                    z->father->father->color = 0;
                    leftRotate(t, z->father->father);
                }
            }
        }
    }
    rb_tree->root->color = 1;
}

// rotação a esquerda
void leftRotate(SRbTree T, Node N) {
    arvRB *tree = (arvRB *)T;
    No *x = (No *)N;
    // No* y = (No*) malloc(sizeof(No));
    No *y = x->right;
    // y = x->right;

    x->right = y->left;
    if (y->left != NULL) {
        y->left->father = x;
    }
    y->father = x->father;
    if (x->father == NULL) {
        tree->root = y;
    } else if (x == x->father->left) {
        x->father->left = y;
    } else {
        x->father->right = y;
    }
    y->left = x;
    x->father = y;
}

// rotação a direita
void rightRotate(SRbTree T, Node N) {
    arvRB *tree = (arvRB *)T;
    No *x = (No *)N;
    No *y = x->left;

    x->left = y->right;
    if (y->right != NULL) {
        y->right->father = x;
    }
    y->father = x->father;
    if (x->father == NULL) {
        tree->root = y;
    } else if (x == x->father->right) {
        x->father->right = y;
    } else {
        x->father->left = y;
    }
    y->right = x;
    x->father = y;
}

Node getRoot(SRbTree T) {
    arvRB *t = T;
    return t->root;
}

void printTree(Node N) {
    No *node = N;

    if (!node) {
        return;
    }

    printf("NO %d %s\n", getID(node->info), node->color == 1 ? "Black" : "Red");
    if (node->left) {
        printf("Left %d %s\n", getID(node->left->info),
               node->left->color == 1 ? "Black" : "Red");
    }
    if (node->right) {
        printf("Right %d %s\n", getID(node->right->info),
               node->right->color == 1 ? "Black" : "Red");
    }

    printTree(node->left);
    printTree(node->right);
}

void makeNodes(Node n, FILE *dot);
void makeEdges(Node n, FILE *dot);

void printSRb(SRbTree T, char *nomeArq) {
    arvRB *t = T;
    FILE *arq = fopen(nomeArq, "w");

    fprintf(arq, "digraph G {");
    fprintf(arq, "\n\tnode [fontcolor=white style=filled]");
    fprintf(arq, "\n\tedge [fontcolor=grey fontsize=12]\n");

    // Declarando os nós
    makeNodes(t->root, arq);
    // Fazendo ligações das arestas
    makeEdges(t->root, arq);

    fprintf(arq, "\n}");
    fclose(arq);
}

void makeNodes(Node n, FILE *dot) {
    No *node = n;

    if (!node) {
        return;
    }

    if (node->color == 0) {
        fprintf(dot, "\tnode [fillcolor=red] %d\n", getID(node->info));
    }
    if (node->color == 1) {
        fprintf(dot, "\tnode [fillcolor=black] %d\n", getID(node->info));
    }

    makeNodes(node->left, dot);
    makeNodes(node->right, dot);
}

void makeEdges(Node n, FILE *dot) {
    No *node = n;

    if (!node) {
        return;
    }

    if (node->left) {
        fprintf(dot, "\t%d -> %d\n", getID(node->info),
                getID(node->left->info));
    }
    if (node->right) {
        fprintf(dot, "\t%d -> %d\n", getID(node->info),
                getID(node->right->info));
    }

    makeEdges(node->left, dot);
    makeEdges(node->right, dot);
}

void percursoProfundidadeAux(Node N, FvisitaNo f, void *aux) {
    No *no = (No *)N;
    if (no == NULL) {
        return;
    }

    f(no->info, no->ch1, no->ch2, no->x1, no->y1, no->x2, no->y2, aux);

    percursoProfundidadeAux(no->left, f, aux);
    percursoProfundidadeAux(no->right, f, aux);
}

void percursoProfundidade(SRbTree t, FvisitaNo f, void *aux) {
    arvRB *tree = (arvRB *)t;
    percursoProfundidadeAux(tree->root, f, aux);
}

void getMbbSub(Node N, double *x1, double *y1, double *x2, double *y2) {
    No *node = (No *)N;

    // se o nó é folha -> atribui mbb da figura
    if (node->left == NULL && node->right == NULL) {
        *x1 = node->x1;
        *y1 = node->y1;
        *x2 = node->x2;
        *y2 = node->y2;
    } else {  // senão -> atribui mbb da sub-arvore
        *x1 = node->xs1;
        *y1 = node->ys1;
        *x2 = node->xs2;
        *y2 = node->ys2;
    }
}

void uniteMBB(double x11, double y11, double x12, double y12, double x21, double y21, double x22, double y22, double *xr1, double *yr1, double *xr2, double *yr2) {
    *xr1 = (x11 < x21 ? x11 : x21);
    *xr2 = (x21 >= x22 ? x21 : x22);
    *yr1 = (y11 < y21 ? y11 : y21);
    *yr2 = (y12 >= y22 ? y12 : y22);
}

void corrigeMbbSubArv(Node N) {
    No *node = (No *)N;
    while (node != NULL) {
        // Calcula MBB da sub-arvore esquerda
        if (node->left != NULL) {
            getMbbSub(node->left, &node->xs1, &node->ys1, &node->xs2,
                      &node->ys2);
        } else {
            getMbbSub(node, &node->xs1, &node->ys1, &node->xs2, &node->ys2);
        }

        // Calcula MBB da sub-arvore direita
        if (node->right != NULL) {
            getMbbSub(node->right, &node->xs1, &node->ys1, &node->xs2,
                      &node->ys2);
        } else {
            getMbbSub(node, &node->xs1, &node->ys1, &node->xs2, &node->ys2);
        }

        uniteMBB(node->x1, node->y1, node->x2, node->y2, node->xs1, node->ys1,
                 node->xs2, node->ys2, &node->xs1, &node->ys1, &node->xs2,
                 &node->ys2);
        node = node->father;
    }
}


void getBbPartSRb_AUX (Node N, double x, double y, double w, double h, List result) {

    bool taDentro = true;
    No* no = (No*) N;

    // if rectangle has area 0, no overlap
    if (no->x1 == no->x2 || no->y1 == no->y2 || x+w == x || y+h == y) 
        taDentro = false;

    // If one rectangle is on left side of other
    if (no->x1 > x+w || x > no->x2)
        taDentro = false;
 
    // If one rectangle is above other
    if (no->y2 > y || y+h > no->x1)
        taDentro = false;

    if (taDentro == true) {
        inserirLista(result, no);
    }
    getBbPartSRb_AUX(no->left, x, y, w, h, result);
    getBbPartSRb_AUX(no->right, x, y, w, h, result);

}

void getBbPartSRb(SRbTree t, double x, double y, double w, double h, List resultado) { 

    arvRB* tree = (arvRB*) t;
    No* no = tree->root;

    getBbPartSRb_AUX(no, x, y, w, h, resultado);
}

void getBbSRb_AUX (Node N, double x, double y, double w, double h, List resultado) {

    No* no = (No*) N;

    if (no->x1 >= x && no->x2 <= x+w) {
        if (no->y1 >= y && no->y2 <= y+h) {
            inserirLista(resultado, no);
        } 
    }

    getBbSRb_AUX(no->left, x, y, w, h, resultado);
    getBbSRb_AUX(no->right, x, y, w, h, resultado);
}

void getBbSRb(SRbTree t, double x, double y, double w, double h, List resultado) {

    arvRB* tree = (arvRB*) t;
    No* no = tree->root;

    getBbSRb_AUX(no, x, y, w, h, resultado);
}

void updateInfoSRb(SRbTree t, Node n, Info i) {

    arvRB* tree = (arvRB*) t;
    No* no = (No*) n;
    removeSRb(tree, no->ch1, no->ch2, &no->x1, &no->y1, &no->x2, &no->y2);

    switch (getTipo(i)) {
        case 1: // círculo
            insertSRb(tree, getX(i), getY(i), getX(i)-getR(i), getY(i)-getR(i), getX(i)+getR(i), getY(i)+getR(i), i);
            break;
        
        case 2: // retangulo
            insertSRb(tree, getX(i), getY(i), getX(i), getY(i), getX(i)+getW(i), getY(i)+getH(i), i);
            break;
        
        case 3:
            insertSRb(tree, getX1(i), getY1(i), getX1(i), getY1(i), getX2(i), getY2(i), i);
            break;

        case 4:
            insertSRb(tree, getX(i), getY(i), getX(i), getY(i), getX(i), getY(i), i);
            break;
    }

}

int height(Node N) {
    No* node = (No*) N;
    if (node == NULL)
        return 0;
    else {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }

} 

void percursoLarguraAUX(Node N, FvisitaNo fVisita, void *aux, int i) {

    No* no = (No*) N;
    if (no == NULL)
        return;
    if (i == 1)
        fVisita(no->info, no->ch1, no->ch2, no->x1, no->y1, no->x2, no->y2, aux);
    else if (i > 1) {
        percursoLarguraAUX(no->left, fVisita, aux, i - 1);
        percursoLarguraAUX(no->right, fVisita, aux,  i - 1);
    }
}

void percursoLargura(SRbTree t, FvisitaNo fVisita, void *aux) {

    arvRB* tree = (arvRB*) t;
    int h = height(tree->root);
    int i;
    for (i = 1; i <= h; i++)
        percursoLarguraAUX(tree->root, fVisita, aux, i);

}

void percursoSimetricoAux(Node N, FvisitaNo f, void *aux) {

    No *no = (No *)N;
    if (no == NULL) {
        return;
    }

    percursoProfundidadeAux(no->left, f, aux);
    f(no->info, no->ch1, no->ch2, no->x1, no->y1, no->x2, no->y2, aux);
    percursoProfundidadeAux(no->right, f, aux);
}

void percursoSimetrico(SRbTree t, FvisitaNo fVisita, void *aux) {

    arvRB *tree = (arvRB *)t;
    percursoSimetricoAux(tree->root, fVisita, aux);

}

void freeTree(Node raiz) {

    No* no = (No*) raiz;
    if (no == NULL) {
        return;
    }
    if (no->info != NULL) {
        free(no->info);
    }
    freeTree(no->left);
    freeTree(no->right);

    if (no != NULL) {
        free(no);
    }
}

void killSRb(SRbTree t) {
    arvRB* tree = (arvRB*) t;
    freeTree(tree->root);
    free(tree->nil);
    free(tree);

}