#include <iostream>

namespace Days{
    const unsigned days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
}

struct Date {
    unsigned day = 1;
    unsigned month = 1;
    unsigned year = 1;
};

bool isLeapYear(unsigned year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned daysInMonth(unsigned month, unsigned year) {
    return (month == 2 && isLeapYear(year)) ? 29 : Days::days[month - 1];
}

Date getNextDay(const Date& date) {
    Date nextDay = date;
    nextDay.day++;

    if (nextDay.day > daysInMonth(nextDay.month, nextDay.year)) {
        nextDay.day = 1;
        nextDay.month++;

        if (nextDay.month > 12) {
            nextDay.month = 1;
            nextDay.year++;
        }
    }

    return nextDay;
}

int main() {

}
