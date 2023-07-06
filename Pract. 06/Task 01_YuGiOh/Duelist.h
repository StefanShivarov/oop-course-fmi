#pragma once
#include "Deck.h"

class Duelist {

	char* name = nullptr;
	Deck deck;

public:

	Duelist() = default;
	Duelist(const char* name, const Deck& deck);
	Duelist(const Duelist& other);
	Duelist& operator=(const Duelist& other);
	~Duelist();

	size_t getMonsterCardsSize() const;
	size_t getMagicCardsSize() const;

	bool addMagicCard(const MagicCard& card);
	bool addMonsterCard(const MonsterCard& card);
	bool addMagicCardAtIndex(const MagicCard& card, size_t index);
	bool addMonsterCardAtIndex(const MonsterCard& card, size_t index);
	bool removeMagicCard(size_t index);
	bool removeMonsterCard(size_t index);

	const char* getName() const;
	void setName(const char* name);

private:

	void free();
	void copyFrom(const Duelist& other);
};