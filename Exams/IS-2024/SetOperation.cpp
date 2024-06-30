#include "SetOperation.h"

SetOperation::SetOperation(const Set** sets, size_t count) : setsCount(count)
{
    this->sets = new Set * [count];
    for (size_t i = 0; i < count; i++) {
        this->sets[i] = sets[i]->clone();
    }
}

SetOperation::SetOperation(Set**&& sets, size_t count) : setsCount(count), sets(sets) {}

SetOperation::SetOperation(const SetOperation& other)
{
    copyFrom(other);
}

SetOperation::SetOperation(SetOperation&& other) noexcept
{
    moveFrom(std::move(other));
}

SetOperation& SetOperation::operator=(const SetOperation& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

SetOperation& SetOperation::operator=(SetOperation&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

SetOperation::~SetOperation()
{
    free();
}

void SetOperation::copyFrom(const SetOperation& other)
{
    sets = new Set * [other.setsCount];
    for (size_t i = 0; i < other.setsCount; i++) {
        sets[i] = other.sets[i]->clone();
    }
    setsCount = other.setsCount;
}

void SetOperation::moveFrom(SetOperation&& other) noexcept
{
    sets = other.sets;
    other.sets = nullptr;
    setsCount = other.setsCount;
    other.setsCount = 0;
}

void SetOperation::free()
{
    for (size_t i = 0; i < setsCount; i++) {
        delete sets[i];
    }
    delete[] sets;
    sets = nullptr;
    setsCount = 0;
}
