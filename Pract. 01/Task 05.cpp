#include <iostream>

struct ComplexNumber {
	//realPart + imaginaryPart*i
	int realPart;
	int imaginaryPart;
};

ComplexNumber sumOfComplexNumbers(const ComplexNumber& first, const ComplexNumber& second) {
	return {
		first.realPart + second.realPart,
		first.imaginaryPart + second.imaginaryPart
	};
}

void printComplexNumber(const ComplexNumber& complex) {
	std::cout << complex.realPart << ((complex.imaginaryPart > 0) ? " + " : "") << complex.imaginaryPart << "i" << std::endl;
}

int main() {
	
	ComplexNumber c1{ 1, 2 };
	ComplexNumber c2{ 2, 3 };

	ComplexNumber sum = sumOfComplexNumbers(c1, c2);
	printComplexNumber(sum);
}