#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

size_t getFileSize(std::ifstream& ifs)
{
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(currentPos);
    return size;
}

struct Student {

    char name[30];
    int age;
    int fn;
};

struct DynamicNameStudent {

    char* name;
    int age;
    int fn;
};

Student initStudent(const char* name, int age, int fn) {

    Student student;
    strcpy(student.name, name);
    student.age = age;
    student.fn = fn;
    return student;
}

DynamicNameStudent initDynamicMemStudent(const char* name, int age, int fn) {

    DynamicNameStudent student;
    student.name = new char[strlen(name) + 1];
    strcpy(student.name, name);
    student.age = age;
    student.fn = fn;
    return student;
}

void writeStudentsToBinaryFile(Student* studentsArr, size_t count, std::ofstream& ofs) {

    if (!ofs.is_open()) {
        std::cout << "Error!" << std::endl;
        return;
    }

    ofs.write((const char*)&studentsArr, count * sizeof(Student));
}

void saveDynamicNameStudentToFile(const DynamicNameStudent& student, std::ofstream& ofs) {

    if (!ofs.is_open()) {
        std::cout << "Error!" << std::endl;
        return;
    }

    size_t nameLength = strlen(student.name);
    ofs.write((const char*) &nameLength, sizeof(nameLength));
    ofs.write(student.name, nameLength + 1);
    ofs.write((const char*) &student.age, sizeof(student.age));
    ofs.write((const char*) &student.fn, sizeof(student.fn));
}

void writeDynamicNameStudentsToBinaryFile(DynamicNameStudent* students, size_t count, std::ofstream& ofs) {

    if (!ofs.is_open()) {
        std::cout << "Error!" << std::endl;
        return;
    }

    ofs.write((const char*) &count, sizeof(count));

    for (size_t i = 0; i < count; i++) {
        saveDynamicNameStudentToFile(students[i], ofs);
    }
}

void readStudentsFromFile(Student*& students, std::ifstream& ifs) {

    if (!ifs.is_open()) {
        std::cout << "Error!" << std::endl;
        return;
    }

    size_t fileSize = getFileSize(ifs);
    size_t studentsCount = fileSize / sizeof(Student);
    students = new Student[studentsCount];
    ifs.read((char*)students, fileSize);
}

DynamicNameStudent readDynamicNameStudent(std::ifstream& ifs) {

    DynamicNameStudent student;

    size_t nameLength;
    ifs.read((char*)&nameLength, sizeof(nameLength));

    student.name = new char[nameLength + 1];
    ifs.read(student.name, nameLength + 1);

    ifs.read((char*)&student.age, sizeof(student.age));
    ifs.read((char*)&student.fn, sizeof(student.fn));
    return student;
}

void readDynamicNameStudentsFromFile(DynamicNameStudent*& students, size_t& count, std::ifstream& ifs) {

    ifs.read((char*)&count, sizeof(count));
    students = new DynamicNameStudent[count];
    for (size_t i = 0; i < count; i++) {
        students[i] = readDynamicNameStudent(ifs);
    }
}

int main()
{
    //...
}