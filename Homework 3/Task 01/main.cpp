#include <iostream>
#include "PredicateSet.hpp"


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
    
}