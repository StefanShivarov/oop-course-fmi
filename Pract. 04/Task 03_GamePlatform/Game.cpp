#include "Game.h"
#include <cstring>
#include <iostream>
#pragma warning (disable: 4996)

void Game::setTitle(const char* newTitle) {

	size_t length = strlen(newTitle);
	if (!newTitle || length > MAX_TITLE_LENGTH || length == 0) {
		std::cout << "Invalid title!" << std::endl;
		return;
	}

	strcpy(title, newTitle);
}

void Game::setPrice(double newPrice) {

	if (newPrice < 0) {
		std::cout << "Invalid price!" << std::endl;
		return;
	}

	price = newPrice;
}

void Game::setAvailable(bool isAvailable) {
	this->isAvailable = isAvailable;
}

Game::Game(const char* title, double price, bool isAvailable) {

	setTitle(title);
	setPrice(price);
	setAvailable(isAvailable);
}

bool Game::isFree() const {
	return price == 0;
}

void Game::print() const {
	
	std::cout << "Title: " << title << "Price: " << price << "Available: " << (isAvailable ? "True" : "False") << std::endl;
}

const char* Game::getTitle() const {
	return title;
}

double Game::getPrice() const {
	return price;
}

bool Game::getIsAvailable() const {
	return isAvailable;
}

void Game::writeToFile(std::ofstream& ofs) const {

	if (!ofs.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	ofs << title << std::endl << price << std::endl << isAvailable << std::endl;
}

void Game::readFromFile(std::ifstream& ifs) {

	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	ifs.getline(title, MAX_TITLE_LENGTH, '\n');
	ifs >> price >> isAvailable;
}