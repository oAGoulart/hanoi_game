/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/terminal.h"

struct terminal_s {
  struct termios old_termios_;
  struct termios new_termios_;
  int fmode_;
};

void terminal_create(terminal_t** self)
{
  if (self == NULL) __throw("terminal_create: self is NULL");
  *self = (terminal_t*)malloc(sizeof(terminal_t));
  
  tcgetattr(STDIN_FILENO, &(*self)->old_termios_);
  (*self)->new_termios_ = (*self)->old_termios_;

  (*self)->new_termios_.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &(*self)->new_termios_);

  (*self)->fmode_ = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, (*self)->fmode_ | O_NONBLOCK);
}

void terminal_destroy(terminal_t** self)
{
  if (self == NULL) __throw("terminal_destroy: self is NULL");
  if (*self == NULL) __throw("terminal_destroy: *self is NULL");
  tcsetattr(STDIN_FILENO, TCSANOW, &(*self)->old_termios_);
  fcntl(STDIN_FILENO, F_SETFL, (*self)->fmode_);
  free(*self);
  *self = NULL;
}

void terminal_save(terminal_t* self)
{
  if (self == NULL) __throw("terminal_save: self is NULL");
  terminal_out_string(self, "\0337");
}

void terminal_restore(terminal_t* self)
{
  if (self == NULL) __throw("terminal_restore: self is NULL");
  terminal_out_string(self, "\0338");
}

void terminal_move(terminal_t* self, uint16_t x, uint16_t y)
{
  if (self == NULL) __throw("terminal_move: self is NULL");
  char __s[15];
  sprintf((char*)&__s, "\033[%hd;%hdH", x, y);
  terminal_out_string(self, __s);
}

void terminal_restyle(terminal_t* self)
{
  if (self == NULL) __throw("terminal_restyle: self is NULL");
  terminal_out_string(self, "\033[m");
}

void terminal_flush(terminal_t* self)
{
  if (self == NULL) __throw("terminal_flush: self is NULL");
  terminal_out_string(self, "\033[1;1H\033[2J");
}

void terminal_color(terminal_t* self, uint8_t r, uint8_t g, uint8_t b)
{
  if (self == NULL) __throw("terminal_color: self is NULL");
  char __s[12];
  sprintf((char*)&__s, "\033[38;5;%hhum", (uint8_t)__rgb(r, g, b));
  terminal_out_string(self, __s);
}

void terminal_background(terminal_t* self, uint8_t r, uint8_t g, uint8_t b)
{
  if (self == NULL) __throw("terminal_background: self is NULL");
  char __s[12];
  sprintf((char*)&__s, "\033[48;5;%hhum", (uint8_t)__rgb(r, g, b));
  terminal_out_string(self, __s);
}

void terminal_font(terminal_t* self, font_t font)
{
  if (self == NULL) __throw("terminal_font: self is NULL");
  char __s[7];
  sprintf((char*)&__s, "\033[%hhum", (uint8_t)font);
  terminal_out_string(self, __s);
}

void terminal_out_char(terminal_t* self, char __c)
{
  if (self == NULL) __throw("terminal_out_char: self is NULL");
  if (fputc(__c, stdout) == EOF) __throw("terminal_out_char: fputc failed");
}

void terminal_out_string(terminal_t* self, const char* __s)
{
  if (self == NULL) __throw("terminal_out_string: self is NULL");
  if (fputs(__s, stdout) == EOF) __throw("terminal_out_string: fputs failed");
}

void terminal_out_bool(terminal_t* self, boolean_t __b)
{
  if (self == NULL) __throw("terminal_out_boolean: self is NULL");
  if (fputs((__b) ? "true" : "false", stdout) == EOF) __throw("terminal_out_boolean: fputs failed");
}

