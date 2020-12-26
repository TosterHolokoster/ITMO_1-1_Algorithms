#pragma once
#include <utility>
#include <stdlib.h>

template <typename T>
class MyArray
{
private:
    class Iterator
    {
    private:
        MyArray<T>* iteratorFor;
        int index;
    public:
        Iterator(MyArray<T>* iteratorFor) : iteratorFor(iteratorFor), index(0) { }
        
        const T& get() const { return (*iteratorFor)[index]; }
        void set(const T& value) { (*iteratorFor)[index] = value; }

        void insert(const T& value) { iteratorFor->insert(value, index); }
        void remove() { iteratorFor->remove(index); }

        void toIndex(int index) { this->index = index; }

        void next() { index++; }
        void prev() { index--; }

        bool hasNext() const { return (index + 1) < iteratorFor->size(); }
        bool hasPrev() const { return index > 0; }
    };

    T* _array;
    int max_size = 8;
    int length = 0;

    void CheckCapacity()
    {
        if (length >= max_size)
        {
            max_size = max_size << 1; // Multiply by 2
            T* newArray = (T*)malloc(max_size * sizeof(T));
            for (int i = 0; i < length; i++)
            {
                new (newArray + i) T(std::move(_array[i]));
            }
            free(_array);
            _array = newArray;
        }
    }

public:
    MyArray() { _array = (T*)malloc(max_size * sizeof(T)); }
    ~MyArray() noexcept { free(_array); }

    MyArray(int size) : max_size(size) { MyArray(); }

    MyArray(const MyArray& other) : max_size(other.max_size), length(other.length), _array((T*)malloc(other.max_size * sizeof(T)))
    {
        copy(other._array, other._array + length, _array);
    }
    MyArray& operator=(const MyArray& other)
    {
        if (this != &other)
        {
            free(_array);

            length = other.length;
            _array = (T*)malloc(max_size * sizeof(T));
            copy(other._array, other._array + length, _array);
        }
        return *this;
    }

    MyArray(MyArray&& other) noexcept : length(0), _array(nullptr)
    {
        length = other.length;
        _array = other._array;

        other.length = 0;
        other._array = nullptr;
    }
    MyArray& operator=(MyArray&& other) noexcept
    {
        if (this != &other)
        {
            free(_array);

            length = other.length;
            _array = other._array;

            other.length = 0;
            other._array = nullptr;
        }
        return *this;
    }

    void insert(const T& newItem)
    {
        CheckCapacity();
        new (_array + length) T(newItem);
        ++length;
    }
    void insert(const T& newItem, int index)
    {
        CheckCapacity();

        for (int i = ++length; i > index; i--)
        {
            _array[i] = std::move(_array[i - 1]);
        }
        _array[index] = newItem;
    }

    void remove(int index)
    {
        if (length > 0 && index < length)
        {
            length--;
            _array[length].~T();
            for (int i = index; i < length; i++)
            {
                _array[i] = std::move(_array[i + 1]);
            }
        }
    }

    int size() const { return length; }

    T& operator[](int index) { return _array[index]; }
    const T& operator[](int index) const { return _array[index]; }

    Iterator iterator() { return Iterator(this); }
    const Iterator iterator() const { return Iterator(this); }
};