#include <iostream>

struct ComplexNumber {
	int real = 0;
	int imaginary = 0;
};

ComplexNumber sumComplexNumbers(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	return { lhs.real + rhs.real, lhs.imaginary + rhs.imaginary };
}

ComplexNumber multiplyComplexNumbers(const ComplexNumber& lhs, const ComplexNumber& rhs) {
	return {
		lhs.real * rhs.real - lhs.imaginary * rhs.imaginary,
		lhs.real * rhs.imaginary + lhs.imaginary * rhs.real
	};
}

void printComplex(const ComplexNumber& complex) {
	std::cout << complex.real
		<< (complex.imaginary < 0 ? "" : " +")
		<< " " << complex.imaginary << "i"
		<< std::endl;
}

/*
int main() {
	ComplexNumber c1{ 0, 4 };
	ComplexNumber c2{ -6, 1 };

	printComplex(sumComplexNumbers(c1, c2));
	std::cout << std::endl;
	printComplex(multiplyComplexNumbers(c1, c2));

	return 0;
}
*/

