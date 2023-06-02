#include <iostream>
#include "ExpressionCalculator.h"

int main()
{
    
    ExpressionCalculator calc("(Sv(!S))");
    std::cout << calc.isTautology() << " " << calc.isContradiction() << std::endl;
}