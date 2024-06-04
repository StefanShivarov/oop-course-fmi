#include "Command.h"
#include <iostream>

static int myAtoi(char* str) {
    int res = 0;
    bool negative = false;
    if (str[0] == '-') {
        negative = true;
    }
    if (negative) {
        str++;
    }
    for (int i = 0; str[i] != 0; i++) {
        res = res * 10 + str[i] - '0';
    }
    return negative ? (-res) : res;
}

void RegimeOne::execute(const PartialFunction* func) const
{
    int32_t a;
    std::cout << "Enter a: ";
    std::cin >> a;

    int32_t b;
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
}

void RegimeTwo::execute(const PartialFunction* func) const
{
    char inputBuff[50];
    while (true) {
        std::cout << "Enter argument: ";
        std::cin >> inputBuff;

        if (strcmp(inputBuff, "exit") == 0) {
            return;
        }

        int argument = myAtoi(inputBuff);

        if (func->isDefinedFor(argument)) {
            std::cout << "f(" << argument << ") = " << (*func)(argument) << std::endl;
        }
        else {
            std::cout << "f(" << argument << ") is undefined!" << std::endl;
        }
    }
}

Command* CommandFactory::generateCommand()
{
    int commandNumber;
    std::cout << "Enter regime type: ";
    std::cin >> commandNumber;

    switch (commandNumber) {
        case 1: return new RegimeOne();
        case 2: return new RegimeTwo();
        default: throw std::invalid_argument("Invalid regime type! Can only be 1 or 2!");
    }
}

