#include <iostream>

int minWithCopies(const int a, const int b) {
	return (a < b) ? a : b;
}

int minWithReferences(const int& a, const int& b) {
	return (a < b) ? a : b;
}

int minWithPointers(const int* a, const int* b) {
	return (*a < *b) ? *a : *b;
}

int main() {

	int a, b;
	std::cin >> a >> b;

	std::cout << minWithCopies(a, b) << std::endl;
	std::cout << minWithReferences(a, b) << std::endl;
	std::cout << minWithPointers(&a, &b) << std::endl;

}