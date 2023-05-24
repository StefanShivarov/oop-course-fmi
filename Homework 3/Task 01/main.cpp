#include <iostream>
#include <fstream>
#include "PredicateSet.hpp"
#include "UnionSet.hpp"
#include "Vector.hpp"
#include "SetBase.hpp"
#include "IntersectionSet.hpp"
#include "MyString.h"

const short MAX_FILENAME_LENGTH = 1024;
const char FIRST_FILENAME[] = "set.dat";

MyString getStringFromFile(std::ifstream& ifs)
{
    MyString str;
    char character;
    while (ifs.get(character) && character != '\0')
    {
        str += (char*)character;
    }
    return str;
}

bool dividesNoneOfNumbers(const Vector<uint32_t>& numbers,const uint32_t& number)
{
    const size_t numbersSize = numbers.getSize();
    for (size_t i = 0; i < numbersSize; i++) {
        if (number % numbers[i] == 0) {
            return false;
        }
    }
    return true;
}

bool dividesExactlyOneOfNumbers(const Vector<uint32_t>& numbers, const uint32_t& number)
{
    const size_t numbersSize = numbers.getSize();
    size_t counter = 0;
    for (size_t i = 0; i < numbersSize; i++) {
        if (number % numbers[i] == 0) {
            counter++;
        }
    }
    
    return counter == 1;
}

SetBase<uint32_t>* createSetFromFile(std::ifstream& ifs) {

    if (!ifs.is_open()) {
        throw std::exception("Error! File not found.");
    }

    uint16_t N, T;
    ifs.read((char*) N, sizeof(N));
    ifs.read((char*) T, sizeof(T));
    
       
    if (T == 0) {

        Vector<uint32_t> numbers(N);
        ifs.read((char*)(numbers.getData()), N * sizeof(uint32_t));
        UnionSet<uint32_t>* set = new UnionSet<uint32_t>();
        for (size_t i = 0; i < N; i++) {
            set->insert(numbers[i]);
        }
        return set;
    }
    else if (T == 1) {

        Vector<uint32_t> numbers(N);
        ifs.read((char*)(numbers.getData()), N * sizeof(uint32_t));

        PredicateSet<uint32_t>* set = new PredicateSet<uint32_t>(dividesNoneOfNumbers);

        return set;
    
    }
    else if (T == 2) {
    
        Vector<uint32_t> numbers(N);
        ifs.read((char*)(numbers.getData()), N * sizeof(uint32_t));

        PredicateSet<uint32_t>* set = new PredicateSet<uint32_t>(dividesExactlyOneOfNumbers);

        return set;
    }
    else if (T == 3) {

        Vector<MyString> filePaths(N);
        for (size_t i = 0; i < N; i++)
        {
            filePaths[i] = getStringFromFile(ifs);
        }

        Vector<SetBase<uint32_t>*> sets;
        for (size_t i = 0; i < N; i++)
        {
            std::ifstream otherFile(filePaths[i].c_str(), std::ios::binary);
            if (!otherFile.is_open())
            {
                throw std::exception("Error! Can't open other file!");
            }
            SetBase<uint32_t>* set = createSetFromFile(otherFile);
            sets.pushBack(set);
            otherFile.close();
        }
        return new UnionSet<uint32_t>(sets);
    
    }
    else if (T == 4) {
    
        Vector<MyString> filePaths(N);
        for (size_t i = 0; i < N; i++)
        {
            filePaths[i] = getStringFromFile(ifs);
        }

        Vector<SetBase<uint32_t>*> sets;
        for (size_t i = 0; i < N; i++)
        {
            std::ifstream otherFile(filePaths[i].c_str(), std::ios::binary);
            if (!otherFile.is_open())
            {
                throw std::exception("Error! Can't open other file!");
            }
            SetBase<uint32_t>* set = createSetFromFile(otherFile);
            sets.pushBack(set);
            otherFile.close();
        }
        return new IntersectionSet<uint32_t>(sets);
    }
    else {
        throw std::length_error("Invalid file format specified!");

    }
}

void printElementsBetween(const SetBase<uint32_t>* set, unsigned int a, unsigned int b) {

    const size_t createdSetSize = set->size();
    for (size_t i = 0; i < createdSetSize; i++) {
        uint32_t element = set->getAtIndex(i);
        if (element >= a && element <= b) {
            std::cout << element << " ";
        }
    }
    std::cout << std::endl;

}

void generateSetElements(const SetBase<uint32_t>* set) {

    std::cout << "Generating set elements: " << std::endl;
    
    size_t index = 0;
    while (!set->isEmpty()) {

        std::cout << "Print next? Y/N" << std::endl;
        char symbol;
        std::cin >> symbol;
        switch (symbol) {

        case 'Y':
            std::cout << set->getAtIndex(index++) << std::endl;
            break;

        case 'N':
            std::cout << "Ending program...";
            break;

        default:
            throw std::logic_error("Error! Invalid command!");
        }
    }
}

int main()
{
    unsigned int a, b;
    std::cin >> a >> b;
    try {
        std::ifstream ifs(FIRST_FILENAME, std::ios::binary);
        SetBase<uint32_t>* createdSet = createSetFromFile(ifs);

        printElementsBetween(createdSet, a, b);

        generateSetElements(createdSet);

        delete createdSet;
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}