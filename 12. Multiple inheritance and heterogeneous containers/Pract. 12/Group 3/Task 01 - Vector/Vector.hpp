#include <iostream>

template <typename T>
class Vector {
public:
    Vector();
    explicit Vector(size_t size);
    
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    bool empty() const;
    size_t size() const;

    void push_back(const T& obj);
    void push_back(T&& obj);
    void pop_back();

    void insert(size_t index, const T& obj);
    void insert(size_t index, T&& obj);
    void erase(size_t index);

    void clear();

    const T& operator[](size_t index) const;
    T& operator[](size_t index);

private:
    T* data = nullptr;
    size_t count = 0;
    size_t capacity = 0;
    
    void resize(size_t newCapacity);
    void free();
    void copyFrom(const Vector& other);
    void moveFrom(Vector&& other) noexcept;
};

template<typename T>
Vector<T>::Vector() : Vector(0) {}

template<typename T>
Vector<T>::Vector(size_t size) : count(size)
{
    capacity = dataToAllocBySize(size);
    data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
    copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
    moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
Vector<T>::~Vector()
{
    free();
}

template<typename T>
bool Vector<T>::empty() const
{
    return count == 0;
}

template<typename T>
size_t Vector<T>::size() const
{
    return count;
}

template<typename T>
void Vector<T>::push_back(const T& obj)
{
    if (count >= capacity) {
        resize(capacity * 2);
    }

    data[count++] = obj;
}

template<typename T>
void Vector<T>::push_back(T&& obj)
{
    if (count >= capacity) {
        resize(capacity * 2);
    }

    data[count++] = std::move(obj);
}

template<typename T>
void Vector<T>::pop_back()
{
    if (empty()) {
        throw std::length_error("Vector is already empty!");
    }

    count--;

    if (count * 4 <= capacity && capacity > 1) {
        resize(capacity / 2);
    }
}

template<typename T>
void Vector<T>::insert(size_t index, const T& obj)
{
    if (index >= count) {
        throw std::out_of_range("Index out of range!");
    }

    if (count >= capacity) {
        resize(capacity * 2);
    }

    for (size_t i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = obj;
    count++;
}

template<typename T>
void Vector<T>::insert(size_t index, T&& obj)
{
    if (index >= count) {
        throw std::out_of_range("Index out of range!");
    }

    if (count >= capacity) {
        resize(capacity * 2);
    }

    for (size_t i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = std::move(obj);
    count++;
}

template<typename T>
void Vector<T>::erase(size_t index)
{
    if (index >= count) {
        throw std::out_of_range("Index out of range!");
    }

    for (size_t i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }
    count--;

    if (count * 4 <= capacity && capacity > 1) {
        resize(capacity / 2);
    }
}

template<typename T>
void Vector<T>::clear()
{
    count = 0;
    capacity = dataToAllocBySize(count);
    delete[] data;
    data = new T[capacity];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return data[index];
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
    return data[index];
}

template<typename T>
void Vector<T>::resize(size_t newCapacity)
{
    T* resizedData = new T[newCapacity];
    for (size_t i = 0; i < count; i++) {
        resizedData[i] = data[i];
    }
    capacity = newCapacity;
}

template<typename T>
void Vector<T>::free()
{
    delete[] data;
    data = nullptr;
    capacity = count = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector& other)
{
    data = new T[other.capacity];
    for (size_t i = 0; i < other.count; i++) {
        data[i] = other.data[i];
    }
    capacity = other.capacity;
    count = other.count;
}

template<typename T>
void Vector<T>::moveFrom(Vector&& other) noexcept
{
    data = other.data;
    other.data = nullptr;
    capacity = other.capacity;
    other.capacity = 0;
    count = other.count;
    other.count = 0;
}

static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocBySize(size_t size)
{
    return std::max(roundToPowerOfTwo(size + 1), 16u);
}
