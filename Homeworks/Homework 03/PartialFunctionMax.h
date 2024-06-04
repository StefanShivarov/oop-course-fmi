#pragma once
#include "PartialFunctionExtremum.h"

class PartialFunctionMax : public PartialFunctionExtremum
{
public:
    explicit PartialFunctionMax(uint16_t capacity);
    PartialFunctionMax(PartialFunction** functions, uint16_t count);
    int32_t operator()(int32_t x) const override;
    PartialFunction* clone() const override;
};
