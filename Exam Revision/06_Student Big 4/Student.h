#pragma once
class Student
{

	char* name = nullptr;
	int* grades = nullptr;
	size_t gradesAmount = 0;

	void copyFrom(const Student& other);
	void free();

public:

	Student() = default;
	Student(const char* name, int* grades, size_t gradesAmount);
	Student(const Student& other);
	Student& operator=(const Student& other);
	~Student();

	const char* getName() const;
	const int* getGrades() const;
	size_t getGradesAmount() const;

	void setName(const char* name);
	void setGrades(const int* grades, size_t gradesAmount);
	void setGradesAmount(size_t amount);
};