#include <iostream>
#pragma warning (disable: 4996)

const unsigned short MAX_NAME_LENGTH = 30;
const unsigned short MAX_STUDENTS_PER_GROUP = 25;

struct Student {

	char name[MAX_NAME_LENGTH + 1];
	unsigned int fn;
	double grade;
};

struct Group {

	Student students[MAX_STUDENTS_PER_GROUP];
	int studentsAmount;
	double averageGrade;
};

double findSum(const Student* arr, int numberOfStudents) {
	double sum = 0;
	for (int i = 0; i < numberOfStudents; i++) {
		sum += arr[i].grade;
	}

	return sum;
}

void initGroupOfStudents(Group& group) {
	for (int i = 0; i < group.studentsAmount; i++) {
		std::cin >> group.students[i].fn;
		std::cin >> group.students[i].name;
		std::cin.ignore();
		std::cin >> group.students[i].grade;
	}

	group.averageGrade = findSum(group.students, group.studentsAmount) / group.studentsAmount;
}

int numberOfStudentsTakingScholarship(const Group& group, const double minGrade) {
	int studentCounter = 0;

	for (int i = 0; i < group.studentsAmount; i++) {
		if (group.students[i].grade >= minGrade) {
			studentCounter++;
		}
	}

	return studentCounter;
}

void mySwap(Student& a, Student& b) {
	Student temp = a;
	a = b;
	b = temp;
}

void sortStudentsByGrade(Student* students, const int size) {
	for (int i = 0; i < size - 1; i++) {
		size_t minIndex = i;

		for (int j = i + 1; j < size; j++) {
			if (students[j].grade < students[minIndex].grade) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			mySwap(students[minIndex], students[i]);
		}
	}

}

void printStudent(const Student& student) {
	std::cout << "Faculty number: " << student.fn << ", Name: " << student.name <<
		", Grade: " << student.grade << std::endl;
}

void studentsTakingScholarship(Group& group, const double minGrade) {
	int numberOfStudents = numberOfStudentsTakingScholarship(group, minGrade);
	sortStudentsByGrade(group.students, group.studentsAmount);

	for (int i = group.studentsAmount - 1; i >= group.studentsAmount - numberOfStudents; i--) {
		printStudent(group.students[i]);
	}
}

int main() {
	//...
}