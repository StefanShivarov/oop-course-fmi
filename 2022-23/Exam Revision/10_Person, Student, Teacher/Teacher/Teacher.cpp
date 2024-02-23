#include "Teacher.h"
#include <iostream>
#pragma warning (disable: 4996)

void Teacher::free() {

	for (size_t i = 0; i < subjectsAmount; i++) {
		delete[] subjects[i];
	}
	delete[] subjects;
}

void Teacher::copyFrom(const Teacher& other) {

	subjectsAmount = other.subjectsAmount;
	subjects = new char* [subjectsAmount];
	for (size_t i = 0; i < subjectsAmount; i++) {
		subjects[i] = new char[strlen(other.subjects[i]) + 1];
		strcpy(subjects[i], other.subjects[i]);
	}
}

void Teacher::move(Teacher&& other) {

	subjectsAmount = other.subjectsAmount;
	subjects = other.subjects;
	other.subjects = nullptr;
	other.subjectsAmount = 0;
}

Teacher::Teacher(const char* name, int age, const char* const* subjects, size_t subjectsAmount) : Person(name, age), subjectsAmount(subjectsAmount) {

	this->subjects = new char* [subjectsAmount];
	for (size_t i = 0; i < subjectsAmount; i++) {
		this->subjects[i] = new char[strlen(subjects[i]) + 1];
		strcpy(this->subjects[i], subjects[i]);
	}
}

Teacher::Teacher(const Teacher& other) : Person(other) {
	copyFrom(other);
}

Teacher& Teacher::operator=(const Teacher& other) {

	if (this != &other) {
		Person::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

Teacher::Teacher(Teacher&& other) : Person(std::move(other)) {
	copyFrom(other);
}

Teacher& Teacher::operator=(Teacher&& other) {

	if (this != &other) {
		Person::operator=(std::move(other));
		free();
		move(std::move(other));
	}
	return *this;
}

Teacher::~Teacher() {
	free();
}