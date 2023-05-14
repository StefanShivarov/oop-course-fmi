#include <iostream>
#pragma warning (disable: 4996)

const unsigned short MAX_NAME_LENGTH = 30;

struct Student {
	char name[MAX_NAME_LENGTH + 1];
	unsigned int facultyNumber;
};

void initStudent(Student& student, const char* name, unsigned int facultyNumber) {
	if (strlen(name) > MAX_NAME_LENGTH) {
		std::cout << name << " is too long for a name!" << std::endl;
		return;
	}
	strcpy(student.name, name);
	student.facultyNumber = facultyNumber;
}

void printStudent(const Student& student) {
	std::cout << "Name: " << student.name << ", Faculty number: " << student.facultyNumber << std::endl;
}

int main() {

	Student st = { "Kolio", 10 };
	Student st2 = { "Stefan", 24 };
	printStudent(st);
	Student* pSt = &st;
	printStudent(*pSt);
	const Student* pCSt = &st;
	printStudent(*pCSt);
	Student* const cPSt = &st;
	//cPSt = &st2; -> can't be done
	printStudent(*cPSt);
	const Student* const cpCSt = &st;
	//cPCSt = &st2; -> can't be done
	printStudent(*cpCSt);
	Student& refSt = st;
	printStudent(refSt);
	const Student& refCSt = st;
	printStudent(refCSt);

	initStudent(st, "new name", 123);
	printStudent(st);
	printStudent(*pSt);
	printStudent(*pCSt);
	printStudent(*cPSt);
	printStudent(*cpCSt);
	printStudent(refSt);
	printStudent(refCSt);
}