#pragma once
#include "SetOperation.h"

class UnionOfSets : public SetOperation
{
public:
    UnionOfSets(SetOfNumbers** sets, size_t count);

    bool accepts(unsigned int n) const override;

    SetOfNumbers* clone() const override;
};

