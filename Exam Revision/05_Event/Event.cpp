#include "Event.h"
#include <cstring>
#pragma warning (disable: 4996)

Event::Event(const char* name, const Date& date, const Time& start, const Time& end): date(date), startTime(start), endTime(end) {
	setName(name);
	//some validation for date or times...
}

void Event::setName(const char* name) {

	if (strlen(name) > 20) {
		return;
	}

	strcpy(this->name, name);
}

void Event::setDate(const Date& date) {

	this->date = date;
}

void Event::setStartTime(const Time& time) {

	startTime = time;
}

void Event::setEndTime(const Time& time) {
	
	endTime = time;
}

const char* Event::getName() const {
	return name;
}

const Date& Event::getDate() const {
	return date;
}
const Time& Event::getStartTime() const {
	return startTime;
}
const Time& Event::getEndTime() const {
	return endTime;
}