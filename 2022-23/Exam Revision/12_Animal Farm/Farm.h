#pragma once
#include "Animal.h"
#include "AnimalFactory.h"

class Farm
{

	Animal** animals;
	size_t capacity;
	size_t animalsAmount;

	void free();
	void copyFrom(const Farm& other);
	void move(Farm&& other);
	void resize();

public:

	Farm();
	Farm(const Farm& other);
	Farm& operator=(const Farm& other);
	Farm(Farm&& other) noexcept;
	Farm& operator=(Farm&& other) noexcept;
	~Farm();

	size_t getAnimalsAmount() const;
	bool addAnimal(AnimalType animalType);
	
	Animal* operator[](size_t index);
	const Animal* operator[](size_t index) const;

	void allAnimalsMakeSound() const;
};