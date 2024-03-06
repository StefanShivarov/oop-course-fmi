#include <iostream>
#include <fstream>

size_t getSymbolCountFromFile(std::ifstream& ifs, char symbol) {
    size_t counter = 0;

    while (true) {
        char currentSymbol = ifs.get();

        if (ifs.eof()) {
            break;
        }

        if (currentSymbol == symbol) {
            counter++;
        }
    }

    return counter;
}

size_t getNewLinesCount(const char* fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return 0;
    }

    return getSymbolCountFromFile(ifs, '\n') + 1;
}

int main() {
    std::cout << getNewLinesCount("lines.txt");
}
