#include "MyString.h"
#include <cstring>
#pragma warning (disable: 4996)

void MyString::free() {

	delete[] data;
	data = nullptr;
	size = 0;
}

void MyString::copyFrom(const MyString& other) {

	size = other.size;
	data = new char[size + 1];
	strcpy(data, other.data);
}

void MyString::move(MyString&& other) {

	size = other.size;
	data = other.data;
	other.data = nullptr;
	other.size = 0;
}

MyString::MyString(size_t capacity) {

	size = capacity - 1;
	data = new char[capacity];
}

MyString::MyString() : MyString(1) {

	data[0] = '\0';
}

MyString::MyString(const char* data) : MyString(strlen(data) + 1) {

	strcpy(this->data, data);
}

MyString::MyString(const MyString& other) {
	copyFrom(other);
}

MyString::MyString(MyString&& other) noexcept {
	move(std::move(other));
}

MyString& MyString::operator=(const MyString& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other) {

	if (this != &other) {
		free();
		move(std::move(other));
	}
	return *this;
}

MyString::~MyString() {
	free();
}

char& MyString::operator[](size_t index) {
	return data[index];
}

char MyString::operator[](size_t index) const {
	return data[index];
}

size_t MyString::length() const {
	return size;
}

const char* MyString::c_str() const {
	return data;
}

MyString MyString::substr(size_t beginIndex, size_t howMany) const {

	if (beginIndex + howMany > size) {
		throw std::length_error("Error! Substring is out of range!");
	}

	MyString result(howMany + 1);
	for (int i = 0; i < howMany; i++) {
		result[i] = data[beginIndex + i];
	}
	result[howMany] = '\0';
	return result;
}

MyString& MyString::operator+=(const MyString& other) {

	size += other.size;
	char* result = new char[size + 1];
	strcat(result, data);
	strcat(result, other.data);
	delete[] data;
	data = result;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {

	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString& str) {

	char buff[1024];
	is >> buff;
	delete[] str.data;
	str.size = strlen(buff);
	str.data = new char[str.size + 1];
	strcpy(str.data, buff);
	return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {

	MyString result(lhs);
	result += rhs;
	return result;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
	return !(lhs == rhs);
}

bool operator<(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const MyString& lhs, const MyString& rhs) {
	return !(lhs <= rhs);
}

bool operator >=(const MyString& lhs, const MyString& rhs) {
	return !(lhs < rhs);
}