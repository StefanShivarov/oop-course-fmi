#include "Cat.h"

Cat::Cat() : Animal(AnimalType::Cat) {}

void Cat::roar() const
{
    std::cout << "Meow, meow!";
}

Animal* Cat::clone() const
{
    return new Cat(*this);
}
