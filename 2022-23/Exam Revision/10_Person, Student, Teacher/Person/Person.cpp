#include "Person.h"
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

void Person::free() {

	delete[] name;
	name = nullptr;
	age = 0;
}

void Person::copyFrom(const Person& other) {

	age = other.age;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
}

void Person::move(Person&& other) {

	age = other.age;
	name = other.name;
	other.name = nullptr;
}

Person::Person(const char* name, int age) {

	setAge(age);
	setName(name);
}

Person::Person(const Person& other) {
	copyFrom(other);
}

Person& Person::operator=(const Person& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Person::Person(Person&& other) noexcept {
	move(std::move(other));
}

Person& Person::operator=(Person&& other) noexcept {

	if (this != &other) {
		free();
		move(std::move(other));
	}
	return *this;
}

Person::~Person() {
	free();
}

void Person::setAge(int age) {

	if (age < 0 || age > 120) {
		throw std::logic_error("Error! Invalid age!");
	}

	this->age = age;
}

void Person::setName(const char* name) {

	if (name == nullptr || this->name == name) {
		return;
	}

	delete[] this->name;
	size_t nameLength = strlen(name);
	if (nameLength > 30 || nameLength < 2) {
		throw std::length_error("Error! Invalid length for name!");
	}

	this->name = new char[nameLength + 1];
	strcpy(this->name, name);
}

const char* Person::getName() const {
	return name;
}

int Person::getAge() const {
	return age;
}

void Person::print() const {

	std::cout << "Name: " << name << ", Age: " << age;
}