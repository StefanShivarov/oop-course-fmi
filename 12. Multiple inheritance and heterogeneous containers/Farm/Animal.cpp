#include "Animal.h"

Animal::Animal(AnimalType type) : animalType(type) {}

AnimalType Animal::getType() const
{
    return animalType;
}
