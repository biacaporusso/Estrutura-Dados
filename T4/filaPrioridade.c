#include "filaPrioridade.h"
#include "libs.h"

typedef struct node {

    struct node* next;
    struct node* prev;
    void* element;
    double priority;

} node;

typedef struct priority_queue {

    node* head;
    node* end;
    int size;

} priority_queue;

void* create_priority_queue() {

    priority_queue* new_priority_queue = malloc(sizeof(priority_queue));
    new_priority_queue->head = NULL;
    new_priority_queue->end = NULL;
    new_priority_queue->size = 0;
    return new_priority_queue;

}

void* priority_queue_insert(void* sequence, void* element, double priority) {

    priority_queue* priority_queue_aux = sequence;
    node* aux = calloc(1, sizeof(node));
    aux->priority = priority;
    aux->element = element;

    if (priority_queue_aux->size == 0) {

        aux->next = NULL;
        aux->prev = NULL;
        priority_queue_aux->head = aux;
        priority_queue_aux->end = aux;

    } else {

        node* runner = priority_queue_aux->head;

        if(runner->priority > aux->priority) { // Insert first on the start

            runner->prev = aux;
            aux->prev = NULL;
            aux->next = runner;
            priority_queue_aux->head = aux;

        } else {

            while(runner->priority < aux->priority) {
                if(runner->next != NULL) {
                    runner = runner->next;
                } else {
                    break;
                }
            } 
            
            if(runner->prev && runner->priority >= aux->priority){
                runner = runner->prev;
            }
            
            if(runner->next) {
                aux->next = runner->next;
                aux->prev = runner;
                runner->next->prev = aux;
                runner->next = aux;

            } else { // Last position
                
                runner->next = aux;
                aux->prev = runner;
                aux->next = NULL;
                priority_queue_aux->end = aux;

            }

        }

    }

    priority_queue_aux->size++;
    return aux;

}

int priority_queue_get_size(void* sequence) {
    
    priority_queue* priority_queue_aux = sequence;
    return priority_queue_aux->size;

}

void* priority_queue_get_head(void* sequence) {

    priority_queue* priority_queue_aux = sequence;
    return priority_queue_aux ? priority_queue_aux->head : NULL;

}

void priority_queue_free(void* sequence, bool remove_elements, void (*free_element)(void*)) {
    
    if(!sequence) return;

    priority_queue* priority_queue_aux = sequence;

    
    if (priority_queue_aux->size == 0) {

        free(sequence);
        return;

    }

    node* aux_node = priority_queue_aux->head;
    node* aux_element = priority_queue_aux->head->element;

    while (priority_queue_aux->head != NULL) {

        aux_node = priority_queue_aux->head;
        aux_element = priority_queue_aux->head->element;
        priority_queue_aux->head = priority_queue_aux->head->next;

        if(remove_elements == true) free_element(aux_element);

        free(aux_node);
    }

    free(sequence);
}

void* priority_queue_pop(void* sequence, bool remove_elements, void (*free_element)(void*)) {

    if(!sequence) return NULL;

    priority_queue* priority_queue_aux = sequence;
    
    if (priority_queue_aux->size > 1) {
        
        // Remove first element from priority_queue

        node* aux1 = priority_queue_aux->head->next;

        void* temp = priority_queue_aux->head->element;

        if(remove_elements) free_element(priority_queue_aux->head->element);

        free(priority_queue_aux->head);

        priority_queue_aux->head = aux1;
        priority_queue_aux->head->prev = NULL;
        priority_queue_aux->size--;

        return temp;

    } else if (priority_queue_aux->size == 1) {

        // Remove the only element of the priority_queue

        void* temp = priority_queue_aux->head->element;

        if(remove_elements) free_element(priority_queue_aux->head->element);

        free(priority_queue_aux->head);

        priority_queue_aux->head = NULL;
        priority_queue_aux->end = NULL;

        priority_queue_aux->size--;
        
        return temp;

    }

    return NULL;

}
 
void* priority_queue_get_element(void* current) {

    node* aux = current;
    return aux ? aux->element : NULL;

}

void* priority_queue_get_next(void* current) {
    
    node* aux = current;

    if (aux) return aux->next;

    return NULL;
}

void* priority_queue_get_previous(void* current) {
    
    node* aux = current;

    if (aux->prev) return aux->prev;

    return NULL;
}