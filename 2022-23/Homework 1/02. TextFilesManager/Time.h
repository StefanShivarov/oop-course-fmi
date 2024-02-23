#pragma once
class Time
{
private:

	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;

	unsigned int convertToSeconds() const;
public:

	Time(unsigned int hours, unsigned int minutes, unsigned int seconds);

	unsigned int getHours() const;
	unsigned int getMinutes() const;
	unsigned int getSeconds() const;

	void setHours(unsigned int hours);
	void setMinutes(unsigned int minutes);
	void setSeconds(unsigned int seconds);

	int compareTo(const Time& otherTime) const;
};