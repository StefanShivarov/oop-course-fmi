#pragma once
#include <iostream>

enum class AnimalType
{
    Dog,
    Cat,
    Cow
};

class Animal
{
public:
    Animal(AnimalType type);

    virtual ~Animal() = default;

    AnimalType getType() const;
    virtual void roar() const = 0;
    virtual Animal* clone() const = 0;

private:
    AnimalType animalType;
};

