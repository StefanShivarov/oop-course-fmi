#include "PartialFunctionMin.h"

PartialFunctionMin::PartialFunctionMin(uint16_t capacity) : PartialFunctionExtremum(capacity) {}

PartialFunctionMin::PartialFunctionMin(PartialFunction** functions, uint16_t count) 
    : PartialFunctionExtremum(functions, count) {}

int32_t PartialFunctionMin::operator()(int32_t x) const
{
    if (!isDefinedFor(x)) {
        throw std::invalid_argument("Function is not defined for x!");
    }

    int32_t minValue = functions[0]->operator()(x);
    for (uint16_t i = 1; i < functionsCount; i++) {
        int32_t result;
        try {
            result = functions[i]->operator()(x);
        }
        catch (const std::invalid_argument& e) {
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
