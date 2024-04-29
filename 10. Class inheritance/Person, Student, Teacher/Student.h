#pragma once
#include "Person.h"

class Student : public Person
{
public:
    Student() = default;
    Student(const char* name, int age, size_t fn);

    size_t getFn() const;
    void setFn(size_t fn);

private:
    size_t fn = 0;
};

