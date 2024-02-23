#include "Cow.h"

Cow::Cow() : Animal(AnimalType::COW) {}

void Cow::makeSound() const {

	std::cout << "Mooooo!" << std::endl;
}

Animal* Cow::clone() const {

	Animal* cloned = new Cow(*this);
	return cloned;
}