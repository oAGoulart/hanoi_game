/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/game.h"

struct game_s {
  terminal_t* t_;
  size_t num_pins_;
  stack_t* pins_[3];
  uint8_t current_pin_;
  disc_t* current_disc_;
  boolean_t is_running_;
  boolean_t is_solving_;
  boolean_t has_won_;
  size_t num_moves_;
  vector_t* solution_;
};

void calculate_move_(uint8_t src, uint8_t dest, vector_t* solution)
{
  if (solution == NULL) __throw("calculate_move_: solution is NULL");
  keys_t k;
  int move = (int)dest - (int)src;
  if (move > 0) {
    k = key_right;
    vector_append(solution, &k);
    if (move > 1)
      vector_append(solution, &k);
  }
  else if (move < 0) {
    k = key_left;
    vector_append(solution, &k);
    if (move < -1)
      vector_append(solution, &k);
  }
}

void game_solve(game_t* self, uint8_t n, uint8_t src, uint8_t aux, uint8_t dest)
{
  if (self == NULL) __throw("game_run: self is NULL");
  keys_t k = key_up;
  if (n == 1) {
    vector_append(self->solution_, &k);
    calculate_move_(src, dest, self->solution_);
    k = key_down;
    vector_append(self->solution_, &k);
    return;
  }
  
  game_solve(self, n - 1, src, dest, aux);
  calculate_move_(aux, src, self->solution_);
  k = key_up;
  vector_append(self->solution_, &k);
  calculate_move_(src, dest, self->solution_);
  k = key_down;
  vector_append(self->solution_, &k);
  calculate_move_(dest, aux, self->solution_);
  game_solve(self, n - 1, aux, src, dest);
}

void game_create(game_t** self)
{
  if (self == NULL) __throw("game_create: self is NULL");
  *self = (game_t*)malloc(sizeof(game_t));
  if (*self == NULL) __throw("game_create: malloc failed");
  terminal_create(&(*self)->t_);
  (*self)->num_pins_ = 3;
  (*self)->current_pin_ = 0;
  (*self)->current_disc_ = NULL;
  (*self)->is_running_ = TRUE;

  vector_create(&(*self)->solution_, 128, sizeof(keys_t));
  game_solve(*self, 5, 0, 1, 2);
  (*self)->num_moves_ = 0;
  (*self)->has_won_ = FALSE;

  stack_create(&(*self)->pins_[0]);
  stack_create(&(*self)->pins_[1]);
  stack_create(&(*self)->pins_[2]);
  
  disc_t* d = NULL;
  disc_create(&d, disc_huge, 255, 153, 0);
  stack_push((*self)->pins_[0], d);
  disc_create(&d, disc_large, 0, 0, 102);
  stack_push((*self)->pins_[0], d);
  disc_create(&d, disc_medium, 153, 0, 0);
  stack_push((*self)->pins_[0], d);
  disc_create(&d, disc_small, 255, 51, 204);
  stack_push((*self)->pins_[0], d);
  disc_create(&d, disc_tiny, 0, 204, 102);
  stack_push((*self)->pins_[0], d);
}

void game_destroy(game_t** self)
{
  if (self == NULL) __throw("game_destroy: self is NULL");
  if (*self == NULL) __throw("game_destroy: *self is NULL");
  terminal_destroy(&(*self)->t_);
  vector_destroy(&(*self)->solution_);
  stack_destroy(&(*self)->pins_[0]);
  stack_destroy(&(*self)->pins_[1]);
  stack_destroy(&(*self)->pins_[2]);
  free(*self);
  *self = NULL;
}

void draw_disc_(game_t* self, disc_t* disc, uint8_t pin, size_t i)
{
  if (self == NULL) __throw("draw_disc_: self is NULL");
  if (disc == NULL) __throw("draw_disc_: disc is NULL");
  const size_t x = 19 - i;
  const size_t y = 11 + (20 * pin);

  color_t c = disc_color(disc);
  terminal_color(self->t_, c.r, c.g, c.b);
  terminal_background(self->t_, c.r, c.g, c.b);

  disc_size_t disc_sz = disc_size(disc);
  size_t n = 5 - (uint8_t)disc_sz;
  size_t j = n;
  for (; j < n + (1 + 2 * (uint8_t)disc_sz); j++) {
    terminal_move(self->t_, x, y + j);
    terminal_out_char(self->t_, 'D');
  }
}

void draw_pin_(game_t* self, uint8_t pin)
{
  if (self == NULL) __throw("draw_pin_: self is NULL");
  const size_t x = 14;
  const size_t y = 10 + (20 * pin);

  terminal_color(self->t_, 255, 255, 102);
  terminal_background(self->t_, 255, 255, 102);

  size_t j = 0;
  for (; j < 6; j++) {
    terminal_move(self->t_, x + j, y + 6);
    terminal_out_char(self->t_, 'D');
  }
  terminal_move(self->t_, x + j, y);
  terminal_out_string(self->t_, "DDDDDDDDDDDDD");

  terminal_color(self->t_, 0, 0, 0);
  terminal_background(self->t_, 255, 255, 255);
  terminal_move(self->t_, x + 8, y + 5);
  char __s[6];
  sprintf(__s, " %hhu ", pin);
  terminal_out_string(self->t_, __s);

  if (pin == self->current_pin_) {
    terminal_move(self->t_, x + j + 3, y + 5);
    terminal_out_string(self->t_, " | ");

    if (self->current_disc_ != NULL)
      draw_disc_(self, self->current_disc_, pin, 7);
  }
}

