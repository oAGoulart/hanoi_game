/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef STACK_H
#define STACK_H 1

#include "base.h"
#include "list.h"

typedef struct list_s stack_t;

void stack_create(stack_t** self);
void stack_destroy(stack_t** self);
void stack_push(stack_t* self, void* data);
void* stack_pop(stack_t* self);
void* stack_top(stack_t* self);
size_t stack_size(stack_t* self);
boolean_t stack_empty(stack_t* self);

#endif /* STACK_H */