#include "Complex.h"

Complex::Complex(double re, double im): real(re), imaginary(im) {}

Complex Complex::getConjugated() const {
	return Complex(real, -imaginary);
}

double Complex::getReal() const { return real; }

double Complex::getImaginary() const { return imaginary; }

void Complex::setReal(double re) { real = re; }

void Complex::setImaginary(double im) { imaginary = im; }

Complex& Complex::operator+=(const Complex& other) {

	real += other.real;
	imaginary += other.imaginary;
	return *this;
}

Complex& Complex::operator-=(const Complex& other) {

	real -= other.real;
	imaginary -= other.imaginary;
	return *this;
}

Complex& Complex::operator*=(const Complex& other) {

	double realCopy = real;
	real = real * other.real - imaginary * other.imaginary;
	imaginary = realCopy * other.imaginary + imaginary * other.real;
	return *this;
}

Complex& Complex::operator/=(const Complex& other) {

	Complex conjugated = other.getConjugated();
	Complex otherCopy(other);

	*this *= conjugated;
	otherCopy *= conjugated;

	if (otherCopy.real != 0) {

		real /= otherCopy.real;
		imaginary /= otherCopy.real;
	}
	return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {

	Complex result(lhs);
	result += rhs;
	return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {

	Complex result(lhs);
	result -= rhs;
	return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {

	Complex result(lhs);
	result *= rhs;
	return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {

	Complex result(lhs);
	result /= rhs;
	return result;
}

std::ostream& operator<<(std::ostream& os, const Complex& complex) {

	return os << complex.real << ' ' << complex.imaginary << 'i';
}

std::istream& operator>>(std::istream& is, Complex& complex) {

	return is >> complex.real >> complex.imaginary;
}