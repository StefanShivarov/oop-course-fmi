#include "Cat.h"

Cat::Cat() : Animal(AnimalType::CAT) {}

void Cat::makeSound() const {

	std::cout << "Meow, meow!" << std::endl;
}

Animal* Cat::clone() const {

	Animal* cloned = new Cat(*this);
	return cloned;
}