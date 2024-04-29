#include "Person.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

Person::Person(const char* name, int age)
{
    setName(name);
    setAge(age);
}

Person::Person(const Person& other)
{
    copyFrom(other);
}

Person::Person(Person&& other) noexcept
{
    moveFrom(std::move(other));
}

Person& Person::operator=(const Person& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Person& Person::operator=(Person&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Person::~Person()
{
    free();
}

const char* Person::getName() const
{
    return name;
}

int Person::getAge() const
{
    return age;
}

void Person::print() const
{
    std::cout << name << ', ' << age;
}

void Person::setName(const char* name)
{
    if (!name || this->name == name) {
        return;
    }

    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Person::setAge(int age)
{
    this->age = age;
}

void Person::free()
{
    delete[] name;
    name = nullptr;
    age = 0;
}

void Person::copyFrom(const Person& other)
{
    age = other.age;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

void Person::moveFrom(Person&& other) noexcept
{
    name = other.name;
    other.name = nullptr;

    age = other.age;
    other.age = 0;
}
