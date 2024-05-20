#include "Cow.h"

Cow::Cow() : Animal(AnimalType::Cow) {}

void Cow::roar() const
{
    std::cout << "Moo, moo!";
}

Animal* Cow::clone() const
{
    return new Cow(*this);
}
