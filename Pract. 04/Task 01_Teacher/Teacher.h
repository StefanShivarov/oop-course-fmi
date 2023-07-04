#pragma once

const short MAX_NAME_LENGTH = 50;

class Teacher
{

	char name[MAX_NAME_LENGTH + 1];
	unsigned age;
	unsigned yearsExperience;

public:

	Teacher(const char* name, unsigned age, unsigned yearsExperience);

	const char* getName() const;
	void setName(const char* name);

	unsigned getAge() const;
	void setAge(unsigned age);

	unsigned getYearsExperience() const;
	void setYearsExperience(unsigned years);

};