#include "PartialFunctionDeserializer.h"
#pragma warning(disable: 4996)

int main()
{
    /*std::ofstream ofs("func.dat", std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("Could not open file!");
    }

    uint16_t N = 3, T = 3;
    ofs.write((const char*)&N, sizeof(uint16_t));
    ofs.write((const char*)&T, sizeof(uint16_t));

    char filePath[1024];
    strcpy(filePath, "first.dat");
    ofs.write((const char*)filePath, strlen(filePath) + 1);
    strcpy(filePath, "second.dat");
    ofs.write((const char*)filePath, strlen(filePath) + 1);
    strcpy(filePath, "third.dat");
    ofs.write((const char*)filePath, strlen(filePath) + 1);

    ofs.close();*/

    /*std::ofstream first("first.dat", std::ios::binary);
    if (!first.is_open()) {
        throw 7;
    }
    
    uint16_t N = 7;
    uint16_t T = 0;
    first.write((const char*)&N, sizeof(uint16_t));
    first.write((const char*)&T, sizeof(uint16_t));

    int32_t args[] = {0, 1, 2, 3, 5, 6, 7};
    int32_t res[] = {0, 3, 3, 3, 4, 4, 0};

    first.write((const char*)&args, N * sizeof(int32_t));
    first.write((const char*)&res, N * sizeof(int32_t));

    first.close();*/

    /*std::ofstream second("second.dat", std::ios::binary);
    if (!second.is_open()) {
        throw 7;
    }

    uint16_t N = 2;
    uint16_t T = 1;
    second.write((const char*)&N, sizeof(uint16_t));
    second.write((const char*)&T, sizeof(uint16_t));

    int32_t undefinedArgs[] = { 3, 5 };

    second.write((const char*)&undefinedArgs, N * sizeof(int32_t));

    second.close();*/

    /*std::ofstream third("third.dat", std::ios::binary);
    if (!third.is_open()) {
        throw 7;
    }

    uint16_t N = 4;
    uint16_t T = 2;
    third.write((const char*)&N, sizeof(uint16_t));
    third.write((const char*)&T, sizeof(uint16_t));

    int32_t args[] = { 0, 5, 6, 7 };

    third.write((const char*)&args, N * sizeof(int32_t));

    third.close();*/

    try {
        PartialFunction* func = PartialFunctionDeserializer::deserializePartialFunctionFromBinaryFile("func.dat");
        
        int32_t a, b;
        std::cout << "Enter a: ";
        std::cin >> a;
        std::cout << "Enter b: ";
        std::cin >> b;

        for (int32_t i = a; i <= b; i++) {
            if (func->isDefinedFor(i)) {
                std::cout << "f(" << i << ") = " << (*func)(i) << std::endl;
            }
            else {
                std::cout << "f(" << i << ") is undefined!" << std::endl;
            }
        }

        delete func;
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
    catch (...) {
        std::cout << "Error occured!";
    }
}
