#include "Exam.h"
#include <iostream>

void Exam::changeMin(int newMin) {

	if (newMin < 0 || newMin > getMax()) {
		std::cout << "Invalid min points!" << std::endl;
	}
}

Exam::Exam(int minPoints): minPointsToPass(minPoints), tasksAmount(0) {}

int Exam::getMax() const {
	
	int max = 0;
	for (int i = 0; i < tasksAmount; i++) {
		max += tasks[i].getPoints();
	}

	return max;
}

void Exam::readFromBinaryFile(const char* filePath) {

	std::ifstream ifs(filePath, std::ios::binary);

	if (!ifs.is_open()) {
		std::cout << "Error! Can't read from file." << std::endl;
		return;
	}

	ifs.seekg(0, std::ios::end);
	size_t fileSize = ifs.tellg();
	this->tasksAmount = fileSize / sizeof(Task);

	ifs.read((char*) &this->tasks, fileSize);

	ifs.close();
}

void Exam::writeToBinaryFile(const char* filePath) const {

	std::ofstream ofs(filePath, std::ios::binary);

	if (!ofs.is_open()) {
		std::cout << "Error! Can't write to file." << std::endl;
		return;
	}

	for (int i = 0; i < tasksAmount; i++) {
		tasks[i].writeToBinaryFile(ofs);
	}

	ofs.close();
}