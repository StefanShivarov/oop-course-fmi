#pragma once

//From Github/Angeld55

class Date
{

private:
	unsigned int MAX_DAYS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	unsigned int day = 1;
	unsigned int month = 1;
	unsigned int year = 1;

	bool isLeapYear() const;

public: 

	Date(unsigned int day, unsigned int month, unsigned int year);

	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;

	void setDay(unsigned int day);
	void setMonth(unsigned int month);
	void setYear(unsigned int year);

	int compareTo(const Date& otherDate) const;
};

