#pragma once
#include "SetOfNumbers.h"

template <class T>
class SetByCriteria : public SetOfNumbers
{
public:
    explicit SetByCriteria(const T& criteria);
    explicit SetByCriteria(T&& criteria);

    bool accepts(unsigned int n) const override;

    SetOfNumbers* clone() const override;
private:
    T criteriaFunc;
};
