#include "Server.h"
#include <cstring>
#include <iostream>

void mySwap(User& user1, User& user2) {
	User temp = user1;
	user1 = user2;
	user2 = temp;
}

size_t Server::getUserIndexByUsername(const char* username) const {
	for (size_t i = 0; i < usersAmount; i++) {
		if (strcmp(users[i].getUsername(), username) == 0) {
			return i;
		}
	}
	return -1;
}

size_t Server::getIndexOfMostAccessedUser() const {

	if (usersAmount == 0) {
		return -1;
	}
	
	size_t mostAccessedIndex = 0;
	for (size_t i = 0; i < usersAmount; i++) {
		if (users[i].getAccessCount() > users[mostAccessedIndex].getAccessCount()) {
			mostAccessedIndex = i;
		}
	}
	return mostAccessedIndex;
}

bool Server::containsUser(const char* username) const {
	return getUserIndexByUsername(username) != -1 ? true : false;
}

void Server::addUser(const User& user) {
	if (usersAmount >= MAX_USERS_COUNT) {
		return;
	}

	users[usersAmount] = user;
	usersAmount++;
}

void Server::removeUser(const char* username) {
	
	const size_t indexToRemove = getUserIndexByUsername(username);
	if (indexToRemove == -1) {
		return;
	}
	else {
		mySwap(users[indexToRemove], users[usersAmount - 1]);
		usersAmount--;
	}
}

void Server::printAllUsersInfo() const {
	for (size_t i = 0; i < usersAmount; i++) {
		std::cout << users[i].getUsername() << std::endl;
	}
}

void Server::printMostAccessedUser() const {

	std::cout << "Most accessed user: " << users[getIndexOfMostAccessedUser()].getUsername() << std::endl;
}

void Server::readFromBinaryFile() {
	std::ifstream ifs("server.bin", std::ios::binary);

	if (!ifs.is_open()) {
		return;
	}

	ifs.read((char*)&usersAmount, sizeof(usersAmount));
	for (size_t i = 0; i < usersAmount; i++) {
		users[i].readFromBinaryFile(ifs);
	}

	ifs.close();
}

void Server::writeToBinaryFile() const {
	std::ofstream ofs("server.bin", std::ios::binary);

	if (!ofs.is_open()) {
		return;
	}

	ofs.write((const char*)&usersAmount, sizeof(usersAmount));
	for (size_t i = 0; i < usersAmount; i++) {
		users[i].writeToBinaryFile(ofs);
	}

	ofs.close();
}