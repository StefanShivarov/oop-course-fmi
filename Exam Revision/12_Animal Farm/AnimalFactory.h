#pragma once
#include "Animal.h"

class AnimalFactory
{

	static AnimalFactory factory;

	AnimalFactory() = default;

public:

	AnimalFactory(const AnimalFactory& other) = delete;
	AnimalFactory& operator=(const AnimalFactory& other) = delete;

	virtual Animal* createAnimal(AnimalType animalType) const;

	static AnimalFactory& getInstance();
};