#pragma once
#include <utility>
#include <stdlib.h>

template<typename T>
class MyList
{
    struct Chunk
    {
    private:
        T* data = nullptr;
        size_t size = 0;

    public:
        Chunk* next = nullptr;
        Chunk* previous = nullptr;
        static const size_t chunk_size = 16;

        Chunk() { data = (T*)malloc(chunk_size * sizeof(T)); }
        ~Chunk() noexcept { free(data); }

        const size_t Size() const { return size; }
        bool CanAdd() const { return size < chunk_size; }

        const T& GetLast() { return data[size - 1]; }
        const T& GetFirst() { return data[0]; }

        void Set(size_t index, const T& item)
        {
            (data + index)->~T();
            new (data + index) T(item);
        }

        void AddLast(const T& item)
        {
            new (data + size) T(item);
            size++;
        }
        void AddToIndex(size_t index, const T& item)
        {
            AddLast(item);
            for (size_t i = index; i < size; i++)
            {
                std::swap(data[i], data[size - 1]);
            }
        }
        void AddFirst(const T& item)
        {
            AddToIndex(0, item);
        }

        void RemoveLast()
        {
            if (size > 0)
            {
                size--;
                (data + size)->~T();
            }
        }
        void RemoveByIndex(size_t index)
        {
            if (size > 0)
            {
                size--;
                (data + index)->~T();

                for (size_t i = index; i < size; i++)
                {
                    data[i] = std::move(data[i + 1]);
                }
            }
        }
        void RemoveFirst()
        {
            RemoveByIndex(0);
        }

        T& operator[](int index) { return data[index]; }
        const T& operator[](int index) const { return data[index]; };
    };

    class Iterator
    {
    private:
        Chunk* currentChunk;
        size_t currentChunkIndex;
        size_t index;

    public:
        Iterator(Chunk* _head) : currentChunk(_head), currentChunkIndex(0), index(0) { }

        const T& get() const
        {
            return (*currentChunk)[currentChunkIndex];
        }

        void set(const T& value)
        {
            currentChunk->Set(currentChunkIndex, value);
        }

        void insert(const T& value)
        {
            currentChunk->AddToIndex(currentChunkIndex, value);
            index++;
        }

        void remove()
        {
            currentChunk->RemoveByIndex(currentChunkIndex);
            index--;
        }

        void next()
        {
            currentChunkIndex++;
            if (currentChunkIndex == currentChunk->Size())
            {
                currentChunk = currentChunk->next;
                currentChunkIndex = 0;
            }
        }
        void prev()
        {
            if (currentChunkIndex == 0)
            {
                currentChunk = currentChunk->previous;
                currentChunkIndex = currentChunk->Size();
            }
            else
                currentChunkIndex--;
        }

        bool hasNext() const { return currentChunkIndex != currentChunk->Size() - 1 || currentChunk->next != nullptr; }
        bool hasPrev() const { return currentChunkIndex != 0 || currentChunk->previous != nullptr; }
    };

    Chunk* _head = nullptr;     // Start 
    Chunk* _tail = nullptr;     // End 
    int _size = 0;

    MyList(const MyList& other) = delete;               // Copy constructor.
    MyList& operator=(const MyList& other) = delete;    // Copy assignment operator.

public:
    MyList() { _tail = _head = new Chunk(); }
    ~MyList()
    {
        if (_size > 0)
        {
            Chunk* tmp = _head;
            while (tmp != nullptr)
            {
                Chunk* tmp_next = tmp->next;
                delete tmp;
                tmp = tmp_next;
            }
        }
    }

    MyList(MyList&& other) noexcept : _head(nullptr), _head(_tail), _size(0)
    {
        _head = other._head;
        _tail = other._tail;
        _size = other._size;

        other._head = nullptr;
        other._tail = nullptr;
        other._size = 0;
    }
    MyList& operator=(MyList&& other) noexcept  // Move assignment operator.
    {
        if (this != &other)
        {
            if (_size > 0)
            {
                Chunk* tmp = _head;
                while (tmp != nullptr)
                {
                    Chunk* tmp_next = tmp->next;
                    delete tmp;
                    tmp = tmp_next;
                }
            }

            _head = other._head;
            _tail = other._tail;
            _size = other._size;

            other._head = nullptr;
            other._tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    void insertHead(const T& value)
    {
        if (!_head->CanAdd())
        {
            _head->previous = new Chunk();
            _head->previous->next = _head;
            _head = _head->previous;
        }
        _head->AddFirst(value);
        _size++;
    }
    void insertTail(const T& value)
    {
        if (!_tail->CanAdd())
        {
            _tail->next = new Chunk();
            _tail->next->previous = _tail;
            _tail = _tail->next;
        }
        _tail->AddLast(value);
        _size++;
    }

    void removeHead()
    {
        _head->RemoveFirst();
        if (_head != _tail && _head->Size() == 0)
        {
            Chunk* newHead = _head->next;
            delete _head;
            _head = newHead;
        }
        _size--;
    }
    void removeTail()
    {
        _tail->RemoveLast();
        if (_head != _tail && _tail->Size() == 0)
        {
            Chunk* newTail = _tail->previous;
            delete _tail;
            _tail = newTail;
        }
        _size--;
    }

    const T& head() const { return _head->GetFirst(); }
    const T& tail() const { return _tail->GetLast(); }
    int size() const { return _size; }

    Iterator iterator() { return Iterator(_head); }
    const Iterator iterator() const { return Iterator(_head); }
};