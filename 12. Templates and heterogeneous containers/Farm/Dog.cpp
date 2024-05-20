#include "Dog.h"

Dog::Dog() : Animal(AnimalType::Dog) {}

void Dog::roar() const
{
    std::cout << "Woof, woof!";
}

Animal* Dog::clone() const
{
    return new Dog(*this);
}
