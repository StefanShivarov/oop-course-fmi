#include "Farm.h"
#include "AnimalFactory.h"

Farm::Farm() : animalsCount(0), animalsCapacity(16)
{
    animals = new Animal*[animalsCapacity];
}

Farm::Farm(const Farm& other)
{
    copyFrom(other);
}

Farm::Farm(Farm&& other) noexcept
{
    moveFrom(std::move(other));
}

Farm& Farm::operator=(const Farm& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Farm& Farm::operator=(Farm&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Farm::~Farm()
{
    free();
}

void Farm::addAnimal(AnimalType type)
{
    if (animalsCount == animalsCapacity) {
        resize(animalsCapacity * 2);
    }
    animals[animalsCount++] = animalFactory(type);
}

void Farm::addAnimal(const Animal& animal)
{
    if (animalsCount == animalsCapacity) {
        resize(animalsCapacity * 2);
    }
    animals[animalsCount++] = animal.clone();
}

void Farm::roarAll() const
{
    for (size_t i = 0; i < animalsCount; i++) {
        animals[i]->roar();
        std::cout << std::endl;
    }
}

AnimalType Farm::getTypeByIndex(size_t index) const
{
    if (index >= animalsCount) {
        throw std::out_of_range("Index out of range!");
    }
    return animals[index]->getType();
}

void Farm::resize(size_t newCapacity)
{
    Animal** resizedAnimals = new Animal*[newCapacity];
    for (size_t i = 0; i < animalsCount; i++) {
        resizedAnimals[i] = animals[i];
    }
    delete[] animals;
    animals = resizedAnimals;
    animalsCapacity = newCapacity;
}

void Farm::free()
{
    for (size_t i = 0; i < animalsCount; i++) {
        delete animals[i];
    }
    delete[] animals;
    animals = nullptr;
    animalsCount = animalsCapacity = 0;
}

void Farm::copyFrom(const Farm& other)
{
    animals = new Animal*[other.animalsCapacity];
    for (size_t i = 0; i < other.animalsCount; i++) {
        animals[i] = other.animals[i]->clone();
    }
    animalsCount = other.animalsCount;
    animalsCapacity = other.animalsCapacity;
}

void Farm::moveFrom(Farm&& other) noexcept
{
    animals = other.animals;
    other.animals = nullptr;

    animalsCount = other.animalsCount;
    other.animalsCount = 0;

    animalsCapacity = other.animalsCapacity;
    other.animalsCapacity = 0;
}
