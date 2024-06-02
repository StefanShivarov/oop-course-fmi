#include "PartialFunctionExtremum.h"

PartialFunctionExtremum::PartialFunctionExtremum(uint16_t capacity) : PartialFunction(), functionsCapacity(capacity), functionsCount(0)
{
    functions = new PartialFunction*[capacity];
}

PartialFunctionExtremum::PartialFunctionExtremum(const PartialFunctionExtremum& other) : PartialFunction(other)
{
    copyFrom(other);
}

PartialFunctionExtremum::PartialFunctionExtremum(PartialFunctionExtremum&& other) noexcept : PartialFunction(std::move(other)) 
{
    moveFrom(std::move(other));
}

PartialFunctionExtremum& PartialFunctionExtremum::operator=(const PartialFunctionExtremum& other)
{
    if (this != &other) {
        PartialFunction::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

PartialFunctionExtremum& PartialFunctionExtremum::operator=(PartialFunctionExtremum&& other) noexcept
{
    if (this != &other) {
        PartialFunction::operator=(std::move(other));
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

PartialFunctionExtremum::~PartialFunctionExtremum()
{
    free();
}

bool PartialFunctionExtremum::isDefinedFor(int32_t x) const
{
    for (uint16_t i = 0; i < functionsCount; i++) {
        if (functions[i] && !functions[i]->isDefinedFor(x)) {
            return false;
        }
    }
    return true;
}

void PartialFunctionExtremum::addFunction(PartialFunction* func)
{
    if (functionsCount == functionsCapacity) {
        // this heterogeneous container is not meant to be resizeable, since it knows exactly how many functions it contains
        return;
    }

    // takes ownership of the function
    functions[functionsCount++] = func;
    func = nullptr;
}

void PartialFunctionExtremum::addFunction(const PartialFunction& func)
{
    PartialFunction* function = func.clone();
    addFunction(function);
}

void PartialFunctionExtremum::free()
{
    for (uint16_t i = 0; i < functionsCount; i++) {
        delete functions[i];
    }
    delete[] functions;
    functions = nullptr;
    functionsCount = 0;
}

void PartialFunctionExtremum::copyFrom(const PartialFunctionExtremum& other)
{
    functions = new PartialFunction * [other.functionsCapacity];
    for (uint16_t i = 0; i < functionsCapacity; i++) {
        functions[i] = other.functions[i]->clone();
    }
    functionsCount = other.functionsCount;
    functionsCapacity = other.functionsCapacity;
}

void PartialFunctionExtremum::moveFrom(PartialFunctionExtremum&& other) noexcept
{
    functions = other.functions;
    other.functions = nullptr;

    functionsCount = other.functionsCount;
    other.functionsCount = 0;
}
