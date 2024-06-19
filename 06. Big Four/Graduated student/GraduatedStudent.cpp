#include "GraduatedStudent.h"
#include <cstring>
#pragma warning(disable: 4996)

GraduatedStudent::GraduatedStudent(const char* name, const int* grades, size_t gradesCount, const char* quote) : gradesCount(gradesCount)
{
    setName(name);
    setGrades(grades);
    setQuote(quote);
}

GraduatedStudent::GraduatedStudent(const GraduatedStudent& other)
{
    copyFrom(other);
}

GraduatedStudent& GraduatedStudent::operator=(const GraduatedStudent& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

GraduatedStudent::~GraduatedStudent()
{
    free();
}

const char* GraduatedStudent::getName() const
{
    return name;
}

const int* GraduatedStudent::getGrades() const
{
    return grades;
}

size_t GraduatedStudent::getGradesCount() const
{
    return gradesCount;
}

const char* GraduatedStudent::getQuote() const
{
    return quote;
}

void GraduatedStudent::setName(const char* str)
{
    if (!str || str == name) {
        return;
    }
    delete[] name;
    name = new char[strlen(str) + 1];
    strcpy(name, str);
}

void GraduatedStudent::setGrades(const int* newGrades, size_t count)
{
    if (!newGrades || newGrades == grades) {
        return;
    }
    delete[] grades;
    grades = new int[count];
    gradesCount = count;
    for (size_t i = 0; i < count; i++) {
        grades[i] = newGrades[i];
    }
}

void GraduatedStudent::setQuote(const char* str)
{
    if (!str || strlen(str) > 30) {
        return;
    }
    strcpy(quote, str);
}

void GraduatedStudent::free()
{
    delete[] name;
    delete[] grades;
    name = nullptr;
    grades = nullptr;
    gradesCount = 0;
    strcpy(quote, "");
}

void GraduatedStudent::copyFrom(const GraduatedStudent& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    grades = new int[other.gradesCount];
    for (size_t i = 0; i < other.gradesCount; i++) {
        grades[i] = other.grades[i];
    }

    gradesCount = other.gradesCount;
    strcpy(quote, other.quote);
}
