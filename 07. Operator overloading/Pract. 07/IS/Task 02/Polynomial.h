#pragma once
#include <iostream>

class Polynomial {
private:
    size_t degree = 0;
    int* coefficients = nullptr;
    
    void free();
    void copyCoefficients(const int* coefficients, size_t size);
    void copyFrom(const Polynomial& other);
public:
    Polynomial() = default;
    explicit Polynomial(size_t degree);
    Polynomial(size_t degree, int* coefficients);

    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    ~Polynomial();

    size_t getDegree() const;

    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(int num);

    int operator()(int num) const;
    int operator[](size_t degree) const;
    int& operator[](size_t degree);

    friend std::istream& operator>>(std::istream& is, Polynomial& p);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
};
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs);
Polynomial operator*(const Polynomial& p, int num);
Polynomial operator*(int num, const Polynomial& p);
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
