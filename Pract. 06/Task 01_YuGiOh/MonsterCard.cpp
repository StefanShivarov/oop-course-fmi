#include "MonsterCard.h"
#include <cstring>
#pragma warning (disable: 4996)

void MonsterCard::setName(const char* name) {

	if (name == nullptr) {
		return;
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void MonsterCard::setAttackPoints(unsigned points) {
	attackPoints = points;
}

void MonsterCard::setDefensePoints(unsigned points) {
	defensePoints = points;
}

void MonsterCard::free() {

	delete[] name;
	name = nullptr;
	attackPoints = 0;
	defensePoints = 0;
}

void MonsterCard::copyFrom(const MonsterCard& other) {

	setName(other.name);
	setAttackPoints(other.attackPoints);
	setDefensePoints(other.defensePoints);
}

MonsterCard::MonsterCard(const MonsterCard& other) {

	copyFrom(other);
}

MonsterCard& MonsterCard::operator=(const MonsterCard& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

MonsterCard::~MonsterCard() {
	free();
}

const char* MonsterCard::getName() const {
	return name;
}

unsigned MonsterCard::getAttackPoints() const {
	return attackPoints;
}

unsigned MonsterCard::getDefensePoints() const {
	return defensePoints;
}