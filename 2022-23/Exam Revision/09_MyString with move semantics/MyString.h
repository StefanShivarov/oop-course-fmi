#pragma once
#include <iostream>

class MyString {

	char* data;
	size_t size;

	void copyFrom(const MyString& other);
	void move(MyString&& other);
	void free();

	explicit MyString(size_t capacity); // how many bytes to be allocated

public:

	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;
	~MyString();

	size_t length() const;
	MyString& operator+=(const MyString& other);

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;

	MyString substr(size_t beginIndex, size_t howMany) const;

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream& is, MyString& str);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);