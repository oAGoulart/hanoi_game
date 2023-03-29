/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/stack.h"

void stack_create(stack_t** self)
{
  list_create(self);
}

void stack_destroy(stack_t** self)
{
  list_destroy(self);
}

void stack_push(stack_t* self, void* data)
{
  list_emplace_back(self, data);
}

void* stack_pop(stack_t* self)
{
  return list_remove_back(self);
}

void* stack_top(stack_t* self)
{
  if (list_empty(self)) return NULL;
  return list_at(self, list_size(self) - 1);
}

size_t stack_size(stack_t* self)
{
  return list_size(self);
}

boolean_t stack_empty(stack_t* self)
{
  return list_empty(self);
}
