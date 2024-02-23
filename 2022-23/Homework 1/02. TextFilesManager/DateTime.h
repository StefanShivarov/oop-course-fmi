#pragma once
#include "Date.h"
#include "Time.h"
class DateTime
{
private:

	Date date;
	Time time;

public:

	DateTime(const Date& date, const Time& time);
	DateTime(unsigned int day, unsigned int month, unsigned int year, unsigned int hours,
		unsigned int minutes, unsigned int seconds);

	const Date& getDate() const;
	const Time& getTime() const;
	
	void setDate(const Date& date);
	void setTime(const Time& time);

	void print() const;

	int compareTo(const DateTime& otherDateTime);
};

