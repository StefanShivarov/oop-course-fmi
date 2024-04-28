#include "StudentDB.h"

const size_t StudentDB::INITIAL_CAPACITY = 16;

StudentDB::StudentDB() : capacity(INITIAL_CAPACITY), studentsCount(0)
{
    students = new Student[capacity];
}

StudentDB::StudentDB(const StudentDB& other)
{
    copyFrom(other);
}

StudentDB::StudentDB(StudentDB&& other) noexcept
{
    moveFrom(std::move(other));
}

StudentDB& StudentDB::operator=(const StudentDB& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

StudentDB& StudentDB::operator=(StudentDB&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

StudentDB::~StudentDB()
{
    free();
}

size_t StudentDB::getStudentsCount() const
{
    return studentsCount;
}

void StudentDB::add(const Student& student)
{
    if (studentsCount >= capacity) {
        resize(capacity * 2);
    }

    students[studentsCount++] = student;
}

void StudentDB::add(Student&& student)
{
    if (studentsCount >= capacity) {
        resize(capacity * 2);
    }

    students[studentsCount++] = std::move(student);
}

bool StudentDB::remove(unsigned fn)
{
    size_t index = findStudentIndex(fn);
    if (index == studentsCount) {
        return false;
    }

    for (size_t i = index; i < studentsCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentsCount--;
}

const Student* StudentDB::find(unsigned fn) const
{
    for (size_t i = 0; i < studentsCount; i++) {
        if (students[i].getFn() == fn) {
            return &students[i];
        }
    }
    return nullptr;
}

void StudentDB::display() const
{
    for (size_t i = 0; i < studentsCount; i++) {
        students[i].printInfo();
        std::cout << std::endl;
    }
}

void StudentDB::resize(size_t newCapacity)
{
    Student* resizedStudents = new Student[newCapacity];
    for (size_t i = 0; i < studentsCount; i++) {
        resizedStudents[i] = students[i];
    }
    delete[] students;
    students = resizedStudents;
    capacity = newCapacity;
}

size_t StudentDB::findStudentIndex(unsigned fn) const
{
    for (size_t i = 0; i < studentsCount; i++) {
        if (students[i].getFn() == fn) {
            return i;
        }
    }
    return studentsCount; // signals that the student does not exist
}

void StudentDB::free()
{
    delete[] students;
    students = nullptr;
    studentsCount = capacity = 0;
}

void StudentDB::copyFrom(const StudentDB& other)
{
    studentsCount = other.studentsCount;
    capacity = other.capacity;
    students = new Student[capacity];
    for (size_t i = 0; i < studentsCount; i++) {
        students[i] = other.students[i];
    }
}

void StudentDB::moveFrom(StudentDB&& other) noexcept
{
    studentsCount = other.studentsCount;
    other.studentsCount = 0;

    capacity = other.capacity;
    other.capacity = 0;

    students = other.students;
    other.students = nullptr;
}
