#include "EventDuringJanuary2023.h"
#include <fstream>

namespace {
    constexpr unsigned FIRST_DAY = 7; // Sunday
    constexpr unsigned MAX_DAYS = 31;
    constexpr unsigned LAST_DAY_OF_WEEK = 7;
}

void EventDuringJanuary2023::addDay(unsigned day)
{
    if (day == 0 || day > MAX_DAYS) {
        throw std::invalid_argument("Invalid day!");
    }

    data |= (1 << day);
}

void EventDuringJanuary2023::removeDay(unsigned day)
{
    if (day == 0 || day > MAX_DAYS) {
        throw std::invalid_argument("Invalid day!");
    }

    data &= ~(1 << day);
}

bool EventDuringJanuary2023::hasEventOnDay(unsigned day) const
{
    if (day == 0 || day > MAX_DAYS) {
        throw std::invalid_argument("Invalid day!");
    }

    return data & (1 << day);
}

unsigned EventDuringJanuary2023::howManyOnDayOfWeek(unsigned dayOfWeek) const
{
    if (0 == dayOfWeek || dayOfWeek > LAST_DAY_OF_WEEK) {
        throw std::invalid_argument("Invalid day of week!");
    }
    unsigned counter = 0;
    unsigned offset = (FIRST_DAY == dayOfWeek) ? 0 : (dayOfWeek % FIRST_DAY);
    for (int32_t i = 1 + dayOfWeek; i <= MAX_DAYS; i += offset) {
        if (hasEventOnDay(i)) {
            counter++;
        }
    }
    return counter;
}

void EventDuringJanuary2023::saveToFile(std::ofstream& ofs)
{
    ofs.write((const char*)&data, sizeof(int32_t));
}

void EventDuringJanuary2023::readFromFile(std::ifstream& ifs)
{
    ifs.read((char*)&data, sizeof(int32_t));
}

EventDuringJanuary2023 Union(const EventDuringJanuary2023& lhs, const EventDuringJanuary2023& rhs)
{
    EventDuringJanuary2023 result;
    result.data = lhs.data | rhs.data;
    return result;
}

EventDuringJanuary2023 Intersection(const EventDuringJanuary2023& lhs, const EventDuringJanuary2023& rhs)
{
    EventDuringJanuary2023 result;
    result.data = lhs.data & rhs.data;
    return result;
}
