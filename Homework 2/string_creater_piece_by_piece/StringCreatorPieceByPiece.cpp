#include "StringCreatorPieceByPiece.h"
#pragma warning(disable: 4996)

const size_t DEFAULT_INITIAL_CAPACITY = 1;

StringCreatorPieceByPiece::StringCreatorPieceByPiece(): StringCreatorPieceByPiece(DEFAULT_INITIAL_CAPACITY) {}

StringCreatorPieceByPiece::StringCreatorPieceByPiece(size_t initialCapacity): capacity(initialCapacity), piecesAmount(0) {
	pieces = new StringPiece* [initialCapacity];
}

StringCreatorPieceByPiece& StringCreatorPieceByPiece::operator=(const StringCreatorPieceByPiece& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

StringCreatorPieceByPiece::StringCreatorPieceByPiece(const StringCreatorPieceByPiece& other) {
	copyFrom(other);
}

StringCreatorPieceByPiece::StringCreatorPieceByPiece(StringCreatorPieceByPiece&& other) {
	move(std::move(other));
}

StringCreatorPieceByPiece& StringCreatorPieceByPiece::operator=(StringCreatorPieceByPiece&& other) {
	if (this != &other) {
		free();
		move(std::move(other));
	}
	return *this;
}

StringCreatorPieceByPiece::~StringCreatorPieceByPiece() {
	free();
}

void StringCreatorPieceByPiece::free() {
	for (size_t i = 0; i < piecesAmount; i++) {
		delete pieces[i];
	}
	delete[] pieces;
	capacity = piecesAmount = 0;
}

void StringCreatorPieceByPiece::copyFrom(const StringCreatorPieceByPiece& other) {
	capacity = other.capacity;
	piecesAmount = other.piecesAmount;
	pieces = new StringPiece* [capacity];

	for (size_t i = 0; i < piecesAmount; i++) {
		if (other.pieces[i] == nullptr) {
			pieces[i] = nullptr;
		}
		else {
			pieces[i] = new StringPiece(*(other.pieces[i]));
		}
	}
}

void StringCreatorPieceByPiece::move(StringCreatorPieceByPiece&& other) {
	capacity = other.capacity;
	piecesAmount = other.piecesAmount;
	pieces = other.pieces;
	for (size_t i = 0; i < other.capacity; i++) {
		other.pieces[i] = nullptr;
	}
}

void StringCreatorPieceByPiece::resize() {
	capacity *= 2;
	StringPiece** temp = new StringPiece * [capacity] {nullptr};
	for (size_t i = 0; i < piecesAmount; i++) {
		temp[i] = pieces[i];
	}
	delete[] pieces;
	pieces = temp;
}

void StringCreatorPieceByPiece::addPiece(const char* str) {
	if (piecesAmount >= capacity) {
		resize();
	}

	bool foundEmptyIndexBeforeLast = false;
	for (unsigned short i = 0; i < piecesAmount; i++) {
		if (!pieces[i]) {
			pieces[i] = new StringPiece(str);
			foundEmptyIndexBeforeLast = true;
			break;
		}
	}
	if (!foundEmptyIndexBeforeLast) {
		pieces[piecesAmount] = new StringPiece(str);
	}
	piecesAmount++;
}

void StringCreatorPieceByPiece::addPieceAtIndex(size_t index, const char* str) {

	if (index >= capacity) {
		throw std::exception("Invalid index!");
	}

	if (pieces[index]) {
		delete pieces[index];
	}

	pieces[index] = new StringPiece(str);
	piecesAmount++;
}

void StringCreatorPieceByPiece::remove(size_t index) {

	if (index >= capacity) {
		throw std::exception("Invalid index!");
	}

	if (pieces[index]) {
		delete pieces[index];
	}

	pieces[index] = nullptr;
}

void StringCreatorPieceByPiece::swap(size_t firstIndex, size_t secondIndex) {

	if (firstIndex >= capacity || secondIndex >= capacity) {
		throw std::exception("Invalid index!");
	}

	StringPiece* temp = pieces[firstIndex];
	pieces[firstIndex] = pieces[secondIndex];
	pieces[secondIndex] = temp;
}

size_t StringCreatorPieceByPiece::length() const {
	size_t lengthCounter = 0;
	for (size_t i = 0; i < capacity; i++) {
		if (pieces[i]) {
			lengthCounter += pieces[i]->length();
		}
	}
	return lengthCounter;
}

MyString StringCreatorPieceByPiece::getString() const {

	char buff[1024];
	
	for (size_t i = 0; i < capacity; i++) {
		if (pieces[i]) {
			strcat(buff, pieces[i]->getData());
		}
	}

	MyString str(buff);
	return str;
}

const StringPiece& StringCreatorPieceByPiece::operator[](size_t index) const {
	if (index >= capacity) {
		throw std::exception("Invalid index!");
	}
	return *pieces[index];
}

StringPiece& StringCreatorPieceByPiece::operator[](size_t index) {
	if (index >= capacity) {
		throw std::exception("Invalid index!");
	}
	return *pieces[index];
}
