#include "PartialFunctionMax.h"

const int32_t MIN_INT32_VALUE = -2147483648;

PartialFunctionMax::PartialFunctionMax(uint16_t capacity) : PartialFunctionExtremum(capacity) {}

int32_t PartialFunctionMax::operator()(int32_t x) const
{
    if (!isDefinedFor(x)) {
        throw std::invalid_argument("Function is not defined for x!");
    }

    int32_t maxValue = MIN_INT32_VALUE;
    for (uint16_t i = 0; i < functionsCount; i++) {
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
