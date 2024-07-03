#pragma once
#include "Animal.h"

class Farm
{
public:
    Farm();

    Farm(const Farm& other);
    Farm(Farm&& other) noexcept;

    Farm& operator=(const Farm& other);
    Farm& operator=(Farm&& other) noexcept;

    ~Farm();

    void addAnimal(AnimalType type);
    void addAnimal(const Animal& animal);
    
    void roarAll() const;

    AnimalType getTypeByIndex(size_t index) const;

private:
    Animal** animals;
    size_t animalsCount;
    size_t animalsCapacity;

    void resize(size_t newCapacity);
    void free();
    void copyFrom(const Farm& other);
    void moveFrom(Farm&& other) noexcept;
};
