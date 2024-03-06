#include <iostream>
#include <fstream>

namespace Constants {
    const int MAX_NAME_LENGTH = 16;
    const int FN_LENGTH = 5;
    const int MAX_STUDENTS_COUNT = 1024;
    const int MAX_HAIR_COLOR_LENGTH = 10;
}      

enum class HairColor {
    Brown,
    Black,
    Blond,
    Red,
    White,
    Undefined
};

HairColor getHairColorFromString(const char* str) {
    if (strcmp(str, "Brown") == 0) {
        return HairColor::Brown;
    }
    else if (strcmp(str, "Black") == 0) {
        return HairColor::Black;
    }
    else if (strcmp(str, "Blond") == 0) {
        return HairColor::Blond;
    }
    else if (strcmp(str, "Red") == 0) {
        return HairColor::Red;
    }
    else if (strcmp(str, "White") == 0) {
        return HairColor::White;
    }

    return HairColor::Undefined;     
}

const char* getHairColorString(HairColor hairColor) {
    switch (hairColor) {
        case HairColor::Brown: return "Brown";
        case HairColor::Black: return "Black";
        case HairColor::Blond: return "Blond";
        case HairColor::Red: return "Red";
        case HairColor::White: return "White";
        default: return "Undefined";
    }
}

struct Student {
    char firstName[Constants::MAX_NAME_LENGTH];
    char lastName[Constants::MAX_NAME_LENGTH];
    char fn[Constants::FN_LENGTH + 1];
    double averageGrade = 0.0;
    HairColor hairColor = HairColor::Undefined;
};

Student readStudentFromCsvFile(std::ifstream& ifs) {
    Student student;
    char hairColorStr[Constants::MAX_HAIR_COLOR_LENGTH];

    ifs.getline(student.firstName, Constants::MAX_NAME_LENGTH, ',');
    ifs.getline(student.lastName, Constants::MAX_NAME_LENGTH, ',');
    ifs.getline(student.fn, Constants::FN_LENGTH, ',');
    ifs >> student.averageGrade;
    ifs.ignore();
    ifs.getline(hairColorStr, Constants::MAX_HAIR_COLOR_LENGTH);
    student.hairColor = getHairColorFromString(hairColorStr);

    return student;
}

void writeStudentToCsvFile(std::ofstream& ofs, const Student& student) {
    ofs << student.firstName << ', '
        << student.lastName << ', '
        << student.fn << ', '
        << student.averageGrade << ', '
        << getHairColorString(student.hairColor);
}

struct StudentGroup {
    Student students[Constants::MAX_STUDENTS_COUNT];
    unsigned studentsAmount = 0;
};

StudentGroup readStudentGroupFromCsvFile(std::ifstream& ifs) {
    StudentGroup studentGroup;
    ifs >> studentGroup.studentsAmount;

    for (unsigned i = 0; i < studentGroup.studentsAmount; i++) {
        studentGroup.students[i] = readStudentFromCsvFile(ifs);
    }

    return studentGroup;
}

StudentGroup loadStudentGroupFromFile(const char* fileName) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return {};
    }

    return readStudentGroupFromCsvFile(ifs);
}

void writeStudentGroupToCsvFile(std::ofstream& ofs, const StudentGroup& studentGroup) {
    ofs << studentGroup.studentsAmount;

    for (unsigned i = 0; i < studentGroup.studentsAmount; i++) {
        writeStudentToCsvFile(ofs, studentGroup.students[i]);
        ofs << std::endl;
    }
}

void saveStudentGroupToCsvFile(const char* fileName, const StudentGroup& studentGroup) {
    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return;
    }

    writeStudentGroupToCsvFile(ofs, studentGroup);
}

int main() {
    //...
}
