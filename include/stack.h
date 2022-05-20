// 13:44:00 17/05/2022 Augusto Goulart (1901560080)
#pragma once

#include <cctype>
#include "base.h"
#include "list.h"

template <typename T>
class stack: private list<T> {
public:
  using list<T>::empty;
  using list<T>::size;

  void push(const T& value)
  {
    this->emplace_back(value);
  }

  T pop()
  {
    return this->remove_back();
  }

  T& top()
  {
    return this->at(this->size() - 1);
  }
};
