#include "AnimalFactory.h"
#include "Dog.h"
#include "Cat.h"
#include "Cow.h"

AnimalFactory AnimalFactory::factory;

AnimalFactory& AnimalFactory::getInstance() {
	return factory;
}

Animal* AnimalFactory::createAnimal(AnimalType type) const {

	switch (type) {

	case AnimalType::DOG: return new Dog();
	case AnimalType::CAT: return new Cat();
	case AnimalType::COW: return new Cow();
	default: return nullptr;

	}

}