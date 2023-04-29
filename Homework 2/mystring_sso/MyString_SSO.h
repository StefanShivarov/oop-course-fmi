#pragma once
#include <iostream>

const unsigned short MAX_LENGTH_SSO = 15;

class MyString_SSO
{
	unsigned short currentLength;

	union Data {
		char* heapData;
		char stackData[MAX_LENGTH_SSO + 1];
	} data;

	explicit MyString_SSO(size_t capacity);

public:

	MyString_SSO();
	MyString_SSO(const char* data);
	MyString_SSO(const MyString_SSO& other);
	MyString_SSO& operator=(const MyString_SSO& other);
	~MyString_SSO();

	MyString_SSO(MyString_SSO&& other);
	MyString_SSO& operator=(MyString_SSO&& other);

	size_t length() const;
	MyString_SSO& operator+=(const MyString_SSO& other);

	MyString_SSO substr(size_t begin, size_t howMany) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;

	friend MyString_SSO operator+(const MyString_SSO& lhs, const MyString_SSO& rhs);
	friend std::istream& operator>>(std::istream&, MyString_SSO& str);

private:

	void free();
	void copyFrom(const MyString_SSO& other);
	void copyData(size_t length, const char* str);
};

MyString_SSO operator+(const MyString_SSO& lhs, const MyString_SSO& rhs);

std::ostream& operator<<(std::ostream& os, const MyString_SSO& str);

std::istream& operator>>(std::istream& os, MyString_SSO& str);

bool operator<(const MyString_SSO& lhs, const MyString_SSO& rhs);
bool operator<=(const MyString_SSO& lhs, const MyString_SSO& rhs);
bool operator>=(const MyString_SSO& lhs, const MyString_SSO& rhs);
bool operator>(const MyString_SSO& lhs, const MyString_SSO& rhs);
bool operator==(const MyString_SSO& lhs, const MyString_SSO& rhs);
bool operator!=(const MyString_SSO& lhs, const MyString_SSO& rhs);