// 19:43:00 15/05/2022 Augusto Goulart (1901560080)
#pragma once

#include <cctype>
#include "base.h"

template <typename T>
class list {
public:
  list() : _size(0), _head(nullptr), _tail(nullptr)
  {
  };

  virtual ~list()
  {
    auto curr = _head;
    while (curr != nullptr) {
      auto next = curr->_next;
      delete curr;
      curr = next;
    }
  };

  constexpr bool empty() const noexcept
  {
    return (_size == 0);
  };

  constexpr base::size_t size() const noexcept
  {
    return _size;
  };

  T& at(const base::size_t pos)
  {
    if (pos < _size) {
      if (pos == 0)
        return _head->_value;
      if (pos == (_size - 1))
        return _tail->_value;

      base::size_t count = 0;
      auto curr = _head;
      while (curr != nullptr) {
        if (count == pos)
          return curr->_value;
        curr = curr->_next;
        count++;
      }
    }
    throw base::runtime_error("Invalid list position");
  };

  void emplace_back(const T& value)
  {
    auto elem = new node(value);
    if (_tail != nullptr) {
      _tail->_next = elem;
      elem->_prev = _tail;
    }
    if (_size == 0)
      _head = elem;

    _tail = elem;
    _size++;
  };

  void emplace_front(const T& value)
  {
    auto elem = new node(value);
    if (_head != nullptr) {
      _head->_prev = elem;
      elem->_next = _head;
    }
    if (_size == 0)
      _tail = elem;

    _head = elem;
    _size++;
  };

  virtual void emplace(const T& value, const base::size_t at)
  {
    if (at <= _size) {
      if (at == 0) {
        emplace_front(value);
        return;
      }
      else if (at == _size) {
        emplace_back(value);
        return;
      }
      else {
        base::size_t count = 0;
        auto curr = _head;
        while (curr != nullptr) {
          if (count == at) {
            auto prev = curr->_prev;
            auto elem = new node(value, prev, curr);
            prev->_next = elem;
            curr->_prev = elem;
            _size++;
            return;
          }
          curr = curr->_next;
          count++;
        }
      }
    }
    throw base::runtime_error("Invalid list position");
  };

  T remove_back()
  {
    if (_tail != nullptr) {
      auto value = _tail->_value;
      auto prev = _tail->_prev;
      if (prev != nullptr)
        prev->_next = nullptr;
      if (_size == 1)
        _head = nullptr;

      delete _tail;
      _tail = prev;
      _size--;
      return value;
    }
    throw base::runtime_error("Empty list");
  }

  T remove_front()
  {
    if (_head != nullptr) {
      auto value = _head->_value;
      auto next = _head->_next;
      if (next != nullptr)
        next->_prev = nullptr;
      if (_size == 1)
        _tail = nullptr;

      delete _head;
      _head = next;
      _size--;
      return value;
    }
    throw base::runtime_error("Empty list");
  }

  virtual T remove(const base::size_t at)
  {
    if (at < _size) {  
      if (at == 0)
        return remove_front();
      if (at == (_size - 1))
        return remove_back();
      
      base::size_t count = 0;
      auto curr = _head;
      while (curr != nullptr) {
        if (count == at) {
          auto value = curr->_value;
          auto prev = curr->_prev;
          prev->_next = curr->_next;
          curr->_next->_prev = prev;
          delete curr;
          return value;
        }
        curr = curr->_next;
        count++;
      }
    }
    throw base::runtime_error("Invalid list position");
  }

  virtual list& operator+=(const T& value)
  {
    emplace_back(value);
    return *this;
  }

  virtual T& operator[](const base::size_t pos)
  {
    return at(pos);
  }

private:
  class node {
  public:
    node(const T& value) :
      _value(value), _prev(nullptr), _next(nullptr)
    {
    };

    node(const T& value, node* prev, node* next) :
      _value(value), _prev(prev), _next(next)
    {
    };

  private:
    T _value;
    node* _prev;
    node* _next;

    friend class list;
  };

  base::size_t _size;
  node* _head;
  node* _tail;  
};
