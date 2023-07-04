#pragma once
#include "Game.h"

const short MAX_GAMES_AMOUNT = 20;

class GamePlatform
{

	Game games[MAX_GAMES_AMOUNT];
	int gamesAmount = 0;

public:

	GamePlatform() = default;

	void addGame(const Game& game);
	void removeGame(size_t index);

	const Game& getGameByIndex(size_t index) const;
	const Game& getCheapestGame() const;
	const Game& getMostExpensiveGame() const;
	void printGameByIndex(size_t index) const;
	void printCheapestGame() const;
	void printMostExpensiveGame() const;

	void printAllGames() const;
	void printFreeGames() const;

	void saveToFile(const char* filePath) const;
	void loadFromFile(const char* filePath);
};