/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef VECTOR_H
#define VECTOR_H 1

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"

typedef struct vector_s vector_t;

void vector_create(vector_t** vector, size_t capacity, size_t element_size);
void vector_destroy(vector_t** vector);
void vector_append(vector_t* vector, void* element);
void vector_prepend(vector_t* vector, void* element);
void* vector_get(vector_t* vector, size_t index);
void vector_set(vector_t* vector, size_t index, void* element);
void vector_insert(vector_t* vector, size_t index, void* element);
void vector_remove(vector_t* vector, size_t index);
size_t vector_size(vector_t* vector);
boolean_t vector_empty(vector_t* vector);
void vector_clear(vector_t* vector);

#endif /* VECTOR_H */
