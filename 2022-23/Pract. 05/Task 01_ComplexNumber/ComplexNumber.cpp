#include "ComplexNumber.h"
#include <iostream>

void ComplexNumber::setRealPart(int real) {

	realPart = real;
}

void ComplexNumber::setImaginaryPart(int imaginary) {

	imaginaryPart = imaginary;
}

int ComplexNumber::getRealPart() const {
	return realPart;
}

int ComplexNumber::getImaginaryPart() const {
	return imaginaryPart;
}

ComplexNumber::ComplexNumber(int real, int imaginary) : realPart(real), imaginaryPart(imaginary) {}

bool ComplexNumber::isEqualTo(const ComplexNumber& other) const {

	return realPart == other.realPart && imaginaryPart == other.imaginaryPart;
}

ComplexNumber ComplexNumber::add(const ComplexNumber& other) const {

	return ComplexNumber(realPart + other.realPart, imaginaryPart + other.imaginaryPart);
}

ComplexNumber ComplexNumber::subtract(const ComplexNumber& other) const {

	return ComplexNumber(realPart - other.realPart, imaginaryPart - other.imaginaryPart);
}

ComplexNumber ComplexNumber::multiply(const ComplexNumber& other) const {

	return ComplexNumber(realPart * other.realPart - imaginaryPart * other.imaginaryPart,
		realPart * other.imaginaryPart + imaginaryPart * other.realPart);
}

void ComplexNumber::conjugate() {
	imaginaryPart = -imaginaryPart;
}

ComplexNumber ComplexNumber::getConjugated() const {
	return ComplexNumber(realPart, -imaginaryPart);
}

void ComplexNumber::print() const {

	if (imaginaryPart > 0) {
		std::cout << realPart << " + " << imaginaryPart << "i" << std::endl;
	}
	else if (imaginaryPart == 0) {
		std::cout << realPart << std::endl;
	}
	else {
		std::cout << realPart << " " << imaginaryPart << "i" << std::endl;
	}

}