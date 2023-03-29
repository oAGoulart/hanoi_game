/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef GAME_H
#define GAME_H 1

#include "base.h"
#include "terminal.h"
#include "stack.h"
#include "disc.h"
#include "vector.h"

typedef struct game_s game_t;

void game_create(game_t** self);
void game_destroy(game_t** self);
void game_run(game_t* self, boolean_t solve);

#endif
