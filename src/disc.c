/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/disc.h"

struct disc_s {
  disc_size_t size_;
  color_t color_;
};

void disc_create(disc_t** self, disc_size_t size, uint8_t r, uint8_t g, uint8_t b)
{
  if (self == NULL) __throw("disc_create: self is NULL");
  *self = (disc_t*)malloc(sizeof(disc_t));
  if (*self == NULL) __throw("disc_create: malloc failed");
  (*self)->size_ = size;
  (*self)->color_.r = r;
  (*self)->color_.g = g;
  (*self)->color_.b = b;
}

void disc_destroy(disc_t** self)
{
  if (self == NULL) __throw("disc_destroy: self is NULL");
  if (*self == NULL) __throw("disc_destroy: *self is NULL");
  free(*self);
  *self = NULL;
}

disc_size_t disc_size(disc_t* self)
{
  if (self == NULL) __throw("disc_size: self is NULL");
  return self->size_;
}

color_t disc_color(disc_t* self)
{
  if (self == NULL) __throw("disc_color: self is NULL");
  return self->color_;
}
