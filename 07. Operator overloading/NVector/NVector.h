#pragma once
#include <iostream>
class NVector
{
public:
    explicit NVector(size_t size);

    NVector(const NVector& other);
    NVector& operator=(const NVector& other);

    ~NVector();

    NVector& operator+=(const NVector& other);
    NVector& operator-=(const NVector& other);

    NVector& operator*=(size_t scalar);

    int& operator[](size_t index);
    int operator[](size_t index) const;

    size_t getSize() const;

    friend std::istream& operator>>(std::istream& is, NVector& nvector);
    friend std::ostream& operator<<(std::ostream& os, const NVector& nvector);
private:
    int* coordinates;
    size_t size;

    void free();
    void copyFrom(const NVector& other);
};

NVector operator+(const NVector& lhs, const NVector& rhs);
NVector operator-(const NVector& lhs, const NVector& rhs);

NVector operator*(const NVector& nvector, size_t scalar);
NVector operator*(size_t scalar, const NVector& nvector);

bool operator||(const NVector& lhs, const NVector& rhs);
bool operator|=(const NVector& lhs, const NVector& rhs);

size_t operator%(const NVector& lhs, const NVector& rhs);
