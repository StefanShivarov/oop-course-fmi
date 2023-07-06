#include "Duelist.h"
#include <cstring>
#pragma warning (disable: 4996)

void Duelist::setName(const char* name) {

	if (name == nullptr) {
		return;
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}


Duelist::Duelist(const char* name, const Deck& deck) {

	setName(name);
	this->deck = deck;
}

void Duelist::free() {

	delete[] name;
	name = nullptr;

}

void Duelist::copyFrom(const Duelist& other) {

	setName(other.name);
	this->deck = other.deck;
}

Duelist::Duelist(const Duelist& other) {
	copyFrom(other);
}

Duelist& Duelist::operator=(const Duelist& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Duelist::~Duelist() {
	free();
}

const char* Duelist::getName() const {
	return name;
}

size_t Duelist::getMagicCardsSize() const {
	return deck.getMagicCardsSize();
}

size_t Duelist::getMonsterCardsSize() const {
	return deck.getMonsterCardsSize();
}

bool Duelist::addMagicCard(const MagicCard& card) {
	
	return deck.addMagicCard(card);
}

bool Duelist::addMonsterCard(const MonsterCard& card) {

	return deck.addMonsterCard(card);
}

bool Duelist::addMagicCardAtIndex(const MagicCard& card, size_t index) {

	return deck.addMagicCardAtIndex(card, index);
}

bool Duelist::addMonsterCardAtIndex(const MonsterCard& card, size_t index) {

	return deck.addMonsterCardAtIndex(card, index);
}

bool Duelist::removeMagicCard(size_t index) {

	return deck.removeMagicCard(index);
}

bool Duelist::removeMonsterCard(size_t index) {

	return deck.removeMonsterCard(index);
}