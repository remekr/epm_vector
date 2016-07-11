#pragma once

#include <cstdlib>
#include <iostream>

namespace epam
{

template <typename T>
class Vector
{
  public:
    Vector() : capacity(10), size(0) { memory = new T[10]; };
    ~Vector() { delete[] memory; }

    // modifiers
    void push_back(const T);
    void pop_back();

    // getters
    const T& operator[](size_t n) { return memory[n]; }

    // capacity
    size_t getSize() const;
    void resize(const size_t n);
    size_t getCapacity() const;
    bool empty() const;
    void reserve(const size_t n);

    // types
    typedef T value;
    typedef T& reference;
    typedef const T& constReference;

  private:
    size_t capacity;
    size_t size;
    static const size_t increasingFactor = 2;

    T* memory;
};

// capacity related
template <typename T>
size_t Vector<T>::getSize() const { return size; }

template <typename T>
bool Vector<T>::empty() const
{
    return size == 0 ? true : false;
}
template <typename T>
size_t Vector<T>::getCapacity() const { return capacity; }
template <typename T>
void Vector<T>::resize(const size_t n)
{
    if (n == capacity)
    {
        return;
    }
    if (n < capacity)
    {
        if (size > capacity)
        {
            for (auto i = n; i < size; ++i)
            {
                delete (memory + i);
            }
            size = n;
            capacity = n;
            // TODO? memory between 'n' and 'capacity' unfreed
        }
        else
        {
            capacity = n;
            // TODO? memory between 'n' and 'capacity' unfreed
        }
    }
    else
    {
        auto newMemory = new T[n];
        for (auto i = 0u; i < size; ++i)
        {
            newMemory[i] = memory[i];
        }
        delete[] memory;
        memory = newMemory;
        capacity = n;
    }
    if (size > capacity)
    {
        size = capacity;
    }
}

template <typename T>
void Vector<T>::push_back(const T element)
{
    if (capacity > size)
    {
        memory[size++] = element;
    }
    else
    {
        auto newMemory = new T[increasingFactor * capacity];
        for (auto i = 0u; i < size; ++i)
        {
            newMemory[i] = memory[i];
        }
        capacity = increasingFactor * capacity;
        memory[size++] = element;
    }
}

template <typename T>
void Vector<T>::pop_back()
{
    if (size == 0)
        return;
    else
        --size;
}
};
