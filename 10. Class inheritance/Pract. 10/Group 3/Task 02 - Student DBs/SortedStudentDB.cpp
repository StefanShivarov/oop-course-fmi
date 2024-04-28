#include "SortedStudentDB.h"

void SortedStudentDB::sortBy(bool (*sortingCriteria)(const Student&, const Student&))
{
    for (size_t i = 0; i < studentsCount - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < studentsCount; j++) {
            if (sortingCriteria(students[j], students[minIndex])) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(students[i], students[minIndex]);
        }
    }
}
