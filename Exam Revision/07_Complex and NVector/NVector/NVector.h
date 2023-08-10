#pragma once
#include <iostream>

class NVector {
	
	int* data;
	size_t size;

	void copyFrom(const NVector& other);
	void free();

public:

	NVector();
	NVector(size_t n);
	NVector(const NVector& other);
	NVector& operator=(const NVector& other);
	~NVector();

	NVector& operator+=(const NVector& other);
	NVector& operator-=(const NVector& other);
	NVector& operator*=(size_t scalar);

	double length() const;
	void print() const;
	size_t getSize() const;

	int& operator[](size_t index);
	int operator[](size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const NVector& vector);
	friend std::istream& operator>>(std::istream& is, NVector& vector);
};

NVector operator+(const NVector& lhs, const NVector& rhs);
NVector operator-(const NVector& lhs, const NVector& rhs);
NVector operator*(const NVector& vector, size_t scalar);
NVector operator*(size_t scalar, const NVector& vector);

bool operator||(const NVector& lhs, const NVector& rhs);//parallel
bool operator|=(const NVector& lhs, const NVector& rhs);//perpendicular
size_t operator%(const NVector& lhs, const NVector& rhs);//scalar product