#include <iostream>
#include <assert.h>

enum class Year {
	First,
	Second,
	Third,
	Fourth,
	Unknown
};

struct Student {
	unsigned fn;
	Year year;
	double averageGrade;
};

Year getYearFromNumber(int number) {
	switch (number) {
	case 1: return Year::First;
	case 2: return Year::Second;
	case 3: return Year::Third;
	case 4: return Year::Fourth;
	default: return Year::Unknown;
	}
}

const char* getYearString(const Year& year) {
	switch (year) {
	case Year::First: return "First";
	case Year::Second: return "Second";
	case Year::Third: return "Third";
	case Year::Fourth: return "Fourth";
	case Year::Unknown: return "Unknown";
	}
}

bool isValidFn(unsigned fn) {
	return fn > 9999 && fn < 100000;
}

Student initStudent(unsigned fn, int year, double averageGrade) {
	assert(isValidFn(fn));
	return { fn, getYearFromNumber(year), averageGrade };
}

void printStudent(const Student& student) {
	std::cout << "Fn: " << student.fn 
		<< ", Year: " << getYearString(student.year)
		<< ", Average grade: " << student.averageGrade 
		<< std::endl;
}

int main() {
	Student student = initStudent(12345, 2, 4.50);
	printStudent(student); //Fn: 12345, Year: Second, Average grade: 4.50
}
