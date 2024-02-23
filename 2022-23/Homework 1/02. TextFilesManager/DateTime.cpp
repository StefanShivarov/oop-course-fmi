#include "DateTime.h"
#include <iostream>

DateTime::DateTime(const Date& date, const Time& time) : date(date), time(time){
}

DateTime::DateTime(unsigned int day, unsigned int month, unsigned int year, unsigned int hours,
	unsigned int minutes, unsigned int seconds): date(day, month, year), time(hours, minutes, seconds) {
}

const Date& DateTime::getDate() const {
	return date;
}

const Time& DateTime::getTime() const {
	return time;
}

void DateTime::setDate(const Date& date) {
	this->date = date;
}

void DateTime::setTime(const Time& time) {
	this->time = time;
}

void DateTime::print() const {
	std::cout << this->time.getHours() << ":" << this->time.getMinutes() << ":" << this->time.getSeconds() <<
		" " << this->date.getDay() << "/" << this->date.getMonth() << "/" << this->date.getYear() << std::endl;
}


int DateTime::compareTo(const DateTime& otherDateTime) {
	
	const int dateComparison = this->date.compareTo(otherDateTime.getDate());
	const int timeComparison = this->time.compareTo(otherDateTime.getTime());

	if (dateComparison != 0) {
		return dateComparison;
	}
	else if (timeComparison != 0) {
		return timeComparison;
	}
	return 0;
}