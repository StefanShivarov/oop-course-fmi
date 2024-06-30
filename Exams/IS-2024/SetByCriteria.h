#pragma once
#include "Set.h"

template <class T>
class SetByCriteria : public Set
{
public:
    SetByCriteria(const T& crit);
    SetByCriteria(T&& crit);

    bool accepts(int32_t n) const override;
    Set* clone() const override;
private:
    T criteria;
};
