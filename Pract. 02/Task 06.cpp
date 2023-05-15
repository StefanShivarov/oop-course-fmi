#include <iostream>
#include <fstream>

const int BUFFER_LENGTH = 1024;

void printSourceCode(const char* fileName) {

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return;
	}

	while (!ifs.eof()) {
		char buffer[BUFFER_LENGTH];
		ifs.getline(buffer, BUFFER_LENGTH);
		std::cout << buffer << std::endl;
	}
	ifs.close();
}

int main() {

	printSourceCode("Task 06.cpp");
}