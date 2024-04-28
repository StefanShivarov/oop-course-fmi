#pragma once
#include "MyString.h"

class Student
{
public:
    Student();
    Student(const MyString& name, unsigned fn, unsigned year);

    const MyString& getName() const;
    unsigned getFn() const;
    unsigned getYear() const;

    void setName(const MyString& name);
    void setFn(unsigned fn);
    void setYear(unsigned year);

    void printInfo() const;
private:
    MyString name;
    unsigned fn = 0;
    unsigned year = 0;
};
