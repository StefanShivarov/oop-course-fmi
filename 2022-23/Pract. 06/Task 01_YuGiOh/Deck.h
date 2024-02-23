#pragma once
#include "MagicCard.h"
#include "MonsterCard.h"

const short MAX_DECK_SIZE = 40;

class Deck
{

	MagicCard magicCards[MAX_DECK_SIZE / 2];
	MonsterCard monsterCards[MAX_DECK_SIZE / 2];

	bool magicCardsPositions[MAX_DECK_SIZE / 2]{ false };
	bool monsterCardsPositions[MAX_DECK_SIZE / 2]{ false };

	size_t magicCardsSize = 0;
	size_t monsterCardsSize = 0;

public:

	Deck() = default;
	
	size_t getMonsterCardsSize() const;
	size_t getMagicCardsSize() const;

	bool addMagicCard(const MagicCard& card);
	bool addMonsterCard(const MonsterCard& card);
	bool addMagicCardAtIndex(const MagicCard& card, size_t index);
	bool addMonsterCardAtIndex(const MonsterCard& card, size_t index);
	bool removeMagicCard(size_t index);
	bool removeMonsterCard(size_t index);
};