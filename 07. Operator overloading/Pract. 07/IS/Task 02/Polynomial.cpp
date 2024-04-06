#include "Polynomial.h"

namespace HelperFunctions {
    int power(int num, size_t degree) {
        if (num == 0) {
            return 0;
        }

        int result = 1;
        for (size_t i = 0; i < degree; i++) {
            result *= num;
        }
        return result;
    }
}

void Polynomial::free() {
    delete[] coefficients;
    coefficients = nullptr;
    degree = 0;
}

void Polynomial::copyCoefficients(const int* coefficients, size_t degree) {
    if (!coefficients) {
        return;
    }

    for (size_t i = 0; i <= degree; i++) {
        this->coefficients[i] = coefficients[i];
    }
}

void Polynomial::copyFrom(const Polynomial& other) {
    degree = other.degree;
    coefficients = new int[other.degree + 1] {};
    copyCoefficients(other.coefficients, degree);
}

Polynomial::Polynomial(size_t degree) {
    this->degree = degree;
    coefficients = new int[degree + 1] {};
}

Polynomial::Polynomial(size_t degree, int* coefficients): Polynomial(degree) {
    copyCoefficients(coefficients, degree);
}

Polynomial::Polynomial(const Polynomial& other) {
    copyFrom(other);
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Polynomial::~Polynomial() {
    free();
}

size_t Polynomial::getDegree() const {
    return degree;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    Polynomial result(std::max(degree, other.degree));
    result.copyCoefficients(coefficients, degree);

    for (size_t i = 0; i <= other.degree; i++) {
        result.coefficients[i] += other.coefficients[i];
    }

    *this = result;
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    Polynomial result(std::max(degree, other.degree));
    result.copyCoefficients(coefficients, degree);

    for (size_t i = 0; i <= other.degree; i++) {
        result.coefficients[i] -= other.coefficients[i];
    }

    while (result.degree > 0 && result.coefficients[result.degree] == 0) {
        result.degree--;
    }

    *this = result;
    return *this;
}

Polynomial& Polynomial::operator*=(int num) {
    if (num == 0) {
        *this = Polynomial(0);
    }

    for (size_t i = 0; i <= degree; i++) {
        coefficients[i] *= num;
    }
    return *this;
}

int Polynomial::operator()(int num) const {
    int result = 0;
    for (size_t i = 0; i <= degree; i++) {
        result += coefficients[i] * HelperFunctions::power(num, i);
    }
    return result;
}

int Polynomial::operator[](size_t degree) const {
    if (this->degree < degree) {
        return 0;
    }
    return coefficients[degree];
}

int& Polynomial::operator[](size_t degree) {
    return coefficients[degree];
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    size_t degree;
    is >> degree;
    p = Polynomial(degree);

    for (size_t i = 0; i <= p.degree; i++) {
        is >> p[i];
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    for (size_t i = p.degree; i >= 1; i--) {
        if (p[i] != 0) {
            os << p[i] << 'x';
            if (i > 1) {
                os << '^' << i;
            }
            os << " + ";
        }
    }
    os << p[0];
    return os;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);
    result += rhs;
    return result;
}

Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);
    result -= rhs;
    return result;
}

Polynomial operator*(const Polynomial& p, int num) {
    Polynomial result(p);
    result *= num;
    return result;
}

Polynomial operator*(int num, const Polynomial& p) {
    return p * num;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    size_t degree = lhs.getDegree();
    if (degree != rhs.getDegree()) {
        return false;
    }

    for (size_t i = 0; i < degree; i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}
