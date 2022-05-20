// 01:05:00 14/05/2022 Augusto Goulart (1901560080)
#include "../include/terminal.h"

terminal::terminal() : _oldt({}), _newt({}), _fmode(0)
{
  tcgetattr(STDIN_FILENO, &_oldt);
  _newt = _oldt;

  _newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &_newt);

  _fmode = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, _fmode | O_NONBLOCK);
}

terminal::~terminal()
{
  tcsetattr(STDIN_FILENO, TCSANOW, &_oldt);
  fcntl(STDIN_FILENO, F_SETFL, _fmode);
}

void
terminal::save()
{
  *this << "\0337";
}

void
terminal::restore()
{
  *this << "\0338";
}

void
terminal::move(const base::size_t x, const base::size_t y)
{
  *this << "\033[" << x << ';' << y << 'H';
}

void
terminal::flush()
{
  *this << "\033[1;1H\033[2J";
}

void
terminal::restyle()
{
  *this << "\033[m";
}

void
terminal::color(const uint8_t r, const uint8_t g, const uint8_t b,
                const bool fg, const bool bg)
{
  uint8_t c = 16 + 36 * (r / 51) + 6 * (g / 51) + (b / 51);
  _color(c, fg, bg);
}

void terminal::color(const base::color_t c, const bool fg, const bool bg)
{
  _color(static_cast<uint8_t>(c), fg, bg);
}

void
terminal::color(const uint8_t gray, const bool fg, const bool bg)
{
  uint8_t c = gray / 11 + 232;
  _color(c, fg, bg);
}

void
terminal::font(const base::font_t f)
{
  *this << "\033[" << static_cast<uint8_t>(f) << 'm';
}

void
terminal::_color(const uint8_t c, const bool fg, const bool bg)
{
  if (fg || bg) {
    if (fg)
      *this << "\033[38;5;" << c << 'm';
    if (bg)
      *this << "\033[48;5;" << c << 'm';
  }
}

terminal&
operator<<(terminal& __out, const char __c)
{
  if (fputc(__c, stdout) == EOF)
    throw base::runtime_error("Could not output char");
  return __out;
}

terminal&
operator<<(terminal& __out, const char* __s)
{
  if (fputs(__s, stdout) == EOF)
    throw base::runtime_error("Could not output c-string");
  return __out;
}

terminal&
operator<<(terminal& __out, const bool __b)
{
  if (fputs((__b) ? "true" : "false", stdout) == EOF)
    throw base::runtime_error("Could not output boolean value");
  return __out;
}

#define __terminal_outop(F, T) \
terminal& \
operator<<(terminal& __out, const T __tn) \
{ \
  const base::size_t n = sizeof(__tn) * 3 + 1; \
  char __s[n]; \
  if (snprintf(__s, n, F, __tn) < 0) \
    throw base::runtime_error("Could not convert value to string"); \
  return __out << __s; \
}

__terminal_outop("%hhu", unsigned char)
__terminal_outop("%hd", short)
__terminal_outop("%hu", unsigned short)
__terminal_outop("%d", int)
__terminal_outop("%u", unsigned int)
__terminal_outop("%ld", long)
__terminal_outop("%lu", unsigned long)
__terminal_outop("%llu", unsigned long long)
__terminal_outop("%lld", long long)
__terminal_outop("%f", float)
__terminal_outop("%e", double)
__terminal_outop("%Le", long double)
__terminal_outop("%p", void*)

terminal&
operator>>(terminal& __out, char& __c) noexcept
{
  __c = static_cast<char>(fgetc(stdin));
  return __out;
}

terminal&
operator>>(terminal& __out, bool& __c) noexcept
{
  const base::size_t n = 8;
  char __s[n];
  if (fgets(__s, n, stdin) != nullptr) {
    if (!strcmp(__s, "true"))
      __c = true;
    else if (!strcmp(__s, "false"))
      __c = false;
  }
  return __out;
}

#define __terminal_inop(F, T) \
terminal& \
operator>>(terminal& __out, T& __tn) noexcept \
{ \
  auto r = fscanf(stdin, F, &__tn); \
  return __out; \
}

__terminal_inop("%hhd", unsigned char)
__terminal_inop("%hd", short)
__terminal_inop("%hu", unsigned short)
__terminal_inop("%d", int)
__terminal_inop("%u", unsigned int)
__terminal_inop("%ld", long)
__terminal_inop("%lu", unsigned long)
__terminal_inop("%llu", unsigned long long)
__terminal_inop("%lld", long long)
__terminal_inop("%f", float)
__terminal_inop("%lf", double)
__terminal_inop("%Le", long double)
__terminal_inop("%p", void*)

terminal&
operator>>(terminal& __out, base::key_t& __k) noexcept
{
  __k = base::key_t::none;
  char c;
  __out >> c;
  if (c != EOF) {
    if (c == '\033') {
      __out >> c >> c;
      switch (c)
      {
      case 'A':
        __k = base::key_t::up;
        break;

      case 'B':
        __k = base::key_t::down;
        break;

      case 'C':
        __k = base::key_t::right;
        break;

      case 'D':
        __k = base::key_t::left;
        break;
      
      default:
        {
          if (isdigit(c)) {
            unsigned char n = c - 48;
            __out >> c;
            if (isdigit(c))
              n = n * 10 + (c - 48);
            
            switch (n)
            {
            case 1:
            case 7:
              __k = base::key_t::home;
              break;

            case 2:
              __k = base::key_t::insert;
              break;

            case 3:
              __k = base::key_t::del;
              break;

            case 4:
            case 8:
              __k = base::key_t::end;
              break;

            case 5:
              __k = base::key_t::pageup;
              break;

            case 6:
              __k = base::key_t::pagedown;
              break;
            
            default:
              {
                if (n > 9 && n < 16)
                  n = n - 10 + static_cast<uint8_t>(base::key_t::f0);
                else if (n > 16 && n < 22)
                  n = n - 17 + static_cast<uint8_t>(base::key_t::f6);
                else if (n > 22 && n < 27)
                  n = n - 23 + static_cast<uint8_t>(base::key_t::f11);
                else if (n > 27 && n < 30)
                  n = n - 28 + static_cast<uint8_t>(base::key_t::f15);
                else if (n > 30 && n < 35)
                  n = n - 31 + static_cast<uint8_t>(base::key_t::f17);
                else
                  n = 0;

                __k = static_cast<base::key_t>(n);
                break;
              }
            }
          }
          break;
        }
      }
    }
    else if (isprint(c)) {
      unsigned char n = c;
      if (c > 31 && c < 48)
        n = n - 32 + static_cast<uint8_t>(base::key_t::space);
      else if (c > 47 && c < 58)
        n = n - 48 + static_cast<uint8_t>(base::key_t::zero);
      else if (c > 57 && c < 65)
        n = n - 58 + static_cast<uint8_t>(base::key_t::colon);
      else if (c > 64 && c < 91)
        n = n - 65 + static_cast<uint8_t>(base::key_t::a);
      else if (c > 90 && c < 97)
        n = n - 91 + static_cast<uint8_t>(base::key_t::squarebrace_o);
      else if (c > 96 && c < 123)
        n = n - 97 + static_cast<uint8_t>(base::key_t::a);
      else if (c > 122 && c < 127)
        n = n - 123 + static_cast<uint8_t>(base::key_t::curlybrace_o);
      else
        n = 0;

      __k = static_cast<base::key_t>(n);
    }
  }
  return __out;
}
