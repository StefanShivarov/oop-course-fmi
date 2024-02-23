#pragma once

class Person {

	char* name = nullptr;
	int age = 0;

	void free();
	void copyFrom(const Person& other);
	void move(Person&& other);

public:

	Person() = default;
	Person(const char* name, int age);
	Person(const Person& other);
	Person& operator=(const Person& other);
	Person(Person&& other) noexcept;
	Person& operator=(Person&& other) noexcept;
	~Person();

	const char* getName() const;
	int getAge() const;

	void setName(const char* name);
	void setAge(int age);

	void print() const;
};