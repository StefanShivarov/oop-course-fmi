#include "MagicCard.h"
#include <cstring>
#pragma warning (disable: 4996)

void MagicCard::setName(const char* name) {

	if (name == nullptr) {
		return;
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void MagicCard::setType(MagicCardType type) {
	this->type = type;
}

void MagicCard::free() {

	delete[] name;
	name = nullptr;
	type = MagicCardType::unknown;
}

void MagicCard::copyFrom(const MagicCard& other) {

	setName(other.name);
	setType(other.type);
}

MagicCard::MagicCard(const MagicCard& other) {
	copyFrom(other);
}

MagicCard& MagicCard::operator=(const MagicCard& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

MagicCard::~MagicCard() {
	free();
}

const char* MagicCard::getName() const {
	return name;
}

MagicCardType MagicCard::getType() const {
	return type;
}