#include "SetByCriteria.h"

template<class T>
SetByCriteria<T>::SetByCriteria(const T& crit) : criteria(crit) {}

template<class T>
SetByCriteria<T>::SetByCriteria(T&& crit) : criteria(std::move(crit)) {}

template<class T>
bool SetByCriteria<T>::accepts(int32_t n) const
{
    return criteria(n);
}

template<class T>
Set* SetByCriteria<T>::clone() const
{
    return new SetByCriteria<T>(*this);
}

template class SetByCriteria<IncludeCriteria>;
template class SetByCriteria<ExcludeCriteria>;
template class SetByCriteria<bool (*)(int32_t)>;
