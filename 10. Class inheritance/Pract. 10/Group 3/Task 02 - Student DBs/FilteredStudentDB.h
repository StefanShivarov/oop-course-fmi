#pragma once
#include "StudentDB.h"

class FilteredStudentDB : public StudentDB
{
public:
    void filter(bool (*criteria)(const Student&));
    void limit(size_t n);
};
