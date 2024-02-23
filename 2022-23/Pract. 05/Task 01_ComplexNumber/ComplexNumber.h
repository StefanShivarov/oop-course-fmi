#pragma once
class ComplexNumber
{
	int realPart = 0;
	int imaginaryPart = 0;

public:

	ComplexNumber() = default;
	ComplexNumber(int real, int imaginary);

	int getRealPart() const;
	void setRealPart(int real);
	int getImaginaryPart() const;
	void setImaginaryPart(int imaginary);

	bool isEqualTo(const ComplexNumber& other) const;
	ComplexNumber add(const ComplexNumber& other) const;
	ComplexNumber subtract(const ComplexNumber& other) const;
	ComplexNumber multiply(const ComplexNumber& other) const;
	void conjugate();
	ComplexNumber getConjugated() const;
	void print() const;
};