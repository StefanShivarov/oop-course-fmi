#include "Date.h"
#include<iostream>
//From Github/Angeld55

Date::Date(unsigned int day, unsigned int month, unsigned int year) {
	setYear(year);
	setMonth(month);
	setDay(day);
}

unsigned int Date::getDay() const {
	return day;
}

unsigned int Date::getMonth() const {
	return month;
}

unsigned int Date::getYear() const {
	return year;
}

void Date::setYear(unsigned int year) {
	if (year == this->year) {
		return;
	}

	this->year = year;
	if (isLeapYear()) {
		MAX_DAYS[1] = 29;
	}
	else {
		MAX_DAYS[1] = 28;
	}	
	setDay(getDay());

}

void Date::setMonth(unsigned int month) {
	if (month == this->month) {
		return;
	}

	if (month == 0 || month > 12) {
		month = 1;
	}

	this->month = month;
	setDay(getDay());

}

void Date::setDay(unsigned int day) {
	if (day == this->day) {
		return;
	}

	if (day == 0 || day > MAX_DAYS[month - 1]) {
		day = 1;
	}
	this->day = day;
}


bool Date::isLeapYear() const {
	if (year <= 1916) {
		return year % 4 == 0;
	}
	else {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
}

int Date::compareTo(const Date& otherDate) const {

	const unsigned int otherYear = otherDate.getYear();
	const unsigned int otherMonth = otherDate.getMonth();
	const unsigned int otherDay = otherDate.getDay();

	if (this->year > otherYear) {
		return 1;
	}
	else if (this->year < otherYear) {
		return -1;
	}
	else if (this->month > otherMonth){
		return 1;
	}
	else if (this->month < otherMonth) {
		return -1;
	}
	else if (this->day > otherDay) {
		return 1;
	}
	else if (this->day < otherDay) {
		return -1;
	}

	return 0;
}


