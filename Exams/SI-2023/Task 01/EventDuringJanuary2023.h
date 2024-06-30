#pragma once
#include <iostream>
class EventDuringJanuary2023
{
public:
    void addDay(unsigned day);
    void removeDay(unsigned day);
    bool hasEventOnDay(unsigned day) const;
    unsigned howManyOnDayOfWeek(unsigned dayOfWeek) const;

    void saveToFile(std::ofstream& ofs);
    void readFromFile(std::ifstream& ifs);

    friend EventDuringJanuary2023 Union(const EventDuringJanuary2023& lhs, const EventDuringJanuary2023& rhs);
    friend EventDuringJanuary2023 Intersection(const EventDuringJanuary2023& lhs, const EventDuringJanuary2023& rhs);

private:
    int32_t data;
};
