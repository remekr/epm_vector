#pragma once

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace epm
{

template <typename T>
class Vector
{
  public:
    Vector()
        : capacity(10), size(0)
    {
        memory = new T[10];
    };
    ~Vector()
    {
        delete[] memory;
    }

    void push_back(const T);
    void pop_back();

    // getters
    T& operator[](size_t n) const;
    T& at(const int index) const;
    T& front() const;
    T& back() const;

    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;

    class base_iterator
    {
      public:
        bool operator!=(const base_iterator& it)
        {
            return it.ptr != ptr;
        }
        bool operator==(const base_iterator& it)
        {
            return it.ptr == ptr;
        }
        base_iterator operator++()
        {
            ptr++;
            return *this;
        }
        base_iterator operator--(int i)
        {
            ptr--;
            return *this;
        }

      protected:
        pointer ptr;
    };
    class iterator : public base_iterator
    {
      public:
        iterator(pointer p)
        {
            this->ptr = p;
        }
        reference operator*()
        {
            return *(this->ptr);
        }
        pointer operator->()
        {
            return this->ptr;
        }
    };
    class const_iterator : public base_iterator
    {
      public:
        const_iterator(pointer p)
        {
            this->ptr = p;
        }
        const_reference operator*() const
        {
            return *(this->ptr);
        }
        const_pointer operator->() const
        {
            return this->ptr;
        }
        const_iterator operator++()
        {
            this->ptr++;
            return *this;
        }
        const_iterator operator--(int i)
        {
            this->ptr--;
            return *this;
        }
    };
    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    // capacity
    size_t getSize() const;
    void resize(const size_t n);
    size_t getCapacity() const;
    bool empty() const;
    void reserve(const size_t n);

  private:
    size_t capacity;
    int size;
    static const size_t increasingFactor = 2;

    T* memory;
};

// capacity related
template <typename T>
size_t Vector<T>::getSize() const
{
    return size;
}

template <typename T>
bool Vector<T>::empty() const
{
    return size == 0 ? true : false;
}
template <typename T>
size_t Vector<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
T& Vector<T>::at(const int index) const
{
    if (index < 0 || (index > size - 1))
    {
        throw std::out_of_range("Given index is out of bounds");
    }
    return memory[index];
}

template <typename T>
T& Vector<T>::operator[](size_t n) const
{
    return memory[n];
}

template <typename T>
T& Vector<T>::front() const
{
    if (size > 0)
    {
        return *memory;
    }
    else
    {
        throw std::out_of_range("");
    }
}

template <typename T>
T& Vector<T>::back() const
{
    if (size > 0)
    {
        return memory[size - 1];
    }
    else
    {
        throw std::out_of_range("");
    }
}

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

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const
{
    return iterator(memory);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const
{
    return iterator(memory + size);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const
{
    return const_iterator(memory);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const
{
    return const_iterator(memory + size);
}
};
