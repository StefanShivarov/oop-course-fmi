#include "Student.h"
#include <cstring>
#pragma warning (disable: 4996)

Student::Student(const char* name, int* grades, size_t gradesAmount) {

	setName(name);
	setGrades(grades, gradesAmount);
}

Student::Student(const Student& other) {
	
	copyFrom(other);
}

Student& Student::operator=(const Student& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Student::~Student() {
	free();
}

void Student::free() {

	delete[] name, grades;
	name = nullptr;
	grades = nullptr;
	gradesAmount = 0;
}

void Student::copyFrom(const Student& other) {

	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	gradesAmount = other.gradesAmount;
	grades = new int[gradesAmount];
	for (int i = 0; i < gradesAmount; i++) {
		grades[i] = other.grades[i];
	}
}

const char* Student::getName() const {
	return name;
}

const int* Student::getGrades() const {
	return grades;
}

size_t Student::getGradesAmount() const {
	return gradesAmount;
}

void Student::setName(const char* newName) {

	size_t length = strlen(newName);

	if (newName == nullptr || newName == name || length > 20) {
		return;
	}

	delete[] name;

	name = new char[length + 1];
	strcpy(name, newName);
}

void Student::setGrades(const int* newGrades, size_t newGradesAmount) {

	if (newGrades == nullptr) {
		return;
	}

	delete[] grades;
	gradesAmount = newGradesAmount;
	grades = new int[gradesAmount];
	for (int i = 0; i < gradesAmount; i++) {
		grades[i] = newGrades[i];
	}
}

void Student::setGradesAmount(size_t amount) {
	gradesAmount = amount;
}