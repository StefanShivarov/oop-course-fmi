#pragma once
#include <iostream>

using UnaryUnsignedFunction = unsigned(*)(unsigned);

class NaturalNumbersFunction
{
public:
    NaturalNumbersFunction();
    NaturalNumbersFunction(UnaryUnsignedFunction pFunc);
    
    unsigned countFixedPoints(int lowerBound, int upperBound) const;

    virtual unsigned operator()(unsigned x) const;
    virtual void setFunction(UnaryUnsignedFunction pFunc);

    virtual ~NaturalNumbersFunction() = default;

protected:
    UnaryUnsignedFunction pFunc;
};

bool compareFunctionsInInterval(const NaturalNumbersFunction& lhs, const NaturalNumbersFunction& rhs,
    int lowerBound, int upperBound);
