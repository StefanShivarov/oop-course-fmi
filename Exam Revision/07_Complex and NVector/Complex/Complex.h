#pragma once
#include <iostream>

class Complex {

	double real = 0;
	double imaginary = 0;

public:

	Complex() = default;
	Complex(double re, double im);
	
	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	Complex getConjugated() const;

	double getReal() const;
	double getImaginary() const;

	void setReal(double re);
	void setImaginary(double im);

	friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
	friend std::istream& operator>>(std::istream& is, Complex& complex);
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);