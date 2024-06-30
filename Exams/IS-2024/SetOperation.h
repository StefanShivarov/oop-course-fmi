#pragma once
#include "Set.h"
class SetOperation : public Set
{
public:
    SetOperation(const Set** sets, size_t count);
    SetOperation(Set**&& sets, size_t count);

    SetOperation(const SetOperation& other);
    SetOperation(SetOperation&& other) noexcept;

    SetOperation& operator=(const SetOperation& other);
    SetOperation& operator=(SetOperation&& other) noexcept;

    ~SetOperation();
protected:
    Set** sets;
    size_t setsCount;
private:
    void copyFrom(const SetOperation& other);
    void moveFrom(SetOperation&& other) noexcept;
    void free();
};
