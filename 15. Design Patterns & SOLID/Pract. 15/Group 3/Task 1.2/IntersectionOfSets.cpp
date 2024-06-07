#include "IntersectionOfSets.h"

IntersectionOfSets::IntersectionOfSets(SetOfNumbers** sets, size_t count) : SetOperation(sets, count) {}

bool IntersectionOfSets::accepts(unsigned int n) const
{
    for (size_t i = 0; i < setsCount; i++) {
        if (!sets[i]->accepts(n)) {
            return false;
        }
    }
    return true;
}

SetOfNumbers* IntersectionOfSets::clone() const
{
    return new IntersectionOfSets(*this);
}
