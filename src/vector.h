#pragma once

#include <cstdlib>

namespace epam {

template <typename T>
class Vector {
 public:
  Vector() : capacity(10) { memory = new T[10]; };
  ~Vector() { delete[] memory; }

 private:
  size_t capacity;
  size_t size;

  T* memory;
};
};
