#include "CriterionFunction.h"
#include <iostream>

CriterionFunction::CriterionFunction(const int32_t* args, uint16_t count) : argsCount(count)
{
    if (count > MAX_ARGS_COUNT) {
        throw std::invalid_argument("Count of arguments can't be higher than 32!");
    }

    for (uint16_t i = 0; i < count; i++) {
        this->args[i] = args[i];
    }
}

int CriterionFunction::findArgumentIndex(int32_t x) const
{
    for (uint16_t i = 0; i < argsCount; i++) {
        if (args[i] == x) {
            return i;
        }
    }
    return -1;
}

CriterionFunctionZero::CriterionFunctionZero(const int32_t* args, const int32_t* results, uint16_t count)
    : CriterionFunction(args, count)
{
    for (uint16_t i = 0; i < count; i++) {
        this->results[i] = results[i];
    }
}

Pair<bool, int32_t> CriterionFunctionZero::operator()(int32_t x) const
{
    int argIndex = findArgumentIndex(x);
    if (argIndex != -1) {
        return Pair<bool, int32_t>(true, results[argIndex]);
    }
    return Pair<bool, int32_t>(false, 0);
}

CriterionFunction* CriterionFunctionZero::clone() const
{
    return new CriterionFunctionZero(*this);
}

CriterionFunctionOne::CriterionFunctionOne(const int32_t* args, uint16_t count) : CriterionFunction(args, count) {}

Pair<bool, int32_t> CriterionFunctionOne::operator()(int32_t x) const
{
    int argIndex = findArgumentIndex(x);
    if (argIndex != -1) {
        return Pair<bool, int32_t>(false, 0);
    }
    return Pair<bool, int32_t>(true, x);
}

CriterionFunction* CriterionFunctionOne::clone() const
{
    return new CriterionFunctionOne(*this);
}

CriterionFunctionTwo::CriterionFunctionTwo(const int32_t* args, uint16_t count) : CriterionFunction(args, count) {}

Pair<bool, int32_t> CriterionFunctionTwo::operator()(int32_t x) const
{
    int argIndex = findArgumentIndex(x);
    if (argIndex != -1) {
        return Pair<bool, int32_t>(true, 1);
    }
    return Pair<bool, int32_t>(true, 0);
}

CriterionFunction* CriterionFunctionTwo::clone() const
{
    return new CriterionFunctionTwo(*this);
}
