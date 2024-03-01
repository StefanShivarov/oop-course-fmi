#include <iostream>
#include <fstream>

int main()
{
    int a, b;
    std::cin >> a >> b;

    std::ofstream ofs("result1.txt");
    if (!ofs.is_open()) {
        std::cerr << "There was an error with opening the file!";
        return -1;
    }

    int sum = a + b;
    int diff = a - b;

    ofs << sum << std::endl;
    ofs << diff << std::endl;

    std::ifstream ifs("result1.txt");
    if (!ifs.is_open()) {
        std::cerr << "There was an error with opening the file!";
        return -1;
    }

    ifs >> sum >> diff;

    int firstNumber = (sum + diff) / 2;
    int secondNumber = sum - firstNumber;

    std::cout << "a: " << firstNumber << ", b: " << secondNumber;
}
