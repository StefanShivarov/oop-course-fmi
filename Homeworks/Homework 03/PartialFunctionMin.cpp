#include "PartialFunctionMin.h"

const int32_t MAX_INT32_VALUE = 2147483647;

PartialFunctionMin::PartialFunctionMin(uint16_t capacity) : PartialFunctionExtremum(capacity) {}

int32_t PartialFunctionMin::operator()(int32_t x) const
{
    if (!isDefinedFor(x)) {
        throw std::out_of_range("Function is not defined for x = " + x);
    }
    int32_t minValue = MAX_INT32_VALUE;
    for (uint16_t i = 0; i < functionsCount; i++) {
        int32_t result;
        try {
            result = functions[i]->operator()(x);
        }
        catch (const std::out_of_range& e) {
            continue;
        }
        minValue = std::min(minValue, result);
    }
    return minValue;
}

PartialFunction* PartialFunctionMin::clone() const
{
    return new PartialFunctionMin(*this);
}
