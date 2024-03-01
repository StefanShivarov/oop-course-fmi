#include <iostream>
#include <fstream>

const int MAX_BUFF_SIZE = 1024;

int main() {
    char buff1[MAX_BUFF_SIZE];
    char buff2[MAX_BUFF_SIZE];

    std::ifstream ifs1("file1.txt");
    std::ifstream ifs2("file2.txt");

    if (!ifs1.is_open() || !ifs2.is_open()) {
        std::cerr << "There was an error with opening one of the files!";
        return -1;
    }

    unsigned currentRow = 1;
    while (!ifs1.eof() || !ifs2.eof()) {
        ifs1.getline(buff1, MAX_BUFF_SIZE);
        ifs2.getline(buff2, MAX_BUFF_SIZE);

        if (strcmp(buff1, buff2) != 0) {
            std::cout << "There is a difference at row " << currentRow;
            return 0;
        }

        currentRow++;
    }
}
