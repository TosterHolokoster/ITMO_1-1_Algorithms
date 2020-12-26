#include "MyList.h"

using namespace std;

template<typename T>
MyList<T>::Chunk::Chunk()
{
    data = (T*)malloc(chunk_size * sizeof(T));
}
template<typename T>
MyList<T>::Chunk::~Chunk() noexcept
{
    free(data);
}

template<typename T>
const size_t MyList<T>::Chunk::Size() const
{
    return size;
}
template<typename T>
inline bool MyList<T>::Chunk::CanAdd() const
{
    return size < chunk_size;
}

template<typename T>
const T& MyList<T>::Chunk::GetFirst()
{
    return data[0];
}
template<typename T>
const T& MyList<T>::Chunk::GetLast()
{
    return data[size - 1];
}

template<typename T>
void MyList<T>::Chunk::AddFirst(const T& item)
{
    AddLast(item);
    for (int i = 0; i < size; i++)
    {
        swap(data[i], data[size - 1]);
    }

    //size++;
    //for (int i = size; i > 0; i--)
    //{
    //    data[i] = move(data[i - 1]);
    //}
    //data[0] = item;
}
template<typename T>
void MyList<T>::Chunk::AddLast(const T& item)
{
    new (data + size) T(item);
    size++;
}

template<typename T>
void MyList<T>::Chunk::RemoveFirst()
{
    if (size > 0)
    {
        size--;
        (data)->~T();

        for (int i = 0; i < size; i++)
        {
            data[i] = move(data[i + 1]);
        }
    }
}
template<typename T>
void MyList<T>::Chunk::RemoveLast()
{
    if (size > 0)
    {
        size--;
        (data + size)->~T();
    }
}

template<typename T>
MyList<T>::MyList()
{
    _tail = _head = new Chunk();
}
template<typename T>
MyList<T>::~MyList()
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

template<typename T>
MyList<T>::MyList(MyList&& other) noexcept : _head(nullptr), _head(_tail), _size(0)
{
    _head = other._head;
    _tail = other._tail;
    _size = other._size;

    other._head = nullptr;
    other._tail = nullptr;
    other._size = 0;
}

template<typename T>
void MyList<T>::insertHead(const T& value)
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
template<typename T>
void MyList<T>::insertTail(const T& value)
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

template<typename T>
void MyList<T>::removeHead()
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
template<typename T>
void MyList<T>::removeTail()
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

template<typename T>
const T& MyList<T>::head() const
{
    return _head->GetFirst();
}
template<typename T>
const T& MyList<T>::tail() const
{
    return _tail->GetLast();
}
template<typename T>
int MyList<T>::size() const
{
    return _size;
}

