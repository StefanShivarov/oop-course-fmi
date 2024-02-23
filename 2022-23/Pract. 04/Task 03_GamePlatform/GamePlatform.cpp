#include "GamePlatform.h"
#include <iostream>

void GamePlatform::addGame(const Game& game) {

	if (gamesAmount >= MAX_GAMES_AMOUNT) {
		std::cout << "Platform is full!" << std::endl;
		return;
	}

	games[++gamesAmount] = game;
}

void GamePlatform::removeGame(size_t index) {

	if (index >= gamesAmount) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}

	for (int i = index; i < gamesAmount - 1; i++) {

		Game temp = games[i];
		games[i] = games[i + 1];
		games[i + 1] = temp;
	}

	gamesAmount--;
}

void GamePlatform::printAllGames() const {

	for (int i = 0; i < gamesAmount; i++) {
		games[i].print();
	}
}

void GamePlatform::printFreeGames() const {

	for (int i = 0; i < gamesAmount; i++) {
		if (games[i].isFree()) {
			games[i].print();
		}
	}
}

const Game& GamePlatform::getGameByIndex(size_t index) const {

	if (index >= gamesAmount) {
		std::cout << "Invalid index!" << std::endl;
		return;
	}

	return games[index];
}

const Game& GamePlatform::getCheapestGame() const {

	int cheapestIndex = 0;
	for (int i = 0; i < gamesAmount; i++) {

		if (games[i].getPrice() < games[cheapestIndex].getPrice()) {
			cheapestIndex = i;
		}
	}

	return games[cheapestIndex];
}

const Game& GamePlatform::getMostExpensiveGame() const {

	int mostExpensiveIndex = 0;
	for (int i = 0; i < gamesAmount; i++) {

		if (games[i].getPrice() > games[mostExpensiveIndex].getPrice()) {
			mostExpensiveIndex = i;
		}
	}

	return games[mostExpensiveIndex];
}

void GamePlatform::printGameByIndex(size_t index) const {

	getGameByIndex(index).print();
}

void GamePlatform::printCheapestGame() const {

	getCheapestGame().print();
}

void GamePlatform::printMostExpensiveGame() const {

	getMostExpensiveGame().print();
}

void GamePlatform::saveToFile(const char* filePath) const {

	std::ofstream ofs(filePath);

	if (!ofs.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	for (int i = 0; i < gamesAmount; i++) {
		games[i].writeToFile(ofs);
	}

	ofs.close();
}

void GamePlatform::loadFromFile(const char* filePath) {

	std::ifstream ifs(filePath);

	if (!ifs) {
		std::cout << "Error!" << std::endl;
		return;
	}

	int i = 0;
	while (!ifs.eof()) {
		games[i].readFromFile(ifs);
		i++;
	}

	gamesAmount = i + 1;
	ifs.close();
}