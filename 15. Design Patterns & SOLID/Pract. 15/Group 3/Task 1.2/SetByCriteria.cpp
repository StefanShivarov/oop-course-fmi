#include "SetByCriteria.h"

template<class T>
SetByCriteria<T>::SetByCriteria(const T& criteria) : criteriaFunc(criteria) {}

template<class T>
SetByCriteria<T>::SetByCriteria(T&& criteria) : criteriaFunc(std::move(criteria)) {}

template<class T>
bool SetByCriteria<T>::accepts(unsigned int n) const
{
    return criteriaFunc(n);
}

template<class T>
SetOfNumbers* SetByCriteria<T>::clone() const
{
    return new SetByCriteria<T>(*this);
}

template class SetByCriteria<bool (*)(unsigned int)>;
