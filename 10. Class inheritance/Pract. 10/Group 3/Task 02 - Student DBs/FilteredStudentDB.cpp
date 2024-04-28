#include "FilteredStudentDB.h"

static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocateByCount(unsigned count)
{
    return std::max(roundToPowerOfTwo(count + 1), 16u);
}

void FilteredStudentDB::filter(bool(*criteria)(const Student&))
{
    FilteredStudentDB filtered;
    for (size_t i = 0; i < studentsCount; i++) {
        if (criteria(students[i])) {
            filtered.add(students[i]);
        }
    }
    *this = filtered;
}

void FilteredStudentDB::limit(size_t n)
{
    if (n >= studentsCount) {
        return;
    }

    studentsCount = n;
    resize(dataToAllocateByCount(n));
}
