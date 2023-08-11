#include "Student.h"

void Student::setFn(size_t fn) {
	this->fn = fn;
}

size_t Student::getFn() const {
	return fn;
}

Student::Student(const char* name, int age, size_t fn) : Person(name, age), fn(fn) {}