#include "User.h"
#include <cstring>
#pragma warning(disable:4996)

void copyCharArray(char*& dest, const char* source) {

	dest = new char[strlen(source) + 1];
	strcpy(dest, source);
}

void readDynamicCharArrayFromBinaryFile(std::ifstream& ifs, char*& arr) {
	size_t arrLength;
	ifs.read((char*)&arrLength, sizeof(arrLength));
	arr = new char[arrLength + 1];
	ifs.read(arr, arrLength);
	arr[arrLength] = '\0';
}

void writeDynamicCharArrayToBinaryFile(std::ofstream& ofs, const char* arr) {
	size_t length = strlen(arr);
	ofs.write((const char*)&length, sizeof(length));
	ofs.write(arr, length);
}

void User::free() {
	delete[] username;
	delete[] password;
	username = password = nullptr;
	accessCount = 0;
}

void User::copyFrom(const User& other) {
	copyCharArray(this->username, other.username);
	copyCharArray(this->password, other.password);
	this->accessCount = other.accessCount;
}

User::User(const char* name, const char* password) {
	setUsername(name ? name : "\0");
	setPassword(password ? password : "\0");
}

User::User(const User & other) {
	copyFrom(other);
}

User& User::operator=(const User& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

User::~User() {
	free();
}

const char* User::getUsername() const {
	accessCount++;
	return username;
}

size_t User::getAccessCount() const {
	return accessCount;
}

void User::setUsername(const char* username) {

	if (!username) {
		return;
	}
	
	if (this->username) {
		delete[] this->username;
	}

	copyCharArray(this->username, username);
}

void User::setPassword(const char* password) {
	if (!password) {
		return;
	}

	if (this->password) {
		delete[] this->password;
	}

	copyCharArray(this->password, password);
}

void User::setAccessCount(size_t accessCount) {
	this->accessCount = accessCount;
}

void User::readFromBinaryFile(std::ifstream& ifs) {

	readDynamicCharArrayFromBinaryFile(ifs, username);
	readDynamicCharArrayFromBinaryFile(ifs, password);
	ifs.read((char*)accessCount, sizeof(accessCount));
}

void User::writeToBinaryFile(std::ofstream& ofs) const {

	writeDynamicCharArrayToBinaryFile(ofs, username);
	writeDynamicCharArrayToBinaryFile(ofs, password);
	ofs.write((const char*)&accessCount, sizeof(accessCount));
}