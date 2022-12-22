#ifndef filaPrioridade_h
#define filaPrioridade_h
#include "libs.h"

void* create_priority_queue();
void* priority_queue_insert(void* sequence, void* element, double priority);
int priority_queue_get_size(void* sequence);
void* priority_queue_get_head(void* sequence);
void priority_queue_free(void* sequence, bool remove_elements, void (*free_element)(void*));
void* priority_queue_pop(void* sequence, bool remove_elements, void (*free_element)(void*));
void* priority_queue_get_element(void* current);
void* priority_queue_get_next(void* current);
void* priority_queue_get_previous(void* current);

#endif