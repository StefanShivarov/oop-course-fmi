#include "Secret.h"
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

Secret::Secret(const char* task, const char* password): loginFails(0) {

	if (task && password) {
		strcpy(this->task, task);
		strcpy(this->password, password);
	}
}

const char* Secret::getTask(const char* password) const {

	if (strcmp(this->password, password) != 0) {
		std::cout << "Incorrect password!" << std::endl;
		loginFails++;
		return "";
	}

	return task;
}

void Secret::setPassword(const char* newPass, const char* oldPass) {

	if (strcmp(password, oldPass) != 0) {
		std::cout << "Incorrect password!" << std::endl;
		loginFails++;
		return;
	}

	strcpy(password, newPass);
}

void Secret::setTask(const char* newTask, const char* pass) {

	if (strcmp(password, pass) != 0) {
		std::cout << "Incorrect password!" << std::endl;
		loginFails++;
		return;
	}

	strcpy(task, newTask);
}

size_t Secret::getLoginFails() const {
	return loginFails;
}