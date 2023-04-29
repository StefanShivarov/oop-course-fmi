#include "StringPiece.h"
#include <cstring>
#include <iostream>
#pragma warning (disable: 4996)

StringPiece::StringPiece(const char* data) {
	setData(data);
}

const unsigned short StringPiece::length() const {
	return currentLength;
}

void StringPiece::removeLastKSymbols(unsigned short k) {
	if (k > MAX_SYMBOLS_AMOUNT) {
		throw std::exception("Error! The string piece contains less symbols than you want to remove.");
	}
	
	if (k > currentLength) {
		endIndex = startIndex = 0;
		currentLength = 0;
	}
	else {
		endIndex -= k;
		currentLength -= k;
	}
}

void StringPiece::replaceAt(unsigned short index, char replacement) {

	if (index >= MAX_SYMBOLS_AMOUNT) {
		throw std::exception("Invalid index to replace at!");
	}

	data[index] = replacement;
}

void checkLengthBeforeConcat(unsigned short length1, unsigned short length2) {
	if (length1 + length2 >= MAX_SYMBOLS_AMOUNT + 1) {
		throw std::exception("Error! Cannot concatenate because the result will exceed max length.");
	}
}

StringPiece& StringPiece::operator<<(const char* str) {

	const size_t appendLength = strlen(str);
	checkLengthBeforeConcat(currentLength, appendLength);
	unsigned short copyIndexCounter = 0;
	for (size_t i = currentLength; i < currentLength + appendLength; i++) {
		data[i] = str[copyIndexCounter++];
	}
	endIndex += appendLength;
	currentLength += appendLength;

	return *this;
}

StringPiece& StringPiece::operator<<(unsigned int number) {
	unsigned short appendLength = 0;
	unsigned int copy = number;
	while (copy != 0) {
		copy /= 10;
		appendLength++;
	}
	checkLengthBeforeConcat(currentLength, appendLength);
	for (unsigned short i = currentLength + appendLength - 1; i >= currentLength; i--) {
		data[i] = (number % 10) + '0';
	}
	endIndex += appendLength;
	currentLength += appendLength;

	return *this;
}

StringPiece& operator>>(const char* str, StringPiece& strPiece) {

	const size_t appendLength = strlen(str);
	checkLengthBeforeConcat(strPiece.currentLength, appendLength);
	size_t copyIndexCounter = appendLength - 1;
	strPiece.startIndex = MAX_SYMBOLS_AMOUNT - appendLength;

	for (unsigned short i = MAX_SYMBOLS_AMOUNT - 1; i >= MAX_SYMBOLS_AMOUNT - 1 - appendLength; i--) {
		strPiece.data[i - appendLength] = strPiece.data[i];
	}
	for (unsigned short i = MAX_SYMBOLS_AMOUNT - 1; i >= MAX_SYMBOLS_AMOUNT - 1 - appendLength; i--) {
		strPiece.data[i] = str[copyIndexCounter--];
	}
	strPiece.currentLength += appendLength;


	return strPiece;
}

StringPiece& operator>>(unsigned int number, StringPiece& strPiece) {

	unsigned short appendLength = 0;
	unsigned int copy = number;
	while (copy != 0) {
		copy /= 10;
		appendLength++;
	}
	checkLengthBeforeConcat(strPiece.currentLength, appendLength);
	strPiece.startIndex = MAX_SYMBOLS_AMOUNT - appendLength;
	for (unsigned short i = MAX_SYMBOLS_AMOUNT - 1; i >= MAX_SYMBOLS_AMOUNT - 1 - appendLength; i--) {
		strPiece.data[i - appendLength] = strPiece.data[i];
	}
	for (unsigned short i = MAX_SYMBOLS_AMOUNT-1; i < MAX_SYMBOLS_AMOUNT; i++) {
		strPiece.data[i] = (number % 10) + '0';
	}

	return strPiece;
}

const char* StringPiece::getData() {
	
	//Quick note: Without setting '\0', this method is almost irrelevant and very hard to implement !
	//if you cout << getData it might print some other elements because there is no '\0'...
	char result[MAX_SYMBOLS_AMOUNT]{};
	size_t indexToAdd = 0;
	if (startIndex <= endIndex) {
		for (size_t i = 0; i <= endIndex; i++) {
			result[indexToAdd++] = data[i];
		}
	}
	else {
		for (size_t i = startIndex; i < MAX_SYMBOLS_AMOUNT; i++) {
			result[indexToAdd++] = data[i];
		}

		for (size_t i = 0; i <= endIndex; i++) {
			result[indexToAdd++] = data[i];
		}
	}

	for (size_t i = 0; i < currentLength; i++) {
		data[i] = result[i];
	}
	
	return this->data;
}

void StringPiece::setData(const char* data){

	if (!data) {
		throw "Error! Incorrect data!";
	}
	if (strlen(data) > MAX_SYMBOLS_AMOUNT) {
		throw "Error! Data is too long!";
	}

	strcpy(this->data, data);
	startIndex = 0;
	currentLength = strlen(this->data);
	endIndex = currentLength - 1;
}