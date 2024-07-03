#pragma once
#include <iostream>

template <typename T>
class Queue
{
public:
    Queue();

    Queue(const Queue<T>& other);
    Queue(Queue<T>&& other) noexcept;

    Queue& operator=(const Queue<T>& other);
    Queue& operator=(Queue<T>&& other);

    ~Queue();

    void push(const T& obj);
    void push(T&& obj);

    void pop();

    const T& peek() const;
    bool isEmpty() const;
private:
    T* data;
    size_t size;
    size_t capacity;

    size_t get;
    size_t put;

    void resize();
    void copyFrom(const Queue<T>& other);
    void moveFrom(Queue<T>&& other) noexcept;
    void free();
};

template<typename T>
Queue<T>::Queue() : capacity(4), size(0), get(0), put(0)
{
    data = new T[capacity];
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other)
{
    copyFrom(other);
}

template<typename T>
Queue<T>::Queue(Queue<T>&& other) noexcept
{
    moveFrom(std::move(other));
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other)
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
Queue<T>::~Queue()
{
    free();
}

template<typename T>
inline void Queue<T>::push(const T& obj)
{
    if (size == capacity) {
        resize();
    }

    data[put] = obj;
    (++put) %= capacity;
    size++;
}

template<typename T>
void Queue<T>::push(T&& obj)
{
    if (size == capacity) {
        resize();
    }

    data[put] = std::move(obj);
    (++put) %= capacity;
    size++;
}

template<typename T>
void Queue<T>::pop()
{
    if (isEmpty()) {
        throw std::out_of_range("Queue is already empty!");
    }
    size--;
    (++get) %= capacity;
}

template<typename T>
const T& Queue<T>::peek() const
{
    if (isEmpty()) {
        throw std::out_of_range("Queue is already empty!");
    }
    return data[get];
}

template<typename T>
bool Queue<T>::isEmpty() const
{
    return size == 0;
}

template<typename T>
void Queue<T>::resize()
{
    T* resized = new T[capacity * 2];
    for (size_t i = 0; i < size; i++) {
        resized[i] = data[get];
        (++get) %= capacity;
    }
    capacity *= 2;
    delete[] data;
    data = resized;
    get = 0;
    put = size;
}

template<typename T>
void Queue<T>::copyFrom(const Queue<T>& other)
{
    data = new T[other.capacity];
    for (size_t i = 0; i < other.size; i++) {
        data[i] = other.data[i];
    }
    get = other.get;
    put = other.put;
    size = other.size;
    capacity = other.capacity;
}

template<typename T>
void Queue<T>::moveFrom(Queue<T>&& other) noexcept
{
    data = other.data;
    other.data = nullptr;
    get = other.get;
    other.get = 0;
    put = other.put;
    other.put = 0;
    size = other.size;
    other.size = 0;
    capacity = other.capacity;
    other.capacity = 0;
}

template<typename T>
void Queue<T>::free()
{
    delete data;
    size = capacity = 0;
    get = put = 0;
}
