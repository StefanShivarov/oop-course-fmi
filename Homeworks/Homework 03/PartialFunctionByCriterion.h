#pragma once
#include "PartialFunction.h"
#include "CriterionFunction.h"

template <class T> 
class PartialFunctionByCriterion : public PartialFunction
{
public:
    explicit PartialFunctionByCriterion(const T& criterion);

    bool isDefinedFor(int32_t x) const override;
    int32_t operator()(int32_t x) const override;
    PartialFunction* clone() const override;
private:
    T criterionFunc;
};
