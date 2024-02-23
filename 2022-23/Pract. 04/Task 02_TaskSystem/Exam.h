#pragma once
#include "Task.h"

const short MAX_TASKS_AMOUNT = 10;

class Exam
{

	Task tasks[MAX_TASKS_AMOUNT];
	int minPointsToPass = 0;
	int tasksAmount = 0;

public:

	Exam() = default;
	Exam(int minPointsToPass);

	void changeMin(int newMin);
	int getMax() const;

	void writeToBinaryFile(const char* filePath) const;
	void readFromBinaryFile(const char* filePath);
};