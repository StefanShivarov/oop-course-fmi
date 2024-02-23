#include "Deck.h"

size_t Deck::getMagicCardsSize() const {
	return magicCardsSize;
}

size_t Deck::getMonsterCardsSize() const {
	return monsterCardsSize;
}

bool Deck::addMagicCardAtIndex(const MagicCard& card, size_t index) {

	if (index >= MAX_DECK_SIZE / 2) {
		return false;
	}

	if (magicCardsPositions[index]) {
		return false;
	}

	magicCardsPositions[index] = true;
	magicCards[index] = card;
	magicCardsSize++;
	return true;
}

bool Deck::addMagicCard(const MagicCard& card) {

	for (int i = 0; i < MAX_DECK_SIZE / 2; i++) {
		if (!magicCardsPositions[i]) {
			addMagicCardAtIndex(card, i);
			return true;
		}
	}
	return false;
}

bool Deck::addMonsterCardAtIndex(const MonsterCard& card, size_t index) {

	if (index >= MAX_DECK_SIZE / 2) {
		return false;
	}

	if (monsterCardsPositions[index]) {
		return false;
	}

	monsterCardsPositions[index] = true;
	monsterCards[index] = card;
	monsterCardsSize++;
	return true;
}

bool Deck::addMonsterCard(const MonsterCard& card) {

	for (int i = 0; i < MAX_DECK_SIZE / 2; i++) {
		if (!monsterCardsPositions[i]) {
			addMonsterCardAtIndex(card, i);
			return true;
		}
	}
	return false;
}

bool Deck::removeMagicCard(size_t index) {

	if (!magicCardsPositions[index]) {
		return false;
	}

	magicCardsPositions[index] = false;
	magicCardsSize--;
	return true;
}

bool Deck::removeMonsterCard(size_t index) {

	if (!monsterCardsPositions[index]) {
		return false;
	}

	monsterCardsPositions[index] = false;
	monsterCardsSize--;
	return true;
}