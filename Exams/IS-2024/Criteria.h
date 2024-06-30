#pragma once
#include <iostream>

constexpr size_t MAX_NUMBERS_COUNT = 32;

class Criteria
{
public:
    virtual bool operator()(int32_t n) const = 0;
    virtual ~Criteria() = default;

    friend void readCriteriaFromFile(const char* fileName, Criteria& cr);
protected:
    int32_t numbers[MAX_NUMBERS_COUNT];
    size_t numbersCount = 0;
};

class IncludeCriteria : public Criteria {
public:
    bool operator()(int32_t n) const override;
};

class ExcludeCriteria : public Criteria {
public:
    bool operator()(int32_t n) const override;
};
