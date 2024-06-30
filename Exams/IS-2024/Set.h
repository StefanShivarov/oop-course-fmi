#pragma once
#include <iostream>
#include "Criteria.h"

class Set
{
public:
    virtual bool accepts(int32_t n) const = 0;
    virtual ~Set() = default;
    virtual Set* clone() const = 0;
};

