#include <iostream>
#include <fstream>

const int MAX_BUFF_SIZE = 1024;

int main() {
    std::ifstream ifs("source.txt");
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file!";
        return -1;
    }

    std::ofstream ofs("dest.txt");
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file!";
        return -1;
    }

    char buff[MAX_BUFF_SIZE];
    while (!ifs.eof()) {
        ifs.getline(buff, MAX_BUFF_SIZE);
        ofs << buff << std::endl;
    }

    ifs.close();
    ofs.close();
}
