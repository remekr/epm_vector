#pragma once

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <memory>

namespace epm
{

template <typename T>
class Vector
{
  public:
    Vector(const std::allocator<T> alloc = std::allocator<T>())
        : capacity(10), size(0), allocator(alloc)
    {
        memory = allocator.allocate(capacity);
    };
    explicit Vector(std::initializer_list<T> list, const std::allocator<T>& alloc = std::allocator<T>());
    explicit Vector(size_t n, const std::allocator<T>& alloc = std::allocator<T>());
    explicit Vector(size_t n, const T& val, const std::allocator<T>& alloc = std::allocator<T>());
    Vector(const Vector& v, const std::allocator<T>& alloc = std::allocator<T>());
    ~Vector();

    void push_back(const T);
    void pop_back();

    void clear();

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
        iterator operator++()
        {
            this->ptr++;
            return *this;
        }
        iterator operator--(int i)
        {
            this->ptr--;
            return *this;
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

    template <typename X, typename Y>
    friend bool operator==(const Vector<X>& v1, const Vector<Y>& v2);
    template <typename X, typename Y>
    friend bool operator!=(const Vector<X>& v1, const Vector<Y>& v2);

  private:
    size_t capacity;
    int size;
    static const size_t increasingFactor = 2;
    std::allocator<T> allocator;

    T* memory;
};

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list, const std::allocator<T>& alloc)
{
    allocator = alloc;
    memory = allocator.allocate(list.size());

    auto i = 0;
    for (auto e : list)
    {
        memory[i++] = e;
    }
    size = list.size();
    capacity = list.size();
}

template <typename T>
Vector<T>::Vector(size_t n, const std::allocator<T>& alloc)
{
    allocator = alloc;
    memory = allocator.allocate(n);
    capacity = n;
    size = 0;
}

template <typename T>
Vector<T>::Vector(size_t n, const T& val, const std::allocator<T>& alloc)
{
    allocator = alloc;
    memory = allocator.allocate(n);
    for (auto i = 0; i < n; ++i)
    {
        memory[i] = val;
    }
    size = n;
    capacity = n;
}

template <typename T>
Vector<T>::Vector(const Vector& v, const std::allocator<T>& alloc)
{
    size = v.getSize();
    capacity = v.getCapacity();
    memory = allocator.allocate(capacity);
    for (auto i = 0; i < size; ++i)
    {
        memory[i] = v[i];
    }
}

template <typename T>
Vector<T>::~Vector()
{
    if (memory != nullptr)
    {
        allocator.deallocate(memory, capacity);
    }
}

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
    if (index < 0 || (index > size))
    {
        throw std::out_of_range("Given index is out of bounds");
    }
    if (size == 0)
    {
        throw std::logic_error("Vector is empty!");
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

template <typename T>
void Vector<T>::clear()
{
    size = 0;
}

template <typename X>
bool operator==(const Vector<X>& v1, const Vector<X>& v2)
{
    auto eq = true;
    if (v1.getSize() != v2.getSize())
    {
        return false;
    }
    for (auto i = 0; i < v1.getSize(); ++i)
    {
        if (v1[i] != v2[i])
        {
            eq = false;
        }
    }
    return eq;
}

template <typename X>
bool operator!=(const Vector<X>& v1, const Vector<X>& v2)
{
    if (v1.getSize() != v2.getSize())
    {
        return true;
    }
    for (auto i = 0; i < v1.getSize(); ++i)
    {
        if (v1[i] != v2[i])
        {
            return true;
        }
    }
    return false;
}

template <typename X, typename Y>
bool operator!=(const Vector<X>& v1, const Vector<Y>& v2)
{
    return true;
}

template <typename X, typename Y>
bool operator==(const Vector<X>& v1, const Vector<Y>& v2)
{
    return false;
}
};
