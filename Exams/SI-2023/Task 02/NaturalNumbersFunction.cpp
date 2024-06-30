#include "NaturalNumbersFunction.h"

NaturalNumbersFunction::NaturalNumbersFunction() : NaturalNumbersFunction([](unsigned x) { return x; }) {}

NaturalNumbersFunction::NaturalNumbersFunction(UnaryUnsignedFunction pFunc) : pFunc(pFunc) {}

unsigned NaturalNumbersFunction::countFixedPoints(int lowerBound, int upperBound) const
{
    if (!checkBounds(lowerBound, upperBound)) {
        return 0;
    }

    unsigned counter = 0;
    for (size_t i = lowerBound; i < upperBound; i++) {
        if (this->operator()(i) == i) {
            counter++;
        }
    }

    return counter;
}

unsigned NaturalNumbersFunction::operator()(unsigned x) const
{
    return pFunc(x);
}

void NaturalNumbersFunction::setFunction(UnaryUnsignedFunction pFunc)
{
    this->pFunc = pFunc;
}

bool compareFunctionsInInterval(const NaturalNumbersFunction& lhs, const NaturalNumbersFunction& rhs, int lowerBound, int upperBound)
{
    if (!checkBounds(lowerBound, upperBound)) {
        throw std::invalid_argument("Invalid interval!");
    }

    for (int i = lowerBound; i <= upperBound; i++) {
        if (lhs(i) != rhs(i)) {
            return false;
        }
    }

    return true;
}

static bool checkBounds(int& lowerBound, int& upperBound)
{
    if (lowerBound > upperBound) {
        std::swap(lowerBound, upperBound);
    }

    if (upperBound < 0) {
        return false;
    }

    if (lowerBound < 0) {
        lowerBound = 0;
    }

    return true;
}
