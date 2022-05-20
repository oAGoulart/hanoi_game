// 23:36:00 11/05/2022 Augusto Goulart (1901560080)
#pragma once

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cctype>
#include "base.h"

class terminal {
public:
  terminal();
  ~terminal();

  void save();
  void restore();
  void move(const base::size_t x, const base::size_t y);
  void flush();
  void restyle();
  void color(const uint8_t r, const uint8_t g, const uint8_t b,
             const bool fg, const bool bg);
  void color(const base::color_t c, const bool fg, const bool bg);
  void color(const uint8_t gray, const bool fg, const bool bg);
  void font(const base::font_t f);

private:
  struct termios _oldt, _newt;
  int _fmode;
  
  void _color(const uint8_t c, const bool fg, const bool bg);
};

terminal& operator<<(terminal& __out, const char __c);
terminal& operator<<(terminal& __out, const char* __s);
terminal& operator<<(terminal& __out, const bool __b);
terminal& operator<<(terminal& __out, const unsigned char __tn);
terminal& operator<<(terminal& __out, const short __tn);
terminal& operator<<(terminal& __out, const unsigned short __tn);
terminal& operator<<(terminal& __out, const int __tn);
terminal& operator<<(terminal& __out, const unsigned int __tn);
terminal& operator<<(terminal& __out, const long __tn);
terminal& operator<<(terminal& __out, const unsigned long __tn);
terminal& operator<<(terminal& __out, const long long __tn);
terminal& operator<<(terminal& __out, const unsigned long long __tn);
terminal& operator<<(terminal& __out, const float __tn);
terminal& operator<<(terminal& __out, const double __tn);
terminal& operator<<(terminal& __out, const long double __tn);
terminal& operator<<(terminal& __out, const void* __tn);

terminal& operator>>(terminal& __out, char& __c) noexcept;
terminal& operator>>(terminal& __out, bool& __c) noexcept;
terminal& operator>>(terminal& __out, unsigned char& __tn) noexcept;
terminal& operator>>(terminal& __out, short& __tn) noexcept;
terminal& operator>>(terminal& __out, unsigned short& __tn) noexcept;
terminal& operator>>(terminal& __out, int& __tn) noexcept;
terminal& operator>>(terminal& __out, unsigned int& __tn) noexcept;
terminal& operator>>(terminal& __out, long& __tn) noexcept;
terminal& operator>>(terminal& __out, unsigned long& __tn) noexcept;
terminal& operator>>(terminal& __out, long long& __tn) noexcept;
terminal& operator>>(terminal& __out, unsigned long long& __tn) noexcept;
terminal& operator>>(terminal& __out, float& __tn) noexcept;
terminal& operator>>(terminal& __out, double& __tn) noexcept;
terminal& operator>>(terminal& __out, long double& __tn) noexcept;
terminal& operator>>(terminal& __out, void*& __tn) noexcept;

terminal& operator>>(terminal& __out, base::key_t& __k) noexcept;
