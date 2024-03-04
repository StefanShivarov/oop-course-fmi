#include <iostream>
#include <fstream>

namespace Constants {
    const int MAX_MAJOR_NAME_LENGTH = 10;
    const int MAX_FN_LENGTH = 11;
    const int MAX_FULL_NAME_LENGTH = 31;
    const int MAX_STUDENTS_COUNT = 100;
}

enum class Major {
    IS,
    SI,
    KN,
    IN,
    Undefined
};

const char* getMajorString(Major major) {
    switch (major) {
        case Major::IS: return "IS";
        case Major::SI: return "SI";
        case Major::KN: return "KN";
        case Major::IN: return "IN";
        default: return "Undefined";
    }
}

Major getMajorFromString(const char* str) {
    if (strcmp(str, "IS") == 0) {
        return Major::IS;
    }
    else if (strcmp(str, "SI") == 0) {
        return Major::SI;
    }
    else if (strcmp(str, "KN") == 0) {
        return Major::KN;
    }
    else if (strcmp(str, "IN") == 0) {
        return Major::IN;
    }

    return Major::Undefined;
}

struct Student {
    char fn[Constants::MAX_FN_LENGTH];
    char fullName[Constants::MAX_FULL_NAME_LENGTH];
    Major major = Major::Undefined;
    double averageGrade = 0.0;
};

void printStudent(const Student& student) {
    std::cout << student.fn << ' '
        << student.fullName << ' '
        << getMajorString(student.major) << ' '
        << student.averageGrade;
}

struct StudentDatabase {
    Student students[Constants::MAX_STUDENTS_COUNT];
    size_t studentsAmount = 0;
};

void addStudentToDatabase(StudentDatabase& studentDatabase, const Student& student) {
    studentDatabase.students[studentDatabase.studentsAmount++] = student;
}

void sortStudentsByGrade(Student students[Constants::MAX_STUDENTS_COUNT], size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        size_t maxGradeIndex = i;
        for (size_t j = i + 1; j < size; j++) {
            if (students[j].averageGrade > students[maxGradeIndex].averageGrade) {
                maxGradeIndex = j;
            }
        }

        if (maxGradeIndex != i) {
            std::swap(students[i], students[maxGradeIndex]);
        }
    }
}

void printHighestGradeFromMajor(Student students[Constants::MAX_STUDENTS_COUNT], size_t size, Major major) {
    sortStudentsByGrade(students, size);

    for (size_t i = 0; i < size; i++) {
        if (students[i].major == major) {
            printStudent(students[i]);
            return;
        }
    }
}

double getAverageFromMajor(Student students[Constants::MAX_STUDENTS_COUNT], size_t size, Major major) {
    double gradeSum = 0.0;
    size_t majorCount = 0;

    for (size_t i = 0; i < size; i++) {
        if (students[i].major == major) {
            gradeSum += students[i].averageGrade;
            majorCount++;
        }
    }

    return gradeSum / majorCount;
}

Student readStudent(std::istream& is) {
    Student student;
    is.getline(student.fn, Constants::MAX_FN_LENGTH, ';');

    is.getline(student.fullName, Constants::MAX_FULL_NAME_LENGTH, ';');

    char majorStr[Constants::MAX_MAJOR_NAME_LENGTH];
    is.getline(majorStr, Constants::MAX_MAJOR_NAME_LENGTH, ';');
    student.major = getMajorFromString(majorStr);

    is >> student.averageGrade;

    is.ignore();
    return student;
}

void readStudentsFromFile(const char* fileName, StudentDatabase& studentDatabase) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return;
    }

    while (!ifs.eof()) {
        addStudentToDatabase(studentDatabase, readStudent(ifs));
    }

    ifs.close();
}

int main() {
    StudentDatabase studentDatabase;
    readStudentsFromFile("student_data.txt", studentDatabase);

    sortStudentsByGrade(studentDatabase.students, studentDatabase.studentsAmount);

    for (unsigned i = 0; i < studentDatabase.studentsAmount; i++) {
        printStudent(studentDatabase.students[i]);
        std::cout << std::endl;
    }

    printHighestGradeFromMajor(studentDatabase.students, studentDatabase.studentsAmount, Major::SI);
    std::cout << std::endl;
    printHighestGradeFromMajor(studentDatabase.students, studentDatabase.studentsAmount, Major::KN);
    std::cout << std::endl;

    std::cout << getAverageFromMajor(studentDatabase.students, studentDatabase.studentsAmount, Major::SI);
}
