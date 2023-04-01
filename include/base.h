/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#ifndef BASE_H
#define BASE_H 1

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct color_s {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;

typedef enum font_e {
  font_normal,
  font_bold,
  font_faint,
  font_italic,
  font_underline,
  font_blink,
  font_strike = 9
} font_t;

typedef enum key_e {
  key_none,
  key_space,
  key_exclamation, /* ! */
  key_quotes, /* " */
  key_hash, /* # */
  key_dollar, /* $ */
  key_percent, /* % */
  key_ampersand, /* & */
  key_apostrophe, /* ' */
  key_parenthesis_o, /* ( */
  key_parenthesis_c, /* ) */
  key_asterisk, /* * */
  key_plus, /* + */
  key_comma, /* , */
  key_hyphen, /* - */
  key_period, /* . */
  key_slash_f, /* / */
  key_colon, /* : */
  key_semicolon, /* ; */
  key_lessthan, /* < */
  key_equal, /* = */
  key_greaterthan, /* > */
  key_question, /* ? */
  key_at, /* @ */
  key_squarebrace_o, /* [ */
  key_slash_b, /* \ */
  key_squarebrace_c, /* ] */
  key_carat, /* ^ */
  key_underscore, /* _ */
  key_backtick, /* ` */
  key_curlybrace_o, /* { */
  key_pipe, /* | */
  key_curlybrace_c, /* } */
  key_tilde, /* ~ */
  key_zero, /* 0 */
  key_one, /* 1 */
  key_two, /* 2 */
  key_three, /* 3 */
  key_four, /* 4 */
  key_five, /* 5 */
  key_six, /* 6 */
  key_seven, /* 7 */
  key_eight, /* 8 */
  key_nine, /* 9 */
  key_a,
  key_b,
  key_c,
  key_d,
  key_e,
  key_f,
  key_g,
  key_h,
  key_i,
  key_j,
  key_k,
  key_l,
  key_m,
  key_n,
  key_o,
  key_p,
  key_q,
  key_r,
  key_s,
  key_t_,
  key_u,
  key_v,
  key_w,
  key_x,
  key_y,
  key_z,
  key_home,
  key_insert,
  key_del,
  key_end,
  key_pageup,
  key_pagedown,
  key_up,
  key_down,
  key_left,
  key_right,
  key_f0,
  key_f1,
  key_f2,
  key_f3,
  key_f4,
  key_f5,
  key_f6,
  key_f7,
  key_f8,
  key_f9,
  key_f10,
  key_f11,
  key_f12,
  key_f13,
  key_f14,
  key_f15,
  key_f16,
  key_f17,
  key_f18,
  key_f19,
  key_f20,
  key_backspace,
  key_tab,
  key_enter,
  key_esc
} keys_t;

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

/* stringify */
#define __str(s) #s
/* expand and stringify */
#define __xstr(s) __str(s)

typedef uint8_t boolean_t;

/* terminal color manipulation */
#define __rgb(r, g, b) 16 + 36 * (r / 51) + 6 * (g / 51) + (b / 51)
#if !defined(NCOLOR)
#define __c(c, str) "\033[" __str(c) "m" str "\033[m"
#define __cs(cs, str) "\033[" cs "m" str "\033[m"
#else
#define __c(c, str) str
#define __cs(cs, str) str
#endif

/* terminal cursor manipulation */
#define __csave() printf("\033\067")
#define __crestore() printf("\033\070")
#define __cmove(x, y) printf("\033[%lu;%luH", x, y)

/* terminal flush */
#define __tflush() printf("\033[1;1H\033[2J")

/* debugging helper */
#if !defined(NDEBUG)
#define __pdebug(str) \
{ \
  printf( \
		"%s\n" \
    "FILE: " __FILE__ " LINE: " __xstr(__LINE__) "\n" \
    "FUNC: %s\n", str, __func__ \
  ); \
}
#else
#define __pdebug(str)
#endif

/* exception handling */
#define __exception_invalid_argument __c(41, " FATAL ") "\tInvalid argument"
#define __exception_null_pointer __c(41, " FATAL ") "\tNULL pointer"
#define __exception_unimplemented __c(41, " FATAL ") "\tUnimplemented"
#define __exception_unexpected __c(41, " FATAL ") "\tUnexpected"
#define __exception_realloc_failed __c(41, " FATAL ") "\trealloc() failed"
#define __exception_malloc_failed __c(41, " FATAL ") "\tmalloc() failed"
#define __exception_out_of_range __c(41, " FATAL ") "\tIndex out of range"
#define __exception_fputc_failed __c(41, " FATAL ") "\tfputc() failed"
#define __exception_fputs_failed __c(41, " FATAL ") "\tfputs() failed"
#define __exception_fgets_failed __c(41, " FATAL ") "\tfgets() failed"
#define __exception_fscanf_failed __c(41, " FATAL ") "\tfscanf() failed"
#define __exception_snprintf_failed __c(41, " FATAL ") "\tsnprintf() failed"

#define __throw(e) \
{ \
  __pdebug(e); \
  __builtin_trap(); \
}

#endif /* BASE_H */
