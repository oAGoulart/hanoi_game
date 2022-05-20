// 14:14:00 17/05/2022 Augusto Goulart (1901560080)
#pragma once

#include <cctype>
#include "base.h"
#include "terminal.h"
#include "list.h"
#include "stack.h"

class hanoi_game {
public:
  hanoi_game() : _t(), _pins(), _curr_pin(0), _selected(), _over(false)
  {
    _pins += {};
    _pins += {};
    _pins += {};
    _pins[0].push(disc(disc::size::big, disc::color(255, 153, 0)));
    _pins[0].push(disc(disc::size::medium, disc::color(0, 0, 102)));
    _pins[0].push(disc(disc::size::normal, disc::color(153, 0, 0)));
    _pins[0].push(disc(disc::size::small, disc::color(255, 51, 204)));
    _pins[0].push(disc(disc::size::tiny, disc::color(0, 204, 102)));
  };

  void run()
  {
    bool redraw = true;
    base::key_t k;
    while(true)
    {
      _t >> k;
      if (k == base::key_t::q) { // user wants to quit
        _t.flush();
        _t.font(base::font_t::italic);
        _t.color(200, 60, 10, true, false);
        _t << "User interrupted application\n";
        _t.restyle();
        break;
      }

      if (k == base::key_t::left) {
        if (_curr_pin > 0) {
          _curr_pin--; // move selection left
          redraw = true;
        }
      }
      else if (k == base::key_t::right) {
        if (_curr_pin < (_pins.size() - 1)) {
          _curr_pin++; // move selection right
          redraw = true;
        }
      }
      else if (k == base::key_t::up) {
        if (_selected.empty() && !_pins[_curr_pin].empty()) {
          _selected.push(_pins[_curr_pin].pop()); // remove disc from pin
          redraw = true;
        }
      }
      else if (k == base::key_t::down) {
        if (!_selected.empty()) {
          if (_pins[_curr_pin].empty()) {           // pin is empty, so...
            _pins[_curr_pin].push(_selected.pop()); // put disc on pin
            redraw = true;
          }
          else {
            auto d = _pins[_curr_pin].top();
            auto t = _selected.top();
            if (d._size > t._size) {                  // pin's top disc is bigger
              _pins[_curr_pin].push(_selected.pop()); // put disc on pin
              redraw = true;
            }
          }
        }
        if (_curr_pin == (_pins.size() - 1)) {        // check if game is over
          if (_selected.empty() && _pins[_curr_pin].size() == 5) {
            _over = true;
            redraw = true;
          }
        }
      }

      if (redraw) {
        _t.flush();
        _draw();
        redraw = false;
      }
      if (_over)
        break;
    }
  }

private:
  struct disc {
    enum class size : uint8_t {
      none,
      tiny,
      small,
      normal,
      medium,
      big
    } _size;

    struct color {
      uint8_t _r;
      uint8_t _g;
      uint8_t _b;

      color(const uint8_t r, const uint8_t g, const uint8_t b) :
        _r(r), _g(g), _b(b)
      {
      };
    } _color;

    disc() : _size(size::none), _color({ 255, 255, 255 })
    {
    };

    disc(const size s, const struct color c) : _size(s), _color(c)
    {
    };
  };
  using disc = struct disc;

  terminal _t;
  list<stack<disc>> _pins;
  base::size_t _curr_pin;
  stack<disc> _selected;
  bool _over;

  void _draw_disc(const disc d, const base::size_t pin, const base::size_t i)
  {
    const base::size_t x = 19 - i;
    const base::size_t y = 11 + (20 * pin);

    _t.color(d._color._r, d._color._g, d._color._b, true, true);

    base::size_t n = (5 - static_cast<uint8_t>(d._size));
    base::size_t j = n;
    for (; j < n + (1 + 2 * static_cast<uint8_t>(d._size)); j++) {
      _t.move(x, y + j);
      _t << "D";
    }
  }

  void _draw_pin(const base::size_t i)
  {
    const base::size_t x = 14;
    const base::size_t y = 10 + (20 * i);

    _t.color(255, 255, 102, true, true);

    base::size_t j = 0;
    for (; j < 6; j++) {
      _t.move(x + j, y + 6);
      _t << "D";
    }
    _t.move(x + j, y);
    _t << "DDDDDDDDDDDDD";

    _t.color(base::color_t::black, true, false);
    _t.color(base::color_t::white, false, true);
    _t.move(x + j + 2, y + 5);
    _t << ' ' << i << ' ';

    if (i == _curr_pin) {
      _t.move(x + j + 3, y + 5);
      _t << " | ";

      if (!_selected.empty())
        _draw_disc(_selected.top(), i, 7);
    }
  }

  void _draw()
  {
    if (_over) {
      _t.font(base::font_t::bold);
      _t.color(base::color_t::hmagenta, true, false);
      _t << "\n\tCongratulations! You've done it.\n\n";
      _t.restyle();
      return;
    }

    _t.save();
    base::size_t i = 0;
    for (; i < _pins.size(); i++) {
      _draw_pin(i);

      stack<disc> aux = {};
      base::size_t j = _pins[i].size();
      for (; j > 0; j--) {
        auto d = _pins[i].pop();
        _draw_disc(d, i, j - 1);
        aux.push(d);
      }
      while (aux.size() > 0)
        _pins[i].push(aux.pop());
    }
    _t.restore();
    _t.restyle();
  }
};
