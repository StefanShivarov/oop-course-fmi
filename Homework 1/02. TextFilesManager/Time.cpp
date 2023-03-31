#include "Time.h"

//Some of the code is from Github/Angeld55

Time::Time(unsigned int hours, unsigned int minutes, unsigned int seconds) {
	setHours(hours);
	setMinutes(minutes);
	setSeconds(seconds);
}

unsigned int Time::getHours() const{
	return hours;
}

unsigned int Time::getMinutes() const {
	return minutes;
}

unsigned int Time::getSeconds() const {
	return seconds;
}

void Time::setHours(unsigned int hours) {
	if (hours > 23) {
		hours = 23;
	}
	this->hours = hours;
}

void Time::setMinutes(unsigned int minutes) {
	if (minutes > 59) {
		minutes = 59;
	}
	this->minutes = minutes;
}

void Time::setSeconds(unsigned int seconds) {
	if (seconds > 59) {
		seconds = 59;
	}
	this->seconds = seconds;
}

unsigned int Time::convertToSeconds() const {
	return this->seconds + this->minutes * 60 + this->hours * 3600;
}

int Time::compareTo(const Time& otherTime) const {
	
	const unsigned int timeInSeconds = this->convertToSeconds();
	const unsigned int otherTimeInSeconds = otherTime.convertToSeconds();
	if (timeInSeconds > otherTimeInSeconds) {
		return 1;
	}
	else if (timeInSeconds < otherTimeInSeconds) {
		return -1;
	}

	return 0;
}
