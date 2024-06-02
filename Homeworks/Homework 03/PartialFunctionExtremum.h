#pragma once
#include "PartialFunction.h"

class PartialFunctionExtremum : public PartialFunction
{
public:
    PartialFunctionExtremum(uint16_t capacity);

    PartialFunctionExtremum(const PartialFunctionExtremum& other);
    PartialFunctionExtremum(PartialFunctionExtremum&& other) noexcept;

    PartialFunctionExtremum& operator=(const PartialFunctionExtremum& other);
    PartialFunctionExtremum& operator=(PartialFunctionExtremum&& other) noexcept;

    ~PartialFunctionExtremum();

    bool isDefinedFor(int32_t x) const override;

    void addFunction(PartialFunction* func);
    void addFunction(const PartialFunction& func);
protected:
    PartialFunction** functions;
    uint16_t functionsCount;
    uint16_t functionsCapacity;
private:
    void free();
    void copyFrom(const PartialFunctionExtremum& other);
    void moveFrom(PartialFunctionExtremum&& other) noexcept;
};
