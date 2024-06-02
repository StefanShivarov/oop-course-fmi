#pragma once
#include "PartialFunctionExtremum.h"

class PartialFunctionMax : public PartialFunctionExtremum
{
public:
    PartialFunctionMax(uint16_t capacity);
    int32_t operator()(int32_t x) const override;
    PartialFunction* clone() const override;
};
