#pragma once
#include "SetOperation.h"
class SetUnion : public SetOperation
{
public:
    SetUnion(const Set** sets, size_t count);
    SetUnion(Set**&& sets, size_t count);

    bool accepts(int32_t n) const override;
    Set* clone() const override;
};
