#pragma once
#include "NaturalNumbersFunction.h"

class ModifiableNaturalNumbersFunction : public NaturalNumbersFunction
{
public:
    ModifiableNaturalNumbersFunction();
    ModifiableNaturalNumbersFunction(UnaryUnsignedFunction pFunc, unsigned pointsToChange);

    ModifiableNaturalNumbersFunction(const ModifiableNaturalNumbersFunction& other);
    ModifiableNaturalNumbersFunction(ModifiableNaturalNumbersFunction&& other) noexcept;

    ModifiableNaturalNumbersFunction& operator=(const ModifiableNaturalNumbersFunction& other);
    ModifiableNaturalNumbersFunction& operator=(ModifiableNaturalNumbersFunction&& other) noexcept;

    ~ModifiableNaturalNumbersFunction();

    bool modify(unsigned point, unsigned value);
    bool removeModification(unsigned point);

    unsigned operator()(unsigned x) const override final;
    void setFunction(UnaryUnsignedFunction pFunc) final;

private:
    struct PointValuePair
    {
        int point = -1;
        int value = -1;
    };

    PointValuePair* modifiedPoints = nullptr;
    size_t pointsCount = 0;
    size_t capacity = 0;

    void copyFrom(const ModifiableNaturalNumbersFunction& other);
    void moveFrom(ModifiableNaturalNumbersFunction&& other) noexcept;
    void free();

    unsigned findPointIndex(unsigned point) const;
    void removeAllModifications();
};

