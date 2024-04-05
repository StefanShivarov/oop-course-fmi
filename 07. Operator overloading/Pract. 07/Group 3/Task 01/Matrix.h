#pragma once
#include <iostream>

constexpr size_t DEFAULT_DIMENSION = 2;

class Matrix {
private:
    size_t rows = DEFAULT_DIMENSION;
    size_t cols = DEFAULT_DIMENSION;
    int** data = nullptr;

    void free();
    void copyFrom(const Matrix& other);
public:
    Matrix();
    Matrix(size_t rows, size_t cols);

    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    ~Matrix();

    size_t getRows() const;
    size_t getCols() const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(int scalar);

    int* operator[](size_t index);
    const int* operator[](size_t index) const;

    operator bool() const;

    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& matrix, int scalar);
Matrix operator*(int scalar, const Matrix& matrix);

bool operator==(const Matrix& lhs, const Matrix& rhs);
bool operator!=(const Matrix& lhs, const Matrix& rhs);
