#pragma once
#include "Student.h"

class StudentDB
{
public:
    StudentDB();
    
    StudentDB(const StudentDB& other);
    StudentDB(StudentDB&& other) noexcept;

    StudentDB& operator=(const StudentDB& other);
    StudentDB& operator=(StudentDB&& other) noexcept;

    ~StudentDB();

    size_t getStudentsCount() const;

    void add(const Student& student);
    void add(Student&& student);
    bool remove(unsigned fn);

    const Student* find(unsigned fn) const;

    void display() const;

protected:
    Student* students;
    size_t studentsCount;
    size_t capacity;

    void resize(size_t newCapacity);
private:
    static const size_t INITIAL_CAPACITY;

    size_t findStudentIndex(unsigned fn) const;

    void free();
    void copyFrom(const StudentDB& other);
    void moveFrom(StudentDB&& other) noexcept;
};
