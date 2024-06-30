#pragma once
#include "SetOperation.h"
class SetIntersection : public SetOperation
{
public:
    SetIntersection(const Set** sets, size_t count);
    SetIntersection(Set**&& sets, size_t count);

    bool accepts(int32_t n) const override;
    Set* clone() const override;
};
