#include <iostream>
#include <fstream>
#include "Set.h"
#include "SetByCriteria.h"
#include "SetIntersection.h"

void printSetInInterval(const Set& set, unsigned begin, unsigned end)
{
    for (unsigned i = begin; i < end; i++)
    {
        if (set.accepts(i))
            std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    
    IncludeCriteria includeCrit;
    readCriteriaFromFile("include.txt", includeCrit);

    ExcludeCriteria excludeCrit;
    readCriteriaFromFile("exclude.txt", excludeCrit);

    SetByCriteria<IncludeCriteria> s1(includeCrit);
    SetByCriteria<ExcludeCriteria> s2(excludeCrit);
    SetByCriteria<bool(*)(int32_t)> s3([](int32_t x) { return x % 2 == 0; });

    const Set** sets = new const Set * [3] {&s1, & s2, & s3};
    SetIntersection s4(sets, 3);

    printSetInInterval(s1, 0, 10);
    printSetInInterval(s2, 0, 10);
    printSetInInterval(s3, 0, 10);
    printSetInInterval(s4, 0, 10);

    delete[] sets;
}
