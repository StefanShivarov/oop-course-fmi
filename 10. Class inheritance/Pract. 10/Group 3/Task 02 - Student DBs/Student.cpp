#include "Student.h"

Student::Student() : Student("Unknown", 0, 0) {}

Student::Student(const MyString& name, unsigned fn, unsigned year) : fn(fn), year(year)
{
    setName(name);
}

const MyString& Student::getName() const
{
    return name;
}

unsigned Student::getFn() const
{
    return fn;
}

unsigned Student::getYear() const
{
    return year;
}

void Student::setName(const MyString& name)
{
    if (name.length() == 0) {
        throw std::invalid_argument("Name can't be empty!");
    }
    this->name = name;
}

void Student::setFn(unsigned fn)
{
    this->fn = fn;
}

void Student::setYear(unsigned year)
{
    this->year = year;
}

void Student::printInfo() const {
    std::cout << name << ', ' << fn << ', ' << year;
}
