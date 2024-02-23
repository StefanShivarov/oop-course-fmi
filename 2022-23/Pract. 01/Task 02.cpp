#include <iostream>

void readArr(int* arr, const int arrSize) {

	for (int i = 0; i < arrSize; i++) {
		std::cin >> arr[i];
	}
}

int countOfBiggerThanAsciiValue(const int* arr, const int arrSize, const char symbol) {
	
	int counter = 0;
	for (int i = 0; i < arrSize; i++) {
		if (symbol < arr[i]) {
			counter++;
		}
	}
	return counter;
}

int main() {

	int N;
	std::cin >> N;
	int* arr = new int[N];
	readArr(arr, N);
	char symbol;
	std::cin >> symbol;
	std::cout << countOfBiggerThanAsciiValue(arr, N, symbol);

	delete[] arr;
}