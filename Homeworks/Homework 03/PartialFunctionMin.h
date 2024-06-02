#pragma once
#include "PartialFunctionExtremum.h"

class PartialFunctionMin : public PartialFunctionExtremum
{
public:
    PartialFunctionMin(uint16_t capacity);
    int32_t operator()(int32_t x) const override;
    PartialFunction* clone() const override;
};
