#include "MyString_SSO.h"
#pragma warning (disable: 4996)

void MyString_SSO::free() {

	if (currentLength <= MAX_LENGTH_SSO) {
		data.stackData[0] = '\0';
	}
	else {
		delete[] data.heapData;
	}
	currentLength = 0;
}

void MyString_SSO::copyFrom(const MyString_SSO& other) {
	currentLength = other.currentLength;
	copyData(currentLength, other.c_str());
}

void MyString_SSO::copyData(size_t length, const char* str) {

	if (length <= MAX_LENGTH_SSO) {
		strcpy(data.stackData, str);
	}
	else {
		strcpy(data.heapData, str);
	}
}

MyString_SSO::MyString_SSO(size_t capacity) {

	currentLength = capacity - 1;
	if (currentLength > MAX_LENGTH_SSO) {
		data.heapData = new char[capacity];
		data.heapData[currentLength] = '\0';

	}
	else {
		data.stackData[currentLength] = '\0';

	}
}

MyString_SSO::MyString_SSO() : MyString_SSO(1) {}

MyString_SSO::MyString_SSO(const char* str) : MyString_SSO(strlen(str) + 1) {
	copyData(currentLength, str);
}

MyString_SSO::MyString_SSO(const MyString_SSO& other) {
	copyFrom(other);
}

MyString_SSO& MyString_SSO::operator=(const MyString_SSO& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

MyString_SSO::~MyString_SSO() {
	free();
}

size_t MyString_SSO::length() const {
	return currentLength;
}

MyString_SSO::MyString_SSO(MyString_SSO&& other) {

	data = other.data;
	if (other.currentLength > MAX_LENGTH_SSO) {
		other.data.heapData = nullptr;
	}
	currentLength = other.currentLength;
}

MyString_SSO& MyString_SSO::operator=(MyString_SSO&& other) {

	if (this != &other) {
		free();
		data = other.data;
		if (other.currentLength > MAX_LENGTH_SSO) {
			other.data.heapData = nullptr;
		}
		currentLength = other.currentLength;
	}
	return *this;
}

const char* MyString_SSO::c_str() const {
	return (currentLength <= MAX_LENGTH_SSO) ? data.stackData : data.heapData;
}

char& MyString_SSO::operator[](size_t index) { //Not const access
	return (currentLength <= MAX_LENGTH_SSO) ? data.stackData[index] : data.heapData[index];
}

char MyString_SSO::operator[](size_t index) const { //Const access
	return (currentLength <= MAX_LENGTH_SSO) ? data.stackData[index] : data.heapData[index];
}

MyString_SSO MyString_SSO::substr(size_t begin, size_t howMany) const {

	if (begin + howMany > currentLength) {
		throw std::length_error("Error, substring out of range!");

	}

	MyString_SSO res(howMany + 1);
	
	for (size_t i = 0; i < howMany; i++) {
		res[i] = this->operator[](begin + i);
	}
	
	res[howMany] = '\0';
	return res;
}

MyString_SSO& MyString_SSO::operator+=(const MyString_SSO& other) {

	char* result = new char[(currentLength += other.currentLength) + 1];
	result[0] = '\0';
	strcpy(result, this->c_str());
	strcat(result, other.c_str());

	if (currentLength <= MAX_LENGTH_SSO) {
		strcpy(data.stackData, result);
		delete[] result;
	}
	else {
		delete[] data.heapData;
		data.heapData = result;
	}

	return *this;
}

MyString_SSO operator+(const MyString_SSO& lhs, const MyString_SSO& rhs) {

	MyString_SSO result(lhs.currentLength + rhs.currentLength + 1);

	result[0] = '\0';

	strcat((result.currentLength <= MAX_LENGTH_SSO) ? result.data.stackData : result.data.heapData, lhs.c_str());
	strcat((result.currentLength <= MAX_LENGTH_SSO) ? result.data.stackData : result.data.heapData, rhs.c_str());

	return result;
}

std::ostream& operator<<(std::ostream& os, const MyString_SSO& str) {
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString_SSO& str) {
	char buff[1024];
	is >> buff; // is.getLine(buff, 1024);

	if (str.currentLength > MAX_LENGTH_SSO) {
		delete[] str.data.heapData;
	}
	str.currentLength = strlen(buff);
	if (str.currentLength <= MAX_LENGTH_SSO) {
		str.data.heapData = new char[str.currentLength + 1];
		strcpy(str.data.heapData, buff);
	}
	else {
		strcpy(str.data.stackData, buff);
	}
	return is;
}

bool operator<(const MyString_SSO& lhs, const MyString_SSO& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString_SSO& lhs, const MyString_SSO& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const MyString_SSO& lhs, const MyString_SSO& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator>(const MyString_SSO& lhs, const MyString_SSO& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator==(const MyString_SSO& lhs, const MyString_SSO& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString_SSO& lhs, const MyString_SSO& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}