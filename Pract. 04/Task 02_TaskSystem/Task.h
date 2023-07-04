#pragma once
#include <fstream>

const short MAX_TITLE_LENGTH = 30;
const short MAX_DESCRIPTION_LENGTH = 200;

class Task
{

	char title[MAX_TITLE_LENGTH + 1];
	char description[MAX_DESCRIPTION_LENGTH + 1];
	int points = 0;

public:

	Task() = default;
	Task(const char* title, const char* desc, int points);

	const char* getTitle() const;
	const char* getDescription() const;
	int getPoints() const;

	void setTitle(const char* newTitle);
	void setDescription(const char* desc);
	void setPoints(int newPoints);

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
};