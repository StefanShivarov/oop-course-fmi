#include <iostream>
#include <fstream>

size_t countSymbolsInFile(std::ifstream& ifs) {
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t symbolsCount = ifs.tellg();
    ifs.seekg(currentPos);
    ifs.clear();

    return symbolsCount;
}

size_t getFileSize(const char* fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return 0;
    }

    return countSymbolsInFile(ifs);
}

int main() {
    std::cout << getFileSize("student_data.txt");
}
