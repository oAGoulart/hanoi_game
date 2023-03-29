/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef DISC_H
#define DISC_H 1
#include "base.h"

typedef enum disc_size_e {
  disc_tiny = 1,
  disc_small,
  disc_medium,
  disc_large,
  disc_huge
} disc_size_t;

typedef struct disc_s disc_t;

void disc_create(disc_t** self, disc_size_t size, uint8_t r, uint8_t g, uint8_t b);
void disc_destroy(disc_t** self);
disc_size_t disc_size(disc_t* self);
color_t disc_color(disc_t* self);

#endif /* DISC_H */
