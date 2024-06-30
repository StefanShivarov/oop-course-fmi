#include "SetUnion.h"

SetUnion::SetUnion(const Set** sets, size_t count) : SetOperation(sets, count) {}

SetUnion::SetUnion(Set**&& sets, size_t count) : SetOperation(std::move(sets), count) {}

bool SetUnion::accepts(int32_t n) const
{
    for (size_t i = 0; i < setsCount; i++) {
        if (sets[i]->accepts(n)) {
            return true;
        }
    }
    return false;
}

Set* SetUnion::clone() const
{
    return new SetUnion(*this);
}
