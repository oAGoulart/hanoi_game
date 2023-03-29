/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef TERMINAL_H
#define TERMINAL_H 1

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "base.h"

typedef struct terminal_s terminal_t;

void terminal_create(terminal_t** self);
void terminal_destroy(terminal_t** self);
void terminal_save(terminal_t* self);
void terminal_restore(terminal_t* self);
void terminal_move(terminal_t* self, uint16_t x, uint16_t y);
void terminal_flush(terminal_t* self);
void terminal_restyle(terminal_t* self);
void terminal_color(terminal_t* self, uint8_t r, uint8_t g, uint8_t b);
void terminal_background(terminal_t* self, uint8_t r, uint8_t g, uint8_t b);
void terminal_font(terminal_t* self, font_t font);

void terminal_out_char(terminal_t* self, char __c);
void terminal_out_string(terminal_t* self, const char* __s);
void terminal_out_bool(terminal_t* self, boolean_t __b);
void terminal_out_uint8(terminal_t* self, uint8_t __tn);
void terminal_out_int16(terminal_t* self, int16_t __tn);
void terminal_out_uint16(terminal_t* self, uint16_t __tn);
void terminal_out_int32(terminal_t* self, int32_t __tn);
void terminal_out_uint32(terminal_t* self, uint32_t __tn);
void terminal_out_int64(terminal_t* self, int64_t __tn);
void terminal_out_uint64(terminal_t* self, uint64_t __tn);
void terminal_out_float(terminal_t* self, float __tn);
void terminal_out_double(terminal_t* self, double __tn);

void terminal_in_char(terminal_t* self, char* __c);
void terminal_in_string(terminal_t* self, char* __s, size_t __n);
void terminal_in_bool(terminal_t* self, boolean_t* __b);
void terminal_in_uint8(terminal_t* self, uint8_t* __tn);
void terminal_in_int16(terminal_t* self, int16_t* __tn);
void terminal_in_uint16(terminal_t* self, uint16_t* __tn);
void terminal_in_int32(terminal_t* self, int32_t* __tn);
void terminal_in_uint32(terminal_t* self, uint32_t* __tn);
void terminal_in_int64(terminal_t* self, int64_t* __tn);
void terminal_in_uint64(terminal_t* self, uint64_t* __tn);
void terminal_in_float(terminal_t* self, float* __tn);
void terminal_in_double(terminal_t* self, double* __tn);

void terminal_in_key(terminal_t* self, keys_t* __k);

#endif /* TERMINAL_H */
