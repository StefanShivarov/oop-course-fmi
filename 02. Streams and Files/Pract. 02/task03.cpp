#include <iostream>
#include <fstream>

const int BUFFER_CAPACITY = 1024;

int main() {
    std::ifstream ifs("task03.cpp");
    if (!ifs.is_open()) {
        std::cerr << "There was an error with reading from the file!";
        return -1;
    }

    char buff[BUFFER_CAPACITY];
    while (!ifs.eof()) {
        ifs.getline(buff, BUFFER_CAPACITY);
        std::cout << buff << std::endl;
    }
}
