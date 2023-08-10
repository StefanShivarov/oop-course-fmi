#include "NVector.h"

void NVector::free() {

	delete[] data;
	size = 0;
}

void NVector::copyFrom(const NVector& other) {

	size = other.size;
	data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

NVector::NVector(size_t n): size(n) {

	data = new int[n];
	for (int i = 0; i < n; i++) {
		data[i] = 0;
	}
}

NVector::NVector(): NVector(3) {}

NVector::NVector(const NVector& other) {
	copyFrom(other);
}

NVector::~NVector() {
	free();
}

NVector& NVector::operator=(const NVector& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

int& NVector::operator[](size_t index) {

	if (index >= size) {
		throw "Error! Invalid index!";
	}

	return data[index];
}

int NVector::operator[](size_t index) const {

	if (index >= size) {
		throw "Error! Invalid index!";
	}

	return data[index];
}

NVector& NVector::operator+=(const NVector& other) {

	if (size != other.size) {
		throw "Error! Vectors should be the same size!";
	}

	for (int i = 0; i < size; i++) {
		data[i] += other.data[i];
	}

	return *this;
}

NVector& NVector::operator-=(const NVector& other) {

	if (size != other.size) {
		throw "Error! Vectors should be the same size!";
	}

	for (int i = 0; i < size; i++) {
		data[i] -= other.data[i];
	}

	return *this;
}

NVector& NVector::operator*=(size_t scalar) {

	for (int i = 0; i < size; i++) {
		data[i] *= scalar;
	}
	return *this;
}

double NVector::length() const {

	size_t sumOfSquares = 0;
	for (int i = 0; i < size; i++) {
		sumOfSquares += data[i] * data[i]
	}
	return sqrt(sumOfSquares);
}

size_t NVector::getSize() const {
	return size;
}

void NVector::print() const {

	for (int i = 0; i < size; i++) {
		std::cout << data[i] << ' ';
	}
}

NVector operator+(const NVector& lhs, const NVector& rhs) {

	NVector result(lhs);
	result += rhs;
	return result;
}

NVector operator-(const NVector& lhs, const NVector& rhs) {

	NVector result(lhs);
	result += rhs;
	return result;
}

NVector operator*(const NVector& vector, size_t scalar) {

	NVector result(vector);
	result *= scalar;
	return result;
}

NVector operator*(size_t scalar, const NVector& vector) {

	return vector * scalar;
}

bool operator||(const NVector& lhs, const NVector& rhs)
{
	if (lhs.getSize() != rhs.getSize()) {
		throw "The vectors should have the same size!";
	}

	double lambda = 0;
	bool foundIndex = false;

	for (size_t i = 0; i < lhs.getSize(); i++) {
		if (lhs[i] && rhs[i]) {
			if (foundIndex == false) {
				lambda = (double)lhs[i] / rhs[i];
				foundIndex = true;
			}
			else if ((double)lhs[i] / (double)rhs[i] != lambda) {
				return false;
			}
		}
		else if ((lhs[i] == 0) ^ (rhs[i] == 0)) {
			return false;
		}
	}

	return true;
}

size_t operator%(const NVector& lhs, const NVector& rhs) {

	if (lhs.getSize() != rhs.getSize()) {
		throw "The vectors should have the same size!";
	}

	size_t result = 0;

	for (int i = 0; i < lhs.getSize(); i++) {
		result += lhs[i] * rhs[i];
	}
	return result;
}

bool operator|=(const NVector& lhs, const NVector& rhs) {

	return lhs % rhs == 0;
}

std::ostream& operator<<(std::ostream& os, const NVector& vector) {

	os << "[ ";
	for (int i = 0; i < vector.getSize(); i++) {
		os << vector[i] << ' ';	
	}

	os << " ]";
	return os;
}

std::istream& operator>>(std::istream& is, NVector& vector) {

	for (int i = 0; i < vector.getSize(); i++) {
		is >> vector[i];
	}
	return is;
}