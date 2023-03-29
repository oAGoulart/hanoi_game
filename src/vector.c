/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/vector.h"

struct vector_s {
  size_t size;
  size_t capacity;
  size_t element_size;
  void* data;
};

void vector_create(vector_t** self, size_t capacity, size_t element_size)
{
  if (self == NULL) __throw("vector_create: self is NULL");
  *self = (vector_t*)malloc(sizeof(vector_t));
  (*self)->size = 0;
  (*self)->capacity = capacity;
  (*self)->element_size = element_size;
  (*self)->data = malloc(capacity * element_size);
}

void vector_destroy(vector_t** self)
{
  if (self == NULL) __throw("vector_destroy: self is NULL");
  if (*self == NULL) __throw("vector_destroy: *self is NULL");
  free((*self)->data);
  free(*self);
  *self = NULL;
}

void vector_update_capacity_if_needed_(vector_t* self)
{
  if (self == NULL) __throw("vector_update_capacity_if_needed: self is NULL");
  if (self->size == self->capacity) {
    self->capacity *= 2;
    self->data = realloc(self->data, self->capacity * self->element_size);
  }
}

void vector_append(vector_t* self, void* element)
{
  if (self == NULL) __throw("vector_append: self is NULL");
  if (element == NULL) __throw("vector_append: element is NULL");
  vector_update_capacity_if_needed_(self);
  memcpy((char*)self->data + self->size * self->element_size, element, self->element_size);
  self->size++;
}

void vector_prepend(vector_t* self, void* element)
{
  if (self == NULL) __throw("vector_prepend: self is NULL");
  if (element == NULL) __throw("vector_prepend: element is NULL");
  vector_update_capacity_if_needed_(self);
  memmove((char*)self->data + self->element_size, self->data, self->size * self->element_size);
  memcpy(self->data, element, self->element_size);
  self->size++;
}

void* vector_get(vector_t* self, size_t index)
{
  if (self == NULL) __throw("vector_get: self is NULL");
  if (index >= self->size) __throw("vector_get: index out of range");
  return (char*)self->data + index * self->element_size;
}

void vector_set(vector_t* self, size_t index, void* element)
{
  if (self == NULL) __throw("vector_set: self is NULL");
  if (element == NULL) __throw("vector_set: element is NULL");
  if (index >= self->size) __throw("vector_set: index out of range");
  memcpy((char*)self->data + index * self->element_size, element, self->element_size);
}

void vector_insert(vector_t* self, size_t index, void* element)
{
  if (self == NULL) __throw("vector_insert: self is NULL");
  if (element == NULL) __throw("vector_insert: element is NULL");
  if (index >= self->size) __throw("vector_insert: index out of range");
  vector_update_capacity_if_needed_(self);
  memmove((char*)self->data + (index + 1) * self->element_size, (char*)self->data + index * self->element_size, (self->size - index) * self->element_size);
  memcpy((char*)self->data + index * self->element_size, element, self->element_size);
  self->size++;
}

void vector_remove(vector_t* self, size_t index)
{
  if (self == NULL) __throw("vector_remove: self is NULL");
  if (index >= self->size) __throw("vector_remove: index out of range");
  memmove((char*)self->data + index * self->element_size, (char*)self->data + (index + 1) * self->element_size, (self->size - index - 1) * self->element_size);
  self->size--;
}

size_t vector_size(vector_t* self)
{
  if (self == NULL) __throw("vector_size: self is NULL");
  return self->size;
}

boolean_t vector_empty(vector_t* self)
{
  if (self == NULL) __throw("vector_empty: self is NULL");
  return self->size == 0;
}

void vector_clear(vector_t* self)
{
  if (self == NULL) __throw("vector_clear: self is NULL");
  self->size = 0;
}
