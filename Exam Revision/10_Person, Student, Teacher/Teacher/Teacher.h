#pragma once
#include "../Person/Person.h"

class Teacher : public Person {

	char** subjects = nullptr;
	size_t subjectsAmount = 0;

	void free();
	void copyFrom(const Teacher& other);
	void move(Teacher&& other);

public:

	Teacher() = default;
	Teacher(const char* name, int age, const char* const * subjects, size_t subjectsAmount);
	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	Teacher(Teacher&& other) noexcept;
	Teacher& operator=(Teacher&& other) noexcept;
	~Teacher();

	//get, set...
};