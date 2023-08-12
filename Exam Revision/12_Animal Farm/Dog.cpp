#include "Dog.h"

Dog::Dog() : Animal(AnimalType::DOG) {}

void Dog::makeSound() const {

	std::cout << "Woof, woof!" << std::endl;
}

Animal* Dog::clone() const {

	Animal* cloned = new Dog(*this);
	return cloned;
}