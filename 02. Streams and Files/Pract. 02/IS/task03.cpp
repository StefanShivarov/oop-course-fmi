#include <iostream>
#include <fstream>

const int MAX_BUFF_SIZE = 1024;

void reverseLine(char* reversed, const char* original) {
    unsigned length = strlen(original);
    for (unsigned i = 0; i < length; i++) {
        reversed[i] = original[length - i - 1];
    }
    reversed[length] = '\0';
}

void reverseLinesFromFile(const char* sourceFileName, const char* destFileName) {
    std::ifstream ifs(sourceFileName);
    std::ofstream ofs(destFileName);
    if (!ifs.is_open() || !ofs.is_open()) {
        std::cerr << "Failed to open file!";
        return;
    }

    char buff[MAX_BUFF_SIZE];
    while (!ifs.eof()) {
        ifs.getline(buff, MAX_BUFF_SIZE);
        char reversedLine[MAX_BUFF_SIZE];
        reverseLine(reversedLine, buff);
        ofs << reversedLine << std::endl;
    }

    ifs.close();
    ofs.close();
}

int main() {
    reverseLinesFromFile("original.txt", "reversed.txt");
}
