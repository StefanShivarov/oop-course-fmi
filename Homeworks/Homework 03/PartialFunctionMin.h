#pragma once
#include "PartialFunctionExtremum.h"

class PartialFunctionMin : public PartialFunctionExtremum
{
public:
    explicit PartialFunctionMin(uint16_t capacity);
    PartialFunctionMin(PartialFunction** functions, uint16_t count);
    int32_t operator()(int32_t x) const override;
    PartialFunction* clone() const override;
};