/*
template<typename T>
class MyList
{
private:
    struct Node
    {
        T data;
        Node* next = nullptr;
        Node* previous = nullptr;
    };

    Node* _head = nullptr; // Конец 
    Node* _tail = nullptr; // Начало 

    int _size = 0;

public:
    MyList() { cout << "Execute Default constructor" << endl; }

    // Copy constructor.
    MyList(const MyList& other)
    {
        cout << "Execute Copy constructor" << endl;
        CopyList(other);
    }

    // Move constructor.
    MyList(MyList&& other) noexcept
    {
        cout << "Execute Move constructor" << endl;

        _head = other._head;
        _tail = other._tail;
        _size = other._size;

        other._head = nullptr;
        other._tail = nullptr;
        other._size = 0;
    }

    ~MyList()
    {
        if (_size > 0)
        {
            Node* tmp = _tail;
            while (tmp != nullptr)
            {
                Node* tmp_next = tmp->next;
                delete tmp;
                tmp = tmp_next;
            }
        }
    }

    void insertHead(const T& value)
    {
        Node* newNode = new Node();
        newNode->data = value;
        if (_head)
        {
            newNode->previous = _head;
            _head->next = newNode;
        }
        else
        {
            _tail = newNode;
        }
        _head = newNode;
        _size++;
    }
    void insertTail(const T& value)
    {
        Node* newNode = new Node();
        newNode->data = value;
        if (_tail)
        {
            newNode->next = _tail;
            _tail->previous = newNode;
        }
        else
        {
            _head = newNode;
        }
        _tail = newNode;
        _size++;
    }

    void removeHead()
    {
        if (_head)
        {
            Node* newHead = nullptr;
            if (_head->previous)
            {
                newHead = _head->previous;
                newHead->next = nullptr;
            }

            delete _head;
            _head = newHead;
            _size--;
        }
    }
    void removeTail()
    {
        if (_tail)
        {
            Node* newTail = nullptr;
            if (_tail->next)
            {
                newTail = _tail->next;
                newTail->previous = nullptr;
            }

            delete _tail;
            _tail = newTail;
            _size--;
        }
    }

    int size() const { return _size; }

    const T& head() const
    {
        if (_head)
            return _head->data;
    }
    const T& tail() const
    {
        if (_tail)
            return _tail->data;
    }

    // Copy assignment operator.
    MyList& operator=(const MyList& other)
    {
        cout << "Execute Copy assignment operator." << endl;
        if (this != &other)
        {
            Node* start = _tail;
            for (int i = 0; i < _size; i++)
            {
                Node* tmp_next = start->next;
                delete start;
                start = tmp_next;
            }
            _tail = nullptr;
            _head = nullptr;
            _size = 0;

            CopyList(other);
        }
        return *this;
    }

    // Move assignment operator.
    MyList& operator=(MyList&& other) noexcept
    {
        cout << "Execute Move assignment operator." << endl;
        if (this != &other)
        {
            _size = other._size;
            _head = other._head;
            _tail = other._tail;

            other._size = 0;
            other._head = nullptr;
            other._tail = nullptr;
        }
        return *this;
    }

    void Print()
    {
        cout << "Size: " << size() << "; ";
        cout << "Tail: " << tail() << "; ";
        cout << "Head: " << head() << endl;
    }

private:
    void CopyList(const MyList& other)
    {
        if (other._size != 0)
        {
            _tail = new Node();
            _tail->data = other._tail->data;
            if (other._size == 1)
            {
                _head = _tail;
            }
            else
            {
                Node* tmp_prev = _tail;
                for (Node* i = other._tail->next; i != other._head; i = i->next)
                {
                    Node* tmp_next = new Node();
                    tmp_next->data = i->data;
                    tmp_next->previous = tmp_prev;
                    tmp_prev->next = tmp_next;
                    tmp_prev = tmp_next;
                }
                _head = new Node();
                _head->data = other._head->data;
                tmp_prev->next = _head;
                _head->previous = tmp_prev;
            }
            _size = other._size;
        }
    }

    class Iterator
    {
    private:
        Node* currentNode;

    public:
        Iterator(Node* currentNode) : currentNode(currentNode) { }

        const T& get() const
        {
            return currentNode->data;
        }

        void set(const T& value)
        {
            currentNode->data = value;
        }

        void insert(const T& value)
        {
            Node* newNode = new Node();
            newNode->data = value;
            newNode->previous = currentNode;
            newNode->next = currentNode->next;

            currentNode->next->previous = newNode;
            currentNode->next = newNode;
        }

        void remove()
        {
            currentNode->previous->next = currentNode->next;
            currentNode->next->previous = currentNode->previous;
            Node* tmp = currentNode->next;
            delete currentNode;
            currentNode = tmp;
        }

        void next() { currentNode = currentNode->next; }
        void prev() { currentNode = currentNode->previous; }

        bool hasNext() const { return currentNode->next != nullptr; }
        bool hasPrev() const { return currentNode->previous != nullptr; }

    };

public:
    Iterator iterator() { return Iterator(_tail); }
    const Iterator iterator() const { return Iterator(_tail); }
};
*/