/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef LIST_H
#define LIST_H 1

#include "base.h"

typedef struct list_s list_t;

void list_create(list_t** self);
void list_destroy(list_t** self);
void list_clear(list_t* self);
void* list_at(list_t* self, size_t index);
void list_emplace_back(list_t* self, void* data);
void list_emplace_front(list_t* self, void* data);
void list_emplace(list_t* self, void* data, size_t index);
void* list_remove_back(list_t* self);
void* list_remove_front(list_t* self);
void* list_remove(list_t* self, size_t index);
size_t list_size(list_t* self);
boolean_t list_empty(list_t* self);

#endif /* LIST_H */
