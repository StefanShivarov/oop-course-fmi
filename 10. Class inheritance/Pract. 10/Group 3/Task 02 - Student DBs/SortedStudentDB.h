#pragma once
#include "StudentDB.h"

class SortedStudentDB : public StudentDB
{
public:
    void sortBy(bool (*sortingCriteria)(const Student&, const Student&));
};