#define __terminal_outop(F, T) \
void terminal_out_##T(terminal_t* self, T __tn) \
{ \
  if (self == NULL) __throw("terminal_out_" #T ": self is NULL"); \
  const size_t n = sizeof(__tn) * 3 + 1; \
  char __s[n]; \
  if (snprintf(__s, n, F, __tn) < 0) __throw("terminal_out_" #T ": snprintf failed"); \
  terminal_out_string(self, __s); \
}

__terminal_outop("%hhu", uint8_t);
__terminal_outop("%hd", int16_t);
__terminal_outop("%hu", uint16_t);
__terminal_outop("%d", int32_t);
__terminal_outop("%u", uint32_t);
__terminal_outop("%ld", int64_t);
__terminal_outop("%lu", uint64_t);
__terminal_outop("%f", float);
__terminal_outop("%lf", double);

void terminal_in_char(terminal_t* self, char* __c)
{
  if (self == NULL) __throw("terminal_in_char: self is NULL");
  if (__c == NULL) __throw("terminal_in_char: __c is NULL");
  *__c = (char)(fgetc(stdin));
}

void terminal_in_string(terminal_t* self, char* __s, size_t __n)
{
  if (self == NULL) __throw("terminal_in_string: self is NULL");
  if (__s == NULL) __throw("terminal_in_string: __s is NULL");
  if (fgets(__s, __n, stdin) == NULL) __throw("terminal_in_string: fgets failed");
}

void terminal_in_bool(terminal_t* self, boolean_t* __b)
{
  if (self == NULL) __throw("terminal_in_bool: self is NULL");
  if (__b == NULL) __throw("terminal_in_bool: __b is NULL");
  char __s[6];
  if (fgets(__s, 6, stdin) == NULL) __throw("terminal_in_bool: fgets failed");
  *__b = (!strcmp(__s, "true") || !strcmp(__s, "TRUE"));
}

#define __terminal_inop(F, T) \
void terminal_in_##T(terminal_t* self, T* __tn) \
{ \
  if (self == NULL) __throw("terminal_in_" #T ": self is NULL"); \
  if (__tn == NULL) __throw("terminal_in_" #T ": __tn is NULL"); \
  if (fscanf(stdin, F, __tn) < 0) __throw("terminal_in_" #T ": fscanf failed"); \
}

__terminal_inop("%hhu", uint8_t);
__terminal_inop("%hd", int16_t);
__terminal_inop("%hu", uint16_t);
__terminal_inop("%d", int32_t);
__terminal_inop("%u", uint32_t);
__terminal_inop("%ld", int64_t);
__terminal_inop("%lu", uint64_t);
__terminal_inop("%f", float);
__terminal_inop("%lf", double);


void terminal_in_key(terminal_t* self, keys_t* __k)
{
  if (self == NULL) __throw("terminal_in_key: self is NULL");
  if (__k == NULL) __throw("terminal_in_key: __k is NULL");
  *__k = key_none;
  char c;
  terminal_in_char(self, &c);
  if (c != EOF) {
    if (c == '\033') {
      terminal_in_char(self, &c);
      terminal_in_char(self, &c);
      switch (c)
      {
      case 'A':
        *__k = key_up;
        break;

      case 'B':
        *__k = key_down;
        break;

      case 'C':
        *__k = key_right;
        break;

      case 'D':
        *__k = key_left;
        break;
      
      default:
        {
          if (isdigit(c)) {
            unsigned char n = c - 48;
            terminal_in_char(self, &c);
            if (isdigit(c))
              n = n * 10 + (c - 48);
            
            switch (n)
            {
            case 1:
            case 7:
              *__k = key_home;
              break;

            case 2:
              *__k = key_insert;
              break;

            case 3:
              *__k = key_del;
              break;

            case 4:
            case 8:
              *__k = key_end;
              break;

            case 5:
              *__k = key_pageup;
              break;

            case 6:
              *__k = key_pagedown;
              break;

            default:
              {
                if (n > 9 && n < 16)
                  n = n - 10 + (uint8_t)(key_f0);
                else if (n > 16 && n < 22)
                  n = n - 17 + (uint8_t)(key_f6);
                else if (n > 22 && n < 27)
                  n = n - 23 + (uint8_t)(key_f11);
                else if (n > 27 && n < 30)
                  n = n - 28 + (uint8_t)(key_f15);
                else if (n > 30 && n < 35)
                  n = n - 31 + (uint8_t)(key_f17);
                else
                  n = 0;

                *__k = (keys_t)(n);
                break;
              }
            }
          }
        }
        break;
      }
    }
    else if (isprint(c)) {
      unsigned char n = c;
      if (c > 31 && c < 48)
        n = n - 32 + (uint8_t)(key_space);
      else if (c > 47 && c < 58)
        n = n - 48 + (uint8_t)(key_zero);
      else if (c > 57 && c < 65)
        n = n - 58 + (uint8_t)(key_colon);
      else if (c > 64 && c < 91)
        n = n - 65 + (uint8_t)(key_a);
      else if (c > 90 && c < 97)
        n = n - 91 + (uint8_t)(key_squarebrace_o);
      else if (c > 96 && c < 123)
        n = n - 97 + (uint8_t)(key_a);
      else if (c > 122 && c < 127)
        n = n - 123 + (uint8_t)(key_o);
      else
        n = 0;

      *__k = (keys_t)(n);
    }
    else {
      switch (c)
      {
      case '\b':
        *__k = key_backspace;
        break;

      case '\t':
        *__k = key_tab;
        break;

      case '\r':
        *__k = key_enter;
        break;

      case '\x1b':
        *__k = key_esc;
        break;

      default:
        break;
      }
    }
  }
}
