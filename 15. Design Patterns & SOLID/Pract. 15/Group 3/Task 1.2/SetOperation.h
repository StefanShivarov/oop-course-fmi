#pragma once
#include "SetOfNumbers.h"

class SetOperation : public SetOfNumbers
{
public:
    SetOperation(SetOfNumbers** sets, size_t count);

    SetOperation(const SetOperation& other);
    SetOperation(SetOperation&& other) noexcept;

    SetOperation& operator=(const SetOperation& other);
    SetOperation& operator=(SetOperation&& other) noexcept;

    ~SetOperation();
protected:
    SetOfNumbers** sets = nullptr;
    size_t setsCount = 0;
private:
    void free();
    void copyFrom(const SetOperation& other);
    void moveFrom(SetOperation&& other) noexcept;
};

