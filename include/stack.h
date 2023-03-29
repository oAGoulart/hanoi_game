/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef STACK_H
#define STACK_H 1

#include "base.h"
#include "list.h"

typedef struct list_s stacks_t;

void stack_create(stacks_t** self);
void stack_destroy(stacks_t** self);
void stack_push(stacks_t* self, void* data);
void* stack_pop(stacks_t* self);
void* stack_top(stacks_t* self);
size_t stack_size(stacks_t* self);
boolean_t stack_empty(stacks_t* self);

#endif /* STACK_H */