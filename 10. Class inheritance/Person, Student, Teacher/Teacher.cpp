#include "Teacher.h"
#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

static char** copyArrayOfStrings(const char* const* strings, size_t size)
{
    char** result = new char* [size];
    for (size_t i = 0; i < size; i++) {
        result[i] = new char[strlen(strings[i]) + 1];
        strcpy(result[i], strings[i]);
    }
    return result;
}

static void freeArrayOfStrings(char** strings, size_t count) 
{
    for (size_t i = 0; i < count; i++) {
        delete[] strings[i];
    }
    delete[] strings;
}

Teacher::Teacher(const char* name, int age, char** subjects, size_t count) : Person(name, age)
{
    this->subjects = copyArrayOfStrings(subjects, count);
    subjectsCount = count;
}

Teacher::Teacher(const Teacher& other) : Person(other)
{
    copyFrom(other);
}

Teacher::Teacher(Teacher&& other) noexcept : Person(std::move(other))
{
    moveFrom(std::move(other));
}

Teacher& Teacher::operator=(const Teacher& other)
{
    if (this != &other) {
        Person::operator=(other);
        free();
        copyFrom(other);
    }
    return *this;
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
    if (this != &other) {
        Person::operator=(std::move(other));
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Teacher::~Teacher()
{
    free();
}

const char* const* Teacher::getSubjects() const
{
    return subjects;
}

size_t Teacher::getSubjectsCount() const
{
    return subjectsCount;
}

void Teacher::free()
{
    freeArrayOfStrings(subjects, subjectsCount);
    subjects = nullptr;
    subjectsCount = 0;
}

void Teacher::copyFrom(const Teacher& other)
{
    subjects = copyArrayOfStrings(other.subjects, other.subjectsCount);
    subjectsCount = other.subjectsCount;
}

void Teacher::moveFrom(Teacher&& other) noexcept
{
    subjects = other.subjects;
    other.subjects = nullptr;

    subjectsCount = other.subjectsCount;
    other.subjectsCount = 0;
}
