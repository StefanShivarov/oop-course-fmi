#pragma once
#include "MyString.h"
#include <iostream>

class StringVector
{
public:
    StringVector();
    explicit StringVector(size_t size);

    StringVector(const StringVector& other);
    StringVector(StringVector&& other) noexcept;

    StringVector& operator=(const StringVector& other);
    StringVector& operator=(StringVector&& other) noexcept;

    ~StringVector();

    void push_back(const MyString& str);
    void push_back(MyString&& str);
    void pop_back();

    void insert(size_t index, const MyString& str);
    void insert(size_t index, MyString&& str);
    void erase(size_t index);

    void clear();

    MyString& operator[](size_t index);
    const MyString& operator[](size_t index) const;

    bool empty() const;

    size_t size() const;

private:
    MyString* strings = nullptr;
    size_t stringsCount = 0;
    size_t capacity = 0;

    void resize(size_t newCapacity);
    void free();
    void copyFrom(const StringVector& other);
    void moveFrom(StringVector&& other);
};

std::istream& operator>>(std::istream& is, StringVector& sv);
std::ostream& operator<<(std::ostream& os, const StringVector& sv);
