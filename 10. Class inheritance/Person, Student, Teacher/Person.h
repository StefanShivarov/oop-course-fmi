#pragma once
class Person
{
public:
    Person() = default;
    Person(const char* name, int age);

    Person(const Person& other);
    Person(Person&& other) noexcept;

    Person& operator=(const Person& other);
    Person& operator=(Person&& other) noexcept;

    ~Person();

    const char* getName() const;
    int getAge() const;

    void print() const;

protected:
    void setName(const char* name);
    void setAge(int age);

private:
    char* name = nullptr;
    int age = 0;

    void free();
    void copyFrom(const Person& other);
    void moveFrom(Person&& other) noexcept;
};
