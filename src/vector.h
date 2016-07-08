#pragma once

#include <cstdlib>

namespace epam {

template <typename T>
class Vector {
   public:
    Vector() : capacity(10), size(0) { memory = new T[10]; };
    ~Vector() { delete[] memory; }

    // modifiers
    void push_back(const T);

    // getters
    const T& operator[](size_t n) { return memory[n]; }

    // capacity
    size_t getSize() const;
    void resize(const size_t n);
    size_t getCapacity() const;
    void empty();
    void reserve(const size_t n);
    void shrink_to_fit();

   private:
    size_t capacity;
    size_t size;

    T* memory;
};

// capacity related
template <typename T>
size_t Vector<T>::getSize() const {
    return size;
}
template <typename T>
size_t Vector<T>::getCapacity() const {
    return capacity;
}
template <typename T>
void Vector<T>::resize(const size_t n) {
    if (n == capacity) {
        return;
    }
    if (n < capacity) {
        capacity = n;
        if (size > capacity) {
            for (auto i = capacity; i < size - 1; ++i) {
                delete (memory + i);
            }
            size = capacity;
        }
    } else {
        // extend - capacity??
    }
    if (size > capacity) {
        size = capacity;
    }
}

template <typename T>
void Vector<T>::push_back(const T element) {
    if (capacity > size) {
        memory[size] = element;
        ++size;
    } else {  // resize...
    }
}
};
