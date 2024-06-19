#include "Event.h"

Event::Event() : Event("", 1, 1, 1, 0, 0, 0, 0, 0, 0) {}

Event::Event(const char* name, const Date& date, const Time& startTime, const Time& endTime)
    : date(date), startTime(startTime), endTime(endTime)
{
    setName(name);
    validateTimes();
}

Event::Event(const char* name, unsigned day, unsigned month, unsigned year,
    unsigned startTimeHours, unsigned startTimeMins, unsigned startTimeSecs,
    unsigned endTimeHours, unsigned endTimeMins, unsigned endTimeSecs)
    : date(day, month, year), startTime(startTimeHours, startTimeMins, startTimeSecs),
        endTime(endTimeHours, endTimeMins, endTimeSecs) {}

const char* Event::getName() const
{
    return name;
}

const Date& Event::getDate() const
{
    return date;
}

const Time& Event::getStartTime() const
{
    return startTime;
}

const Time& Event::getEndTime() const
{
    return endTime;
}

void Event::setName(const char* str)
{
    if (strlen(str) >= MAX_NAME_LENGTH) {
        return;
    }
    strcpy(name, str);
}

void Event::validateTimes()
{
    if (compareTimes(startTime, endTime) <= -1) {
        std::swap(startTime, endTime);
    }
}
