#include "SetIntersection.h"

SetIntersection::SetIntersection(const Set** sets, size_t count) : SetOperation(sets, count) {}

SetIntersection::SetIntersection(Set**&& sets, size_t count) : SetOperation(std::move(sets), count) {}

bool SetIntersection::accepts(int32_t n) const
{
    for (size_t i = 0; i < setsCount; i++) {
        if (!sets[i]->accepts(n)) {
            return false;
        }
    }
    return true;
}

Set* SetIntersection::clone() const
{
    return new SetIntersection(*this);
}
