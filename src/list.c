/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/list.h"
#include <stdlib.h>

typedef struct node_s {
  void* data_;
  struct node_s* prev_;
  struct node_s* next_;
} node_t;

void node_create(node_t** self, void* data, node_t* prev, node_t* next)
{
  if (self == NULL) __throw(__exception_null_pointer);
  *self = (node_t*)malloc(sizeof(node_t));
  if (*self == NULL) __throw(__exception_malloc_failed);
  (*self)->data_ = data;
  (*self)->prev_ = prev;
  (*self)->next_ = next;
}

void node_destroy(node_t** self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (*self == NULL) __throw(__exception_null_pointer);
  if ((*self)->data_ != NULL) free((*self)->data_);
  free(*self);
  *self = NULL;
}

struct list_s {
  node_t* head_;
  node_t* tail_;
  size_t size_;
};

void list_create(list_t** self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  *self = (list_t*)malloc(sizeof(list_t));
  if (*self == NULL) __throw(__exception_malloc_failed);
  (*self)->head_ = NULL;
  (*self)->tail_ = NULL;
  (*self)->size_ = 0;
}

void list_destroy(list_t** self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (*self == NULL) __throw(__exception_null_pointer);
  list_clear(*self);
  free(*self);
  *self = NULL;
}

void list_clear(list_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  node_t* node = self->head_;
  while (node != NULL) {
    node_t* next = node->next_;
    node_destroy(&node);
    node = next;
  }
  self->head_ = NULL;
  self->tail_ = NULL;
  self->size_ = 0;
}

void* list_at(list_t* self, size_t index)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (index >= self->size_) __throw(__exception_out_of_range);
  node_t* node = self->head_;
  size_t i = 0;
  while (i < index) {
    node = node->next_;
    i++;
  }
  return node->data_;
}

void list_emplace_back(list_t* self, void* data)
{
  if (self == NULL) __throw(__exception_null_pointer);
  node_t* node;
  if (self->tail_ == NULL) {
    node_create(&node, data, NULL, NULL);
    self->head_ = node;
    self->tail_ = node;
  }
  else {
    node_create(&node, data, self->tail_, NULL);
    self->tail_->next_ = node;
    self->tail_ = node;
  }
  self->size_++;
}

void list_emplace_front(list_t* self, void* data)
{
  if (self == NULL) __throw(__exception_null_pointer);
  node_t* node;
  if (self->head_ == NULL) {
    node_create(&node, data, NULL, NULL);
    self->head_ = node;
    self->tail_ = node;
  }
  else {
    node_create(&node, data, NULL, self->head_);
    self->head_->prev_ = node;
    self->head_ = node;
  }
  self->size_++;
}

void list_emplace(list_t* self, void* data, size_t index)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (index > self->size_) __throw(__exception_out_of_range);
  if (index == 0) {
    list_emplace_front(self, data);
    return;
  }
  if (index == self->size_) {
    list_emplace_back(self, data);
    return;
  }
  node_t* node;
  node_create(&node, data, NULL, NULL);
  node_t* prev = self->head_;
  size_t i = 0;
  while (i < index - 1) {
    prev = prev->next_;
    i++;
  }
  node_t* next = prev->next_;
  node->prev_ = prev;
  node->next_ = next;
  prev->next_ = node;
  next->prev_ = node;
  self->size_++;
}

void* list_remove_back(list_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (self->size_ == 0) __throw(__exception_out_of_range);
  node_t* node = self->tail_;
  void* data = node->data_;
  self->tail_ = node->prev_;
  if (self->tail_ != NULL) self->tail_->next_ = NULL;
  if (self->head_ == node) self->head_ = NULL;
  free(node);
  self->size_--;
  return data;
}

void* list_remove_front(list_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (self->size_ == 0) __throw(__exception_out_of_range);
  node_t* node = self->head_;
  void* data = node->data_;
  self->head_ = node->next_;
  if (self->head_ != NULL) self->head_->prev_ = NULL;
  if (self->tail_ == node) self->tail_ = NULL;
  free(node);
  self->size_--;
  return data;
}

void* list_remove(list_t* self, size_t index)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (index >= self->size_) __throw(__exception_out_of_range);
  if (index == 0) return list_remove_front(self);
  if (index == self->size_ - 1) return list_remove_back(self);
  node_t* node = self->head_;
  size_t i = 0;
  while (i < index) {
    node = node->next_;
    i++;
  }
  void* data = node->data_;
  node_t* prev = node->prev_;
  node_t* next = node->next_;
  prev->next_ = next;
  next->prev_ = prev;
  free(node);
  self->size_--;
  return data;
}

size_t list_size(list_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return self->size_;
}

boolean_t list_empty(list_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return self->size_ == 0;
}

void list_foreach(list_t* self, void (*callback)(void*))
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (callback == NULL) __throw(__exception_null_pointer);
  node_t* node = self->head_;
  while (node != NULL) {
    callback(node->data_);
    node = node->next_;
  }
}
