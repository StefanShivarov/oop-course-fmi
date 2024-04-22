#pragma once
#include <iostream>
#include <fstream>

class MultiSet {
public:
    MultiSet(size_t maxNum, size_t bitsPerNum);

    MultiSet();
    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();

    size_t count(unsigned num) const;

    bool insert(unsigned num);
    bool remove(unsigned num);

    void printNumbers() const;
    void printBits() const;

    void deserializeFromBinaryFile(std::ifstream& ifs);
    void serializeToBinaryFile(std::ofstream& ofs) const;

    friend MultiSet unionOfMultiSets(const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet intersectionOfMultiSets(const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet differenceOfMultiSets(const MultiSet& subtractFrom, const MultiSet subtracted);
    friend MultiSet complementOfMultiSet(const MultiSet& ms);

private:
    unsigned char* data = nullptr;
    size_t bytesCount = 0;
    size_t bitsPerNumber = 0;
    size_t maxCountForNumber = 0;
    size_t maxNumber = 0;
    static const size_t DEFAULT_MAX_NUMBER;
    static const size_t BITS_IN_BYTE;

    void free();
    void copyFrom(const MultiSet& other);

    size_t getByteIndex(unsigned number) const;
    size_t getBitIndexInByte(unsigned number) const;

    void setCountForNumber(unsigned number, size_t newCount);

    static void getBinaryRepresentationOfByte(char* buff, unsigned char byte);
};
