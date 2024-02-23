#include "Farm.h"

const size_t INITIAL_FARM_CAPACITY = 10;

void Farm::free() {

	for (size_t i = 0; i < animalsAmount; i++) {

		delete animals[i];
	}
	delete[] animals;
}

void Farm::copyFrom(const Farm& other) {

	capacity = other.capacity;
	animalsAmount = other.animalsAmount;

	animals = new Animal * [other.capacity];
	for (size_t i = 0; i < other.animalsAmount; i++) {
		animals[i] = other.animals[i]->clone();
	}
}

void Farm::move(Farm&& other) {

	capacity = other.capacity;
	animalsAmount = other.animalsAmount;
	animals = other.animals;
	other.animals = nullptr;
	other.capacity = other.animalsAmount = 0;
}

void Farm::resize() {

	Animal** resizedAnimals = new Animal * [capacity *= 2];

	for (size_t i = 0; i < animalsAmount; i++) {
		resizedAnimals[i] = animals[i];
	}

	delete[] animals;
	animals = resizedAnimals;
}

Farm::Farm() : capacity(INITIAL_FARM_CAPACITY), animalsAmount(0) {

	animals = new Animal * [capacity];
}

Farm::Farm(const Farm& other) {

	copyFrom(other);
}

Farm& Farm::operator=(const Farm& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Farm::Farm(Farm&& other) {

	move(std::move(other));
}

Farm& Farm::operator=(Farm&& other) {

	if (this != &other) {
		free();
		move(std::move(other));
	}
	return *this;
}

Farm::~Farm() {
	free();
}

size_t Farm::getAnimalsAmount() const {
	return animalsAmount;
}

void Farm::allAnimalsMakeSound() const {

	for (size_t i = 0; i < animalsAmount; i++) {
		animals[i]->makeSound();
	}
}

Animal* Farm::operator[](size_t index) {

	if (index >= animalsAmount) {
		throw std::logic_error("Error! Invalid index!");
	}

	return animals[index];
}

const Animal* Farm::operator[](size_t index) const {

	if (index >= animalsAmount) {
		throw std::logic_error("Error! Invalid index!");
	}

	return animals[index];
}

bool Farm::addAnimal(AnimalType animalType) {

	Animal* createdAnimal = AnimalFactory::getInstance().createAnimal(animalType);

	if (createdAnimal != nullptr) {

		if (animalsAmount == capacity) {

			resize();
		}
		animals[animalsAmount++] = createdAnimal;
	}

	return createdAnimal;
}