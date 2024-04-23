#include "StringVector.h"

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

StringVector::StringVector() : StringVector(0) {}

StringVector::StringVector(size_t size) : stringsCount(size)
{
    capacity = dataToAllocBySize(size);
    strings = new MyString[capacity];
}

StringVector::StringVector(const StringVector& other)
{
    copyFrom(other);
}

StringVector::StringVector(StringVector&& other) noexcept
{
    moveFrom(std::move(other));
}

StringVector& StringVector::operator=(const StringVector& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

StringVector& StringVector::operator=(StringVector&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

StringVector::~StringVector()
{
    free();
}

void StringVector::push_back(const MyString& str)
{
    if (stringsCount >= capacity) {
        resize(capacity * 2);
    }

    strings[stringsCount++] = str;
}

void StringVector::push_back(MyString&& str)
{
    if (stringsCount >= capacity) {
        resize(capacity * 2);
    }

    strings[stringsCount++] = std::move(str);
}

void StringVector::pop_back()
{
    if (empty()) {
        throw std::length_error("Vector is already empty!");
    }

    stringsCount--;

    if (stringsCount * 4 <= capacity && capacity > 1) {
        resize(capacity / 2);
    }
}

void StringVector::insert(size_t index, const MyString& str)
{
    if (index >= stringsCount) {
        throw std::out_of_range("Index out of range!");
    }

    if (stringsCount >= capacity) {
        resize(capacity * 2);
    }

    for (size_t i = stringsCount; i > index; i--) {
        strings[i] = strings[i - 1];
    }
    strings[index] = str;
    stringsCount++;
}

void StringVector::insert(size_t index, MyString&& str)
{
    if (index >= stringsCount) {
        throw std::out_of_range("Index out of range!");
    }

    if (stringsCount >= capacity) {
        resize(capacity * 2);
    }

    for (size_t i = stringsCount; i > index; i--) {
        strings[i] = strings[i - 1];
    }
    strings[index] = std::move(str);
    stringsCount++;
}

void StringVector::erase(size_t index)
{
    if (index >= stringsCount) {
        throw std::out_of_range("Index out of range!");
    }

    for (size_t i = index; i < stringsCount - 1; i++) {
        strings[i] = strings[i + 1];
    }
    stringsCount--;

    if (stringsCount * 4 <= capacity && capacity > 1) {
        resize(capacity / 2);
    }
}

void StringVector::clear()
{
    stringsCount = 0;
    resize(dataToAllocBySize(stringsCount));
}

MyString& StringVector::operator[](size_t index)
{
    return strings[index];
}

const MyString& StringVector::operator[](size_t index) const
{
    return strings[index];
}

bool StringVector::empty() const
{
    return stringsCount == 0;
}

size_t StringVector::size() const
{
    return stringsCount;
}

void StringVector::resize(size_t newCapacity)
{
    MyString* resizedStrings = new MyString[newCapacity];
    for (size_t i = 0; i < stringsCount; i++) {
        resizedStrings[i] = strings[i];
    }
    delete[] strings;
    strings = resizedStrings;
    capacity = newCapacity;
}

void StringVector::free()
{
    delete[] strings;
    strings = nullptr;
    stringsCount = capacity = 0;
}

void StringVector::copyFrom(const StringVector& other)
{
    stringsCount = other.stringsCount;
    capacity = other.capacity;
    strings = new MyString[capacity];
    for (size_t i = 0; i < stringsCount; i++) {
        strings[i] = other.strings[i];
    }
}

void StringVector::moveFrom(StringVector&& other)
{
    stringsCount = other.stringsCount;
    other.stringsCount = 0;

    capacity = other.capacity;
    other.capacity = 0;

    strings = other.strings;
    other.strings = nullptr;
}

std::istream& operator>>(std::istream& is, StringVector& sv) 
{
    size_t vectorSize;
    is >> vectorSize;

    sv.clear();
    MyString str;
    for (size_t i = 0; i < vectorSize; i++) {
        is >> str;
        sv.push_back(str);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const StringVector& sv)
{
    for (size_t i = 0; i < sv.size(); i++) {
        os << sv[i] << ' ';
    }
    return os;
}
