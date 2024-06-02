#include "PartialFunctionByCriterion.h"

template<class T>
PartialFunctionByCriterion<T>::PartialFunctionByCriterion(const T& criterion) : criterionFunc(criterion) {}

template<class T>
bool PartialFunctionByCriterion<T>::isDefinedFor(int32_t x) const
{
    return criterionFunc(x).getFirst();
}

template<class T>
int32_t PartialFunctionByCriterion<T>::operator()(int32_t x) const
{
    Pair<bool, int32_t> result = criterionFunc(x);
    if (result.getFirst()) {
        return result.getSecond();
    }

    throw std::invalid_argument("Function is not defined for x!");
}

template<class T>
PartialFunction* PartialFunctionByCriterion<T>::clone() const
{
    return new PartialFunctionByCriterion<T>(*this);
}

template class PartialFunctionByCriterion<CriterionFunctionZero>;
template class PartialFunctionByCriterion<CriterionFunctionOne>;
template class PartialFunctionByCriterion<CriterionFunctionTwo>;
template class PartialFunctionByCriterion<Pair<bool, int32_t> (*)(int32_t)>;
