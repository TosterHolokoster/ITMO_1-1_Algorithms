#pragma once

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
        Iterator(MyArray<T>* iteratorFor);
        const T& get() const;
        void set(const T& value);

        void insert(const T& value);
        void remove();

        void toIndex(int index);

        void next();
        void prev();

        bool hasNext() const;
        bool hasPrev() const;
    };

    T* _array;
    int max_size = 8;
    int length = 0;

public:
    MyArray();
    ~MyArray() noexcept;

    MyArray(int size);

    MyArray(const MyArray& other); // Copy constructor.
    MyArray& operator=(const MyArray& other) // Copy assignment operator.
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

    MyArray(MyArray&& other) noexcept; // Move constructor.
    MyArray& operator=(MyArray&& other) noexcept // Move assignment operator.
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

    void CheckCapacity();

    void insert(const T& newItem);
    void insert(const T& newItem, int index);

    void remove(int index);

    int size() const { return length; }

    T& operator[](int index);
    const T& operator[](int index) const;

    Iterator iterator() { return Iterator(this); }
    const Iterator iterator() const { return Iterator(this); }
};