char* movement_to_string_(keys_t key)
{
  if (key == key_up) return "UP";
  if (key == key_down) return "DOWN";
  if (key == key_left) return "LEFT";
  if (key == key_right) return "RIGHT";
  return "UNKNOWN";
}

void draw_info_(game_t* self)
{
  if (self == NULL) __throw("draw_info_: self is NULL");
  terminal_move(self->t_, 2, 20);
  terminal_color(self->t_, 255, 255, 102);
  terminal_font(self->t_, font_bold);
  terminal_out_string(self->t_, "Towers of Hanoi");
  terminal_font(self->t_, font_normal);
  terminal_color(self->t_, 255, 255, 255);
  terminal_move(self->t_, 4, 0);

  if (self->is_solving_) {
    terminal_out_string(self->t_,
      "\tPress TAB to go to the next move.\n"
      "\tPress Q to quit.\n\n\n");
    char __s[32];
    sprintf(__s, "\tStep %hu: %s", (uint16_t)self->num_moves_ + 1, movement_to_string_(*(keys_t*)vector_get(self->solution_, self->num_moves_)));
    terminal_color(self->t_, 0, 0, 0);
    terminal_background(self->t_, 255, 255, 102);    
    terminal_out_string(self->t_, __s);
  }
  else {
    terminal_out_string(self->t_,
      "\tMovement keys: WASD or arrow keys.\n"
      "\tPress Q to quit.\n");
  }
}

void game_draw(game_t* self)
{
  if (self == NULL) __throw("game_draw: self is NULL");
  if (self->has_won_) {
    terminal_color(self->t_, 0, 0, 0);
    terminal_background(self->t_, 255, 255, 255);
    terminal_move(self->t_, 8, 25);
    terminal_out_string(self->t_, "Congratulations! You've done it.");
    terminal_restyle(self->t_);
  }

  terminal_save(self->t_);
  draw_info_(self);

  size_t i = 0;
  for (; i < 3; i++) {
    draw_pin_(self, i);

    stack_t* aux;
    stack_create(&aux);
    size_t j = stack_size(self->pins_[i]);
    for (; j > 0; j--) {
      disc_t* d = (disc_t*)stack_pop(self->pins_[i]);
      draw_disc_(self, d, i, j - 1);
      stack_push(aux, d);
    }
    while (!stack_empty(aux))
      stack_push(self->pins_[i], stack_pop(aux));
  }
  terminal_restore(self->t_);
  terminal_restyle(self->t_);
}

void game_run(game_t* self, boolean_t solve)
{
  if (self == NULL) __throw("game_run: self is NULL");
  self->is_running_ = TRUE;
  self->is_solving_ = solve;
  boolean_t redraw = TRUE;
  keys_t k;
  
  /* first draw */
  terminal_flush(self->t_);
  game_draw(self);

  /* main loop */
  while (self->is_running_) {
    terminal_in_key(self->t_, &k);

    /* quit */
    if (k == key_q) {
      terminal_flush(self->t_);
      terminal_font(self->t_, font_italic);
      terminal_color(self->t_, 200, 60, 10);
      terminal_out_string(self->t_, "User interrupted application\n");
      terminal_restyle(self->t_);
      break;
    }

    if (self->has_won_) continue;

    /* solve */
    if (self->is_solving_) {
      if (k == key_tab) {
        k = *(keys_t*)vector_get(self->solution_, self->num_moves_);
        self->num_moves_++;
      }
      else continue;
    }

    /* move left */
    if (k == key_left || k == key_a) {
      if (self->current_pin_ > 0) {
        self->current_pin_--;
        redraw = TRUE;
      }
    }
    /* move right */
    else if (k == key_right || k == key_d) {
      if (self->current_pin_ < (self->num_pins_ - 1)) {
        self->current_pin_++;
        redraw = TRUE;
      }
    }
    /* move up */
    else if (k == key_up || k == key_w) {
      if (self->current_disc_ == NULL && !stack_empty(self->pins_[self->current_pin_])) {
          self->current_disc_ = stack_pop(self->pins_[self->current_pin_]);
          redraw = TRUE;
      }
    }
    /* move down */
    else if (k == key_down || k == key_s) {
      if (self->current_disc_ != NULL) {
        if (stack_empty(self->pins_[self->current_pin_])) {
          stack_push(self->pins_[self->current_pin_], self->current_disc_);
          self->current_disc_ = NULL;
          redraw = TRUE;
        }
        else {
          disc_t* top = stack_top(self->pins_[self->current_pin_]);
          if (disc_size(top) > disc_size(self->current_disc_)) {
            stack_push(self->pins_[self->current_pin_], self->current_disc_);
            self->current_disc_ = NULL;
            redraw = TRUE;
          }
        }
      }
      if (self->current_pin_ == (self->num_pins_ - 1)) {
        if (self->current_disc_ == NULL && stack_size(self->pins_[self->current_pin_]) == 5) {
          self->has_won_ = TRUE;
          redraw = TRUE;
        }
      }
    }
    
    if (self->has_won_) {
      self->is_solving_ = FALSE;
      self->num_moves_ = 0;
    }
    if (redraw) {
      terminal_flush(self->t_);
      game_draw(self);
      redraw = FALSE;
    }
  }
}
