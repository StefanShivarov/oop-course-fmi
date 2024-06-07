#pragma once
#include <iostream>

class SetOfNumbers
{
public:
    virtual bool accepts(unsigned int n) const = 0;
    virtual SetOfNumbers* clone() const = 0;
    virtual ~SetOfNumbers() = default;
};
