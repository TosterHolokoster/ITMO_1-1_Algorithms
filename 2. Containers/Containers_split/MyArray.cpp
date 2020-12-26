#include "MyArray.h"

template <typename T>
MyArray<T>::MyArray()
{
    _array = (T*)malloc(max_size * sizeof(T));
}
template <typename T>
MyArray<T>::MyArray(int size) : max_size(size)
{
    MyArray();
}
template <typename T>
MyArray<T>::~MyArray() noexcept
{
    free(_array);
}

template <typename T>
MyArray<T>::MyArray(const MyArray& other) : max_size(other.max_size), length(other.length), _array((T*)malloc(other.max_size * sizeof(T)))
{
    copy(other._array, other._array + length, _array);
}
template <typename T>
MyArray<T>::MyArray(MyArray&& other) noexcept : length(0), _array(nullptr)
{
    length = other.length;
    _array = other._array;

    other.length = 0;
    other._array = nullptr;
}

template <typename T>
void MyArray<T>::CheckCapacity()
{
    if (length >= max_size)
    {
        max_size = max_size << 1; // Multiply by 2
        T* newArray = (T*)malloc(max_size * sizeof(T));
        for (int i = 0; i < length; i++)
        {
            new (newArray + i) T(move(_array[i]));
        }
        free(_array);
        _array = newArray;
    }
}

template <typename T>
void MyArray<T>::insert(const T& newItem)
{
    CheckCapacity();
    new (_array + length) T(newItem);
    ++length;
}
template <typename T>
void MyArray<T>::insert(const T& newItem, int index)
{
    CheckCapacity();

    for (int i = ++length; i > index; i--)
    {
        _array[i] = move(_array[i - 1]);
    }
    _array[index] = newItem;
}

template <typename T>
void MyArray<T>::remove(int index)
{
    if (length > 0 && index < length)
    {
        length--;
        _array[length].~T();
        for (int i = index; i < length; i++)
        {
            _array[i] = move(_array[i + 1]);
        }
    }
}

template <typename T>
T& MyArray<T>::operator[](int index) { return _array[index]; }
template <typename T>
const T& MyArray<T>::operator[](int index) const { return _array[index]; }

template<typename T>
inline MyArray<T>::Iterator::Iterator(MyArray<T>* iteratorFor) : iteratorFor(iteratorFor), index(0) { }

template<typename T>
const T& MyArray<T>::Iterator::get() const
{
    return (*iteratorFor)[index];
}
template<typename T>
void MyArray<T>::Iterator::set(const T& value)
{
    iteratorFor[index] = value;
}

template<typename T>
void MyArray<T>::Iterator::insert(const T& value)
{
    iteratorFor->insert(value, index);
}
template<typename T>
void MyArray<T>::Iterator::remove()
{
    iteratorFor->remove(index);
}

template<typename T>
void MyArray<T>::Iterator::toIndex(int index)
{
    this.index = index;
}

template<typename T>
void MyArray<T>::Iterator::next() { index++; }
template<typename T>
void MyArray<T>::Iterator::prev() { index--; }

template<typename T>
bool MyArray<T>::Iterator::hasNext() const
{
    return index < iteratorFor->size();
}
template<typename T>
bool MyArray<T>::Iterator::hasPrev() const
{
    return index > 0;
}



/*
template <typename T>
class MyArray
{
private:
    T* _array;
    int max_size = 8;
    int length = 0;

public:

    // Default constructor.
    MyArray()
    {
        _array = new T[max_size];
    }

    // Constructor with size.
    MyArray(int size) : max_size(size)
    {
        MyArray();
    }

    // Copy constructor.
    MyArray(const MyArray& other) : max_size(other.max_size), length(other.length), _array(new T[other.max_size])
    {
        cout << "MyArray(const MyArray& other)" << endl;
        copy(other._array, other._array + length, _array);
    }

    // Move constructor.
    MyArray(MyArray&& other) noexcept : length(0), _array(nullptr)
    {
        cout << "MyArray(MyArray&& other)" << endl;

        length = other.length;
        _array = other._array;

        other.length = 0;
        other._array = nullptr;
    }

    // Destructor.
    ~MyArray() noexcept
    {
        delete[] _array;
    }

    void isNeedExpand()
    {
        if (length >= max_size)
        {
            max_size = max_size << 1;
            T* tmp = new T[max_size];
            move(_array, _array + length, tmp);
            _array = tmp;
        }
    }

    void insert(const T& newItem)
    {
        isNeedExpand();

        _array[length++] = move(newItem);
    }
    void insert(const T& newItem, int index)
    {
        isNeedExpand();

        for (int i = ++length; i > index; i--)
        {
            _array[i] = move(_array[i - 1]);
        }
        _array[index] = move(newItem);
    }

    void remove(int index)
    {
        if (length > 0 && index <= length)
        {
            for (int i = index; i < length; i++)
            {
                _array[i] = _array[i + 1];
            }
            length--;
        }
    }

    int size() const { return length; }

    // Copy assignment operator.
    MyArray& operator=(const MyArray& other)
    {
        cout << "MyArray& operator=(const MyArray& other)" << endl;
        if (this != &other)
        {
            delete[] _array;

            length = other.length;
            _array = new T[length];
            copy(other._array, other._array + length, _array);
        }
        return *this;
    }

    // Move assignment operator.
    MyArray& operator=(MyArray&& other) noexcept
    {
        cout << "MyArray& operator=(MyArray&& other)" << endl;
        if (this != &other)
        {
            delete[] _array;

            length = other.length;
            _array = other._array;

            other.length = 0;
            other._array = nullptr;
        }
        return *this;
    }

    T& operator[](int index) { return _array[index]; }
    const T& operator[](int index) const { return _array[index]; }

private:
    class Iterator
    {
    private:
        MyArray<T>* iteratorFor;
        int index;

    public:
        Iterator(MyArray<T>* iteratorFor) : iteratorFor(iteratorFor), index(0) { }

        const T& get() const
        {
            return (*iteratorFor)[index];
        }

        void set(const T& value)
        {
            iteratorFor[index] = value;
        }

        void insert(const T& value)
        {
            iteratorFor->insert(value, index);
        }

        void remove()
        {
            iteratorFor->remove(index);
        }

        void toIndex(int index) { this.index = index; }

        void next() { index++; }
        void prev() { index--; }

        bool hasNext() const { return index != iteratorFor->size() - 1; }
        bool hasPrev() const { return index != 0; }

    };

public:
    Iterator iterator() { return Iterator(this); }
    const Iterator iterator() const { return Iterator(this); }
};
*/
