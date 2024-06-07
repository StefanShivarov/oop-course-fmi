#pragma once
#include "SetOperation.h"

class IntersectionOfSets : public SetOperation
{
public:
    IntersectionOfSets(SetOfNumbers** sets, size_t count);

    bool accepts(unsigned int n) const override;

    SetOfNumbers* clone() const override;
};
