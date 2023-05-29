#include <iostream>

//insertion sort
template <typename T>
void sort(T* arr, size_t arrSize) {
	
	for (size_t i = 1; i < arrSize; i++) {

		T current = arr[i];
		size_t compareIndex = i - 1;

		while (current < arr[compareIndex] && compareIndex >= 0) {
			arr[compareIndex + 1] = arr[compareIndex];
			--compareIndex;
		}
		arr[compareIndex + 1] = current;
	}
}

//counting sort
template <>
void sort(char* arr, size_t arrSize) {

	char maxElement = arr[0];

	for (size_t i = 0; i < arrSize; i++) {
		if (arr[i] > maxElement) {
			maxElement = arr[i];
		}
	}

	size_t countSize = maxElement + 1;
	size_t* countArr = new size_t[countSize + 1]();

	for (size_t i = 0; i < arrSize; i++) {
		++countArr[arr[i]];
	}

	for (size_t i = 1; i < countSize; i++) {
		countArr[i] += countArr[i - 1];
	}

	char* tempArr = new char[arrSize];

	for (size_t i = 0; i < arrSize; i++) {
		tempArr[countArr[arr[i]] - 1] = arr[i];
		--countArr[arr[i]];
	}

	for (size_t i = 0; i < arrSize; i++) {
		arr[i] = tempArr[i];
	}

	delete[] countArr;
	delete[] tempArr;
}

template <typename T>
void printArr(T* arr, size_t arrSize) {

	for (size_t i = 0; i < arrSize; i++) {
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;
}