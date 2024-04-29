#pragma once
#include "Person.h"

class Teacher : public Person
{
public:
    Teacher() = default;
    Teacher(const char* name, int age, char** subjects, size_t subjectsCount);

    Teacher(const Teacher& other);
    Teacher(Teacher&& other) noexcept;

    Teacher& operator=(const Teacher& other);
    Teacher& operator=(Teacher&& other) noexcept;

    ~Teacher();

    const char* const* getSubjects() const;
    size_t getSubjectsCount() const;

private:
    char** subjects = nullptr;
    size_t subjectsCount = 0;

    void free();
    void copyFrom(const Teacher& other);
    void moveFrom(Teacher&& other) noexcept;
};
