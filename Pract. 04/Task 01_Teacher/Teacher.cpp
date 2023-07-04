#include "Teacher.h"
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

const short MIN_AGE = 18;
const short MAX_AGE = 100;
const short MAX_EXPERIENCE = 70;

Teacher::Teacher(const char* name, unsigned age, unsigned years) {

	setName(name);
	setAge(age);
	setYearsExperience(years);
}

const char* Teacher::getName() const {
	return name;
}

void Teacher::setName(const char* name) {

	if (!name || strlen(name) > MAX_NAME_LENGTH) {
		std::cout << "Invalid name" << std::endl;
		return;
	}

	strcpy(this->name, name);
}

unsigned Teacher::getAge() const {
	return age;
}

void Teacher::setAge(unsigned age) {

	if (age < MIN_AGE || age > MAX_AGE) {
		std::cout << "Invalid age" << std::endl;
		return;
	}

	this->age = age;
}

unsigned Teacher::getYearsExperience() const {
	return yearsExperience;
}

void Teacher::setYearsExperience(unsigned years) {

	if (years > MAX_EXPERIENCE) {
		std::cout << "Invalid years of experience!" << std::endl;
		return;
	}

	this->yearsExperience = years;
}