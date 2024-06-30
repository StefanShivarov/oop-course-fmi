#include "Criteria.h"
#include <fstream>

bool IncludeCriteria::operator()(int32_t n) const
{
    for (size_t i = 0; i < numbersCount; i++) {
        if (numbers[i] == n) {
            return true;
        }
    }
    return false;
}

bool ExcludeCriteria::operator()(int32_t n) const
{
    for (size_t i = 0; i < numbersCount; i++) {
        if (numbers[i] == n) {
            return false;
        }
    }
    return true;
}

void readCriteriaFromFile(const char* fileName, Criteria& cr)
{
    std::ifstream ifs(fileName);
    if (!ifs)
        return;
    cr.numbersCount = 0;
    while (true)
    {
        ifs >> cr.numbers[cr.numbersCount++];
        if (ifs.eof())
            return;
    }
}
