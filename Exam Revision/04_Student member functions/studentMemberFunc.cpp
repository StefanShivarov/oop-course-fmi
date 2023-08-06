#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

namespace HelperFunctions {

    bool isSmallLetter(char c) {
        return c >= 'a' && c <= 'z';
    }

    bool isCapitalLetter(char c) {
        return c >= 'A' && c <= 'Z';
    }

    bool containsSmallLettersOnly(const char* str){
    
        size_t length = strlen(str);
        for (size_t i = 0; i < length; i++) {
            if (!isSmallLetter(str[i])) {
                return false;
            }
        }
        return true;
    }
}

class Student {

    char name[21];
    int age;
    int fn;

    bool isValidName(const char* name) const {

        if (name == nullptr) {
            return false;
        }

        if (strlen(name) > 20) {
            return false;
        }

        return HelperFunctions::isCapitalLetter(name[0]) && HelperFunctions::containsSmallLettersOnly(name + 1);
    }

    bool isValidAge(int age) const {
        
        return age >= 5 && age <= 90;
    }

public:

    Student(): age(18), fn(0) {
        
        setName("Unknown");
    }

    Student(const char* name, int age, int fn) {
        setName(name);
        setAge(age);
        setFn(fn);
    }

    const char* getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    int getFn() const {
        return fn;
    }

    void setName(const char* name) {

        if (isValidName(name)) {
            strcpy(this->name, name);
        }
    }

    void setAge(int age) {

        if (isValidAge(age)) {
            this->age = age;
        }
    }

    void setFn(int fn) {
        this->fn = fn;
    }

    void print() {
        std::cout << "Name: " << name << ", Age: " << age << ", Fn: " << fn << std::endl;
    }
};


int main()
{

    Student defConstructorStudent;
    defConstructorStudent.print();

    Student student("Stefan", 20, 2407);
    student.print();
}