#pragma once
#include "Time.h"
#include "Date.h"

class Event
{

	char name[21];
	Date date;
	Time startTime;
	Time endTime;

public:

	Event(const char* name, const Date& date, const Time& start, const Time& end);

	const char* getName() const;
	const Date& getDate() const;
	const Time& getStartTime() const;
	const Time& getEndTime() const;

	void setName(const char* name);
	void setDate(const Date& date);
	void setStartTime(const Time& time);
	void setEndTime(const Time& time);
};