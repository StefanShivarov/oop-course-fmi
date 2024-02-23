#pragma once
#include <iostream>

enum class AnimalType { DOG, CAT, COW };

class Animal {

	AnimalType type;

public:

	Animal(AnimalType type) : type(type) {};

	virtual void makeSound() const = 0;
	virtual ~Animal() = default;
	virtual Animal* clone() const = 0;

	AnimalType getType() const { return type; }
};