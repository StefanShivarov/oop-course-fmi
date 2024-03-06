#include <iostream>
#include <fstream>

const int MAX_NUMBERS_AMOUNT = 64;

void selectionSortNumbers(int* numbers, unsigned size) {
    unsigned minIndex;

    for (unsigned i = 0; i < size - 1; i++) {
        minIndex = i;

        for (unsigned j = i + 1; j < size; j++) {
            if (numbers[j] < numbers[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(numbers[i], numbers[minIndex]);
        }
    }
}

int mostFrequentNumberInArr(int* numbers, unsigned size) {
    unsigned maxOccurences = 1, currentOccurences = 1;
    int mostFrequent = numbers[0];

    for (unsigned i = 1; i < size; i++) {
        if (numbers[i] == numbers[i - 1]) {
            currentOccurences++;
        }
        else {
            if (currentOccurences > maxOccurences) {
                maxOccurences = currentOccurences;
                mostFrequent = numbers[i - 1];
            }

            currentOccurences = 1;
        }
    }

    if (currentOccurences > maxOccurences) {
        maxOccurences = currentOccurences;
        mostFrequent = numbers[size - 1];
    }

    return mostFrequent;
}

int main() {
    int numbers[MAX_NUMBERS_AMOUNT]{};

    std::ifstream ifs("numbers.txt");
    if (!ifs.is_open()) {
        std::cerr << "There was an error with opening the file!";
        return -1;
    }

    unsigned numbersAmount;
    ifs >> numbersAmount;

    for (unsigned i = 0; i < numbersAmount; i++) {
        ifs >> numbers[i];
    }

    selectionSortNumbers(numbers, numbersAmount);
    std::cout << "Most frequent: " << mostFrequentNumberInArr(numbers, numbersAmount);
}
