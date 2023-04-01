/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/disc.h"

struct disc_s {
  disc_size_t size_;
  color_t color_;
};

void disc_create(disc_t** self, disc_size_t size, uint8_t r, uint8_t g, uint8_t b)
{
  if (self == NULL) __throw(__exception_null_pointer);
  *self = (disc_t*)malloc(sizeof(disc_t));
  if (*self == NULL) __throw(__exception_malloc_failed);
  (*self)->size_ = size;
  (*self)->color_.r = r;
  (*self)->color_.g = g;
  (*self)->color_.b = b;
}

void disc_destroy(disc_t** self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  if (*self == NULL) __throw(__exception_null_pointer);
  free(*self);
  *self = NULL;
}

disc_size_t disc_size(disc_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return self->size_;
}

color_t disc_color(disc_t* self)
{
  if (self == NULL) __throw(__exception_null_pointer);
  return self->color_;
}
