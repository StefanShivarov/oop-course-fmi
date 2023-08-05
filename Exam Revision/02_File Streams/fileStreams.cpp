#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& ifs) {

    size_t currentPosition = ifs.tellg(); // get the current position, so that we can restore it in the end
    ifs.seekg(0, std::ios::end); // put the get pointer at the end of the file
    size_t fileSize = ifs.tellg(); // the end of the file position should be equal to the file size in bytes
    ifs.seekg(currentPosition); // restore the position of the get pointer
    return fileSize;
}

size_t countOfCharacterFromFile(std::ifstream& ifs, char c) {

    size_t currentPosition = ifs.tellg(); // get the current position, so that we can restore it in the end
    ifs.seekg(0, std::ios::beg); // put the pointer at the beginning of the file
    
    if (!ifs.is_open()) {
        std::cout << "Error!" << std::endl;
        return 0;
    }

    size_t count = 0;

    while (true) {

        char currentSymbol = ifs.get(); // get the next symbol from the file

        if (ifs.eof()) {
            break; // break when the end of the file is reached
        }

        if (currentSymbol == c) {
            count++;
        }
    }

    ifs.seekg(currentPosition); // put the get pointer back to where it was
    return count;
}

size_t getLinesCountOfFile(std::ifstream& ifs) {

    return countOfCharacterFromFile(ifs, '\n') + 1;
}

int main()
{
    
    std::ifstream ifs("test.txt");

    std::cout << getFileSize(ifs) << std::endl;

    std::cout << getLinesCountOfFile(ifs) << std::endl;
   
    ifs.close();
}