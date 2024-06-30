#include "ModifiableNaturalNumbersFunction.h"

namespace {
    constexpr int INVALID_INDEX = -1;
}

ModifiableNaturalNumbersFunction::ModifiableNaturalNumbersFunction()
    : ModifiableNaturalNumbersFunction([](unsigned x) { return x; }, 2) {}

ModifiableNaturalNumbersFunction::ModifiableNaturalNumbersFunction(UnaryUnsignedFunction pFunc, unsigned pointsToChange)
    : NaturalNumbersFunction(pFunc), capacity(pointsToChange)
{
    modifiedPoints = new PointValuePair[pointsToChange];
}

ModifiableNaturalNumbersFunction::ModifiableNaturalNumbersFunction(const ModifiableNaturalNumbersFunction& other)
{
    copyFrom(other);
}

ModifiableNaturalNumbersFunction::ModifiableNaturalNumbersFunction(ModifiableNaturalNumbersFunction&& other) noexcept
{
    moveFrom(std::move(other));
}

ModifiableNaturalNumbersFunction& ModifiableNaturalNumbersFunction::operator=(const ModifiableNaturalNumbersFunction& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ModifiableNaturalNumbersFunction& ModifiableNaturalNumbersFunction::operator=(ModifiableNaturalNumbersFunction&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

ModifiableNaturalNumbersFunction::~ModifiableNaturalNumbersFunction()
{
    free();
}

bool ModifiableNaturalNumbersFunction::modify(unsigned point, unsigned value)
{
    int index = findPointIndex(point);
    if (index == INVALID_INDEX) {
        if (pointsCount >= capacity) {
            return false;
        }
        index = pointsCount++;
    }

    modifiedPoints[index].point = point;
    modifiedPoints[index].value = value;
}

bool ModifiableNaturalNumbersFunction::removeModification(unsigned point)
{
    int index = findPointIndex(point);
    if (index == INVALID_INDEX) {
        return false;
    }

    modifiedPoints[index] = PointValuePair();
    if (index != --pointsCount) {
        std::swap(modifiedPoints[index], modifiedPoints[pointsCount]);
    }

    return true;
}

unsigned ModifiableNaturalNumbersFunction::operator()(unsigned x) const
{
    int index = findPointIndex(x);
    return index == INVALID_INDEX ? pFunc(x) : modifiedPoints[index].value;
}

void ModifiableNaturalNumbersFunction::setFunction(UnaryUnsignedFunction pFunc)
{
    removeAllModifications();
    this->pFunc = pFunc;
}

void ModifiableNaturalNumbersFunction::copyFrom(const ModifiableNaturalNumbersFunction& other)
{
    modifiedPoints = new PointValuePair[other.capacity];
    for (size_t i = 0; i < other.pointsCount; i++) {
        modifiedPoints[i] = other.modifiedPoints[i];
    }
    pointsCount = other.pointsCount;
    capacity = other.capacity;
}

void ModifiableNaturalNumbersFunction::moveFrom(ModifiableNaturalNumbersFunction&& other)
{
    modifiedPoints = other.modifiedPoints;
    other.modifiedPoints = nullptr;
    pointsCount = other.pointsCount;
    capacity = other.capacity;
    other.capacity = other.pointsCount = 0;
}

void ModifiableNaturalNumbersFunction::free()
{
    delete[] modifiedPoints;
    modifiedPoints = nullptr;
    capacity = pointsCount = 0;
}

unsigned ModifiableNaturalNumbersFunction::findPointIndex(unsigned point) const
{
    for (size_t i = 0; i < pointsCount; i++) {
        if (modifiedPoints[i].point == point) {
            return i;
        }
    }
    return INVALID_INDEX;
}

void ModifiableNaturalNumbersFunction::removeAllModifications()
{
    pointsCount = 0;
}
