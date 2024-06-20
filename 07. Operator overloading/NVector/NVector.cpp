#include "NVector.h"

NVector::NVector(size_t size) : size(size)
{
    coordinates = new int[size] {0};
}

NVector::NVector(const NVector& other)
{
    copyFrom(other);
}

NVector& NVector::operator=(const NVector& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

NVector::~NVector()
{
    free();
}

NVector& NVector::operator+=(const NVector& other)
{
    if (size != other.size) {
        throw "Vectors should have the same size!";
    }

    for (size_t i = 0; i < size; i++) {
        coordinates[i] += other.coordinates[i];
    }
    return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
    if (size != other.size) {
        throw "Vectors should have the same size!";
    }

    for (size_t i = 0; i < size; i++) {
        coordinates[i] -= other.coordinates[i];
    }
    return *this;
}

NVector& NVector::operator*=(size_t scalar)
{
    for (size_t i = 0; i < size; i++) {
        coordinates[i] *= scalar;
    }
    return *this;
}

int& NVector::operator[](size_t index)
{
    return coordinates[index];
}

int NVector::operator[](size_t index) const
{
    return coordinates[index];
}

size_t NVector::getSize() const
{
    return size;
}

void NVector::free()
{
    delete[] coordinates;
    coordinates = nullptr;
    size = 0;
}

void NVector::copyFrom(const NVector& other)
{
    coordinates = new int[other.size];
    for (size_t i = 0; i < other.size; i++) {
        coordinates[i] = other.coordinates[i];
    }
    size = other.size;
}

std::istream& operator>>(std::istream& is, NVector& nvector)
{
    for (size_t i = 0; i < nvector.size; i++) {
        is >> nvector[i];
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const NVector& nvector)
{
    os << "[ ";
    for (size_t i = 0; i < nvector.size; i++) {
        os << nvector[i] << " ";
    }
    os << " ]";
    return os;
}   

NVector operator+(const NVector& lhs, const NVector& rhs)
{
    NVector result(lhs);
    result += rhs;
    return result;
}

NVector operator-(const NVector& lhs, const NVector& rhs)
{
    NVector result(lhs);
    result -= rhs;
    return result;
}

NVector operator*(const NVector& nvector, size_t scalar)
{
    NVector result(nvector);
    result *= scalar;
    return result;
}

NVector operator*(size_t scalar, const NVector& nvector)
{
    return nvector * scalar;
}

bool operator||(const NVector& lhs, const NVector& rhs)
{
    size_t size = lhs.getSize();
    if (size != rhs.getSize()) {
        throw "Vectors should have the same size!";
    }

    double ratio = 0.0;
    bool ratioSet = false;

    for (size_t i = 0; i < size; i++) {
        if (lhs[i] == 0 && rhs[i] == 0) {
            continue;
        }

        if (lhs[i] == 0 || rhs[i] == 0) {
            return false;
        }

        double currentRatio = lhs[i] / rhs[i];

        if (!ratioSet) {
            ratio = currentRatio;
            ratioSet = true;
        }
        else if (std::abs(ratio - currentRatio) > 1e-6) {
            return false;
        }
    }
    return true;
}

bool operator|=(const NVector& lhs, const NVector& rhs)
{
    return lhs % rhs == 0;
}

size_t operator%(const NVector& lhs, const NVector& rhs)
{
    size_t size = lhs.getSize();
    if (size != rhs.getSize()) {
        throw "Vectors should have the same size!";
    }

    size_t result = 0;
    for (size_t i = 0; i < size; i++) {
        result += lhs[i] * rhs[i];
    }
    return result;
}
