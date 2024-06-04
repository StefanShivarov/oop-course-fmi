#include "PartialFunctionMax.h"

PartialFunctionMax::PartialFunctionMax(uint16_t capacity) : PartialFunctionExtremum(capacity) {}

PartialFunctionMax::PartialFunctionMax(PartialFunction** functions, uint16_t count) 
    : PartialFunctionExtremum(functions, count) {}

int32_t PartialFunctionMax::operator()(int32_t x) const
{
    if (!isDefinedFor(x)) {
        throw std::invalid_argument("Function is not defined for x!");
    }

    int32_t maxValue = functions[0]->operator()(x);
    for (uint16_t i = 1; i < functionsCount; i++) {
        int32_t result;
        try {
            result = functions[i]->operator()(x);
        }
        catch (const std::invalid_argument& e) {
            continue;
        }
        maxValue = std::max(maxValue, result);
    }
    return maxValue;
}

PartialFunction* PartialFunctionMax::clone() const
{
    return new PartialFunctionMax(*this);
}
