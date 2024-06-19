#pragma once
#include "Date.h"
#include "Time.h"

constexpr unsigned MAX_NAME_LENGTH = 21;

class Event
{
public:
    Event();
    Event(const char* name, const Date& date, const Time& startTime, const Time& endTime);
    Event(const char* name, unsigned day, unsigned month, unsigned year,
        unsigned startTimeHours, unsigned startTimeMins, unsigned startTimeSecs,
        unsigned endTimeHours, unsigned endTimeMins, unsigned endTimeSecs);

    const char* getName() const;
    const Date& getDate() const;
    const Time& getStartTime() const;
    const Time& getEndTime() const;
private:
    char name[MAX_NAME_LENGTH];
    Date date;
    Time startTime;
    Time endTime;

    void setName(const char* name);
    void validateTimes();
};

