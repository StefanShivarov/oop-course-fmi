#include "Task.h"
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

void Task::setTitle(const char* newTitle) {

	size_t length = strlen(newTitle);
	if (!newTitle || length > MAX_TITLE_LENGTH || length == 0) {
		std::cout << "Invalid title!" << std::endl;
		return;
	}

	strcpy(title, newTitle);
}

void Task::setDescription(const char* desc) {

	size_t length = strlen(desc);
	if (!desc || length > MAX_DESCRIPTION_LENGTH || length == 0) {
		std::cout << "Invalid description!" << std::endl;
		return;
	}

	strcpy(description, desc);
}

void Task::setPoints(int newPoints) {
	if (newPoints <= 0) {
		std::cout << "Invalid points!" << std::endl;
		return;
	}

	points = newPoints;
}

Task::Task(const char* title, const char* desc, int points) {

	setTitle(title);
	setDescription(desc);
	setPoints(points);
}

void Task::writeToBinaryFile(std::ofstream& ofs) const {

	if (!ofs.is_open()) {
		std::cout << "Error! Can't write to file." << std::endl;
		return;
	}

	ofs.write((const char*)this, sizeof(Task));
}

void Task::readFromBinaryFile(std::ifstream& ifs) {

	if (!ifs.is_open()) {
		std::cout << "Error! Can't read from file." << std::endl;
		return;
	}

	ifs.read((char*)this, sizeof(Task));
}

const char* Task::getTitle() const {
	return title;
}

const char* Task::getDescription() const {
	return description;
}

int Task::getPoints() const {
	return points;
}