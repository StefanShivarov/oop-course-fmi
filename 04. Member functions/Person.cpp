#include <iostream>
#include <cstring>
#pragma warning(disable: 4996)

namespace HelperFunctions
{
    bool isSmallLetter(char ch) {
        return ch >= 'a' && ch <= 'z';
    }

    bool isCapitalLetter(char ch) {
        return ch >= 'A' && ch <= 'Z';
    }

    bool containsOnlySmallLetters(const char* str) {
        size_t length = strlen(str);

        for (size_t i = 0; i < length; i++) {
            if (!isSmallLetter(str[i])) {
                return false;
            }
        }
        return true;
    }
}

constexpr int MAX_NAME_LENGTH = 20;
constexpr int MIN_NAME_LENGTH = 2;
constexpr int MAX_AGE = 90;
constexpr int MIN_AGE = 5;

class Person 
{
public:
    Person() = default;

    Person(const char* name, int age)
    {
        setName(name);
        setAge(age);
    }

    const char* getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    void setName(const char* name)
    {
        if (isValidName(name)) {
            strcpy(this->name, name);
        }
        else {
            strcpy(this->name, "Unknown");
        }
    }

    void setAge(int age)
    {
        if (isValidAge(age)) {
            this->age = age;
        }
        else {
            this->age = MIN_AGE;
        }
    }

private:
    char name[MAX_NAME_LENGTH + 1] = "Unknown";
    int age = MIN_AGE;

    bool isValidName(const char* name) const
    {
        if (name == nullptr) {
            return false;
        }

        size_t nameLength = strlen(name);
        if (nameLength < MIN_NAME_LENGTH || nameLength > MAX_NAME_LENGTH) {
            return false;
        }

        return HelperFunctions::isCapitalLetter(*name) && HelperFunctions::containsOnlySmallLetters(name + 1);
    }

    bool isValidAge(int age) const
    {
        return age >= MIN_AGE && age <= MAX_AGE;
    }
};