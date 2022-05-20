// 23:37:00 11/05/2022 Augusto Goulart (1901560080)
#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>

namespace base
{

enum class color_t: uint8_t {
  black,
  red,
  green,
  yellow,
  blue,
  magenta,
  cyan,
  white,
  hblack,
  hred,
  hgreen,
  hyellow,
  hblue,
  hmagenta,
  hcyan,
  hwhite
};

enum class font_t: uint8_t {
  normal,
  bold,
  faint,
  italic,
  underline,
  blink,
  strike = 9
};

enum class key_t: uint8_t {
  none,
  space,
  exclamation, // !
  quotes, // "
  hash, // #
  dollar, // $
  percent, // %
  ampersand, // &
  apostrophe, // '
  parenthesis_o, // (
  parenthesis_c, // )
  asterisk, // *
  plus, // +
  comma, // ,
  hyphen, // -
  period, // .
  slash_f, // /
  colon, // :
  semicolon, // ;
  lessthan, // <
  equal, // =
  greaterthan, // >
  question, // ?
  at, // @
  squarebrace_o, // [
  slash_b, /* \ */
  squarebrace_c, // ]
  carat, // ^
  underscore, // _
  backtick, // `
  curlybrace_o, // {
  pipe, // |
  curlybrace_c, // }
  tilde, // ~
  zero, // 0
  one, // 1
  two, // 2
  three, // 3
  four, // 4
  five, // 5
  six, // 6
  seven, // 7
  eight, // 8
  nine, // 9
  a,
  b,
  c,
  d,
  e,
  f,
  g,
  h,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  q,
  r,
  s,
  t,
  u,
  v,
  w,
  x,
  y,
  z,
  home,
  insert,
  del,
  end,
  pageup,
  pagedown,
  up,
  down,
  left,
  right,
  f0,
  f1,
  f2,
  f3,
  f4,
  f5,
  f6,
  f7,
  f8,
  f9,
  f10,
  f11,
  f12,
  f13,
  f14,
  f15,
  f16,
  f17,
  f18,
  f19,
  f20
};

using size_t = size_t;
using runtime_error = std::runtime_error;

}
