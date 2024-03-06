#include <iostream>
#include <fstream>

const int MAX_BUFF_SIZE = 1024;

void concatenateFiles(const char* sourceFileNames[], unsigned sourceFilesAmount, const char* destFileName) {
    std::ofstream ofs(destFileName);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << destFileName << '!';
        return;
    }

    for (unsigned i = 0; i < sourceFilesAmount; i++) {
        std::ifstream ifs(sourceFileNames[i]);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open file " << sourceFileNames[i] << '!';
            return;
        }

        char buff[MAX_BUFF_SIZE];
        while (!ifs.eof()) {
            ifs.getline(buff, MAX_BUFF_SIZE);
            ofs << buff << std::endl;
        }

        ifs.close();
    }
    ofs.close();
}

int main() {
    const char* sourceFiles[] = { "first.txt", "second.txt", "third.txt" };
    concatenateFiles(sourceFiles, 3, "concatenation.txt");
}
