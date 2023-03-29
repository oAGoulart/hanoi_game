/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/stack.h"

void stack_create(stacks_t** self)
{
  list_create(self);
}

void stack_destroy(stacks_t** self)
{
  list_destroy(self);
}

void stack_push(stacks_t* self, void* data)
{
  list_emplace_back(self, data);
}

void* stack_pop(stacks_t* self)
{
  return list_remove_back(self);
}

void* stack_top(stacks_t* self)
{
  if (list_empty(self)) return NULL;
  return list_at(self, list_size(self) - 1);
}

size_t stack_size(stacks_t* self)
{
  return list_size(self);
}

boolean_t stack_empty(stacks_t* self)
{
  return list_empty(self);
}
