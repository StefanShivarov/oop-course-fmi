#include <iostream>
#include "PredicateSet.hpp"
#include "UnionSet.hpp"
#include "Vector.hpp"
#include "SetBase.hpp"
#include "IntersectionSet.hpp"

bool isEvenNumber(const int& num) {
    return num % 2 == 0;
}

int main()
{
    PredicateSet<int> predicateSet(isEvenNumber);

    std::cout << predicateSet.accepts(1) << std::endl;
    std::cout << predicateSet.accepts(2) << std::endl;

    predicateSet.insert(2);
    try {
        predicateSet.insert(5); // throws error, because isEvenNumber(5) == false
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    predicateSet.insert(4);
    predicateSet.printAllElements();

    UnionSet<int> u1, u2, u3;

    u1.insert(1);
    u1.insert(2);
    u1.insert(10);
    u1.insert(100);

    u2.insert(10);
    u2.insert(100);
    u2.insert(20);

    u3.insert(100);
    u3.insert(10);
    u3.insert(200);

    Vector<SetBase<int>*> sets;
    sets.pushBack(&u1);
    sets.pushBack(&u2);
    sets.pushBack(&u3);

    UnionSet<int> result(sets);
    result.printAllElements();// 1 2 10 20 100 200

    IntersectionSet<int> intersectionSet(sets);
    intersectionSet.printAllElements();// 10 100
}