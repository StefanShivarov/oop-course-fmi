#include "UnionOfSets.h"

UnionOfSets::UnionOfSets(SetOfNumbers** sets, size_t count) : SetOperation(sets, count) {}

bool UnionOfSets::accepts(unsigned int n) const
{
    for (size_t i = 0; i < setsCount; i++) {
        if (sets[i]->accepts(n)) {
            return true;
        }
    }
    return false;
}

SetOfNumbers* UnionOfSets::clone() const
{
    return new UnionOfSets(*this);
}
