#include <iostream>
#include "TemplateSortingFunctions.hpp"

int main()
{
    
    char symbolsArr[] = {'d', 'a', 'c', 'b'};
    int numbersArr[] = { 5, 3, 7, 9, -1, 6 };

    sort(symbolsArr, 4);
    sort(numbersArr, 6);

    printArr(symbolsArr, 4); // a b c d
    printArr(numbersArr, 6); // -1 3 5 6 7 9
}
