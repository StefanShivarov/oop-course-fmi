#include <iostream>
#include "PairOfOptionals.hpp"

int main()
{
    PairOfOptionals<int> pair1;
    PairOfOptionals<int> pair2(4, 5);

    std::cout << pair1.firstHasValue() << std::endl; //0
    
    pair1.setFirst(4);
    pair1.setSecond(2);

    std::cout << pair1.firstHasValue() << std::endl; //1
    std::cout << pair1.secondHasValue() << std::endl; //1

    std::cout << (pair1 == pair2) << std::endl; //0
    std::cout << (pair1 != pair2) << std::endl; //1

    pair1.clearSecond();

    try {
        std::cout << pair1.getSecond() << std::endl;
    }
    catch (std::logic_error e) {
        std::cout << e.what() << std::endl; // Second optional has no value!
    }
    
    std::cout << pair1.secondHasValue() << std::endl; //0

    pair1.setSecond(5);

    std::cout << pair1.getFirst() << " " << pair1.getSecond() << std::endl; //4 5
    
    std::cout << (pair1 == pair2) << std::endl; //1
    std::cout << (pair1 != pair2) << std::endl; //0    
}