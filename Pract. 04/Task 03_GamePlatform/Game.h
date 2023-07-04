#pragma once
#include <fstream>

const short MAX_TITLE_LENGTH = 30;

class Game
{

	char title[MAX_TITLE_LENGTH + 1] = "\0";
	double price = 0.0;
	bool isAvailable = false;

public:

	Game() = default;
	Game(const char* title, double price, bool isAvailable = true);

	const char* getTitle() const;
	void setTitle(const char* newTitle);
	double getPrice() const;
	void setPrice(double newPrice);
	bool getIsAvailable() const;
	void setAvailable(bool isAvailable);

	bool isFree() const;
	void print() const;

	void writeToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);
};

