#pragma once

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

        Chunk();
        ~Chunk() noexcept;

        const size_t Size() const;
        bool CanAdd() const;

        const T& GetFirst();
        const T& GetLast();

        void AddFirst(const T& item);
        void AddLast(const T& item);

        void RemoveFirst();
        void RemoveLast();

        T& operator[](int index) { return data[index]; }
        const T& operator[](int index) const { return data[index]; };
    };

    Chunk* _head = nullptr;     // Начало 
    Chunk* _tail = nullptr;     // Конец 
    int _size = 0;

    MyList(const MyList& other) = delete;               // Copy constructor.
    MyList& operator=(const MyList& other) = delete;    // Copy assignment operator.

public:
    MyList();
    ~MyList();

    MyList(MyList&& other) noexcept;            // Move constructor.
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

    void insertHead(const T& value);
    void insertTail(const T& value);

    void removeHead();
    void removeTail();

    const T& head() const;
    const T& tail() const;
    int size() const;

    //class Iterator;
    //Iterator iterator();
    //const Iterator iterator() const;
};