#include "MultiSet.h"

const size_t MultiSet::DEFAULT_MAX_NUMBER = 100;
const size_t MultiSet::BITS_IN_BYTE = 8;

void MultiSet::free() {
    delete[] data;
    data = nullptr;
    bytesCount = bitsPerNumber = maxCountForNumber = maxNumber = 0;
}

void MultiSet::copyFrom(const MultiSet& other) {
    bytesCount = other.bytesCount;
    bitsPerNumber = other.bitsPerNumber;
    maxCountForNumber = other.maxCountForNumber;
    maxNumber = other.maxNumber;
    data = new unsigned char[bytesCount];
    for (size_t i = 0; i < bytesCount; i++) {
        data[i] = other.data[i];
    }
}

MultiSet::MultiSet(size_t maxNum, size_t bitsPerNum) : maxNumber(maxNum), bitsPerNumber(bitsPerNum) {
    if (bitsPerNumber < 1) {
        bitsPerNumber = 1;
    }
    else if (bitsPerNumber > BITS_IN_BYTE) {
        bitsPerNumber = BITS_IN_BYTE;
    }

    maxCountForNumber = (1 << bitsPerNum) - 1;
    size_t bitsNeeded = (maxNum + 1) * bitsPerNum;
    bytesCount = bitsNeeded / BITS_IN_BYTE + (bitsNeeded % BITS_IN_BYTE != 0);
    data = new unsigned char[bytesCount] {};
}

MultiSet::MultiSet() : MultiSet(DEFAULT_MAX_NUMBER, 1) {}

MultiSet::MultiSet(const MultiSet& other) {
    copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MultiSet::~MultiSet() {
    free();
}

size_t MultiSet::getByteIndex(unsigned number) const {
    return (number * bitsPerNumber) / BITS_IN_BYTE;
}

size_t MultiSet::getBitIndexInByte(unsigned number) const {
    return (number * bitsPerNumber) % BITS_IN_BYTE;
}

size_t MultiSet::count(unsigned number) const {
    if (number > maxNumber) {
        return 0;
    }

    size_t byteIndex = getByteIndex(number);
    size_t bitIndex = getBitIndexInByte(number);

    size_t bitsInFirstByte = std::min(bitsPerNumber, BITS_IN_BYTE - bitIndex);

    unsigned char mask = (1 << bitsPerNumber) - 1;
    if (bitsInFirstByte == bitsPerNumber) {
        size_t bitsFromEnd = BITS_IN_BYTE - bitIndex - bitsPerNumber;
        unsigned char shiftedBucket = data[byteIndex] >> bitsFromEnd;
        return shiftedBucket & mask;
    }

    size_t bitsInSecondByte = bitsPerNumber - bitsInFirstByte;
    unsigned char firstBytePart = (data[byteIndex] << bitsInSecondByte) & mask;
    unsigned char secondBytePart = (data[byteIndex + 1] >> (BITS_IN_BYTE - bitsInSecondByte)) & mask;

    return firstBytePart | secondBytePart;
}

void MultiSet::setCountForNumber(unsigned number, size_t newCount) {
    size_t byteIndex = getByteIndex(number);
    size_t bitIndex = getBitIndexInByte(number);
    
    newCount = std::min(newCount, maxCountForNumber);

    size_t bitsInFirstByte = std::min(bitsPerNumber, BITS_IN_BYTE - bitIndex);

    if (bitsInFirstByte == bitsPerNumber) {
        size_t bitsFromEnd = BITS_IN_BYTE - bitIndex - bitsPerNumber;
        data[byteIndex] &= ~(((1 << bitsPerNumber) - 1) << bitsFromEnd);
        data[byteIndex] |= (newCount << bitsFromEnd);
    }
    else {
        size_t bitsInSecondByte = bitsPerNumber - bitsInFirstByte;

        data[byteIndex] &= ~((1 << bitsInFirstByte) - 1);
        data[byteIndex + 1] &= ((1 << (BITS_IN_BYTE - bitsInSecondByte)) - 1);

        if (newCount > 0) {
            data[byteIndex] |= (newCount >> bitsInSecondByte);
            data[byteIndex + 1] |= (newCount << (BITS_IN_BYTE - bitsInSecondByte));
        }
    }
}

bool MultiSet::insert(unsigned number) {
    size_t currentCount = count(number);
    if (currentCount == maxCountForNumber || number > maxNumber) {
        return false;
    }

    setCountForNumber(number, currentCount + 1);
    return true;
}

bool MultiSet::remove(unsigned number) {
    size_t currentCount = count(number);
    if (currentCount == 0 || number > maxNumber) {
        return false;
    }

    setCountForNumber(number, currentCount - 1);
    return true;
}

void MultiSet::printNumbers() const {
    std::cout << "{ ";
    bool firstNumPrinted = false;
    for (size_t i = 0; i <= maxNumber; i++) {
        size_t currentCount = count(i);
        for (size_t j = 0; j < currentCount; j++) {
            if (firstNumPrinted) {
                std::cout << ", ";
            }
            std::cout << i;
            firstNumPrinted = true;
        }
    }
    std::cout << " }";
}

void MultiSet::getBinaryRepresentationOfByte(char* buff, unsigned char byte) {
    for (size_t i = 0; i < BITS_IN_BYTE; i++) {
        buff[i] = (byte & (1 << (BITS_IN_BYTE - 1 - i))) ? '1' : '0';
    }
    buff[BITS_IN_BYTE] = '\0';
}

void MultiSet::printBits() const {
    char byteBuff[BITS_IN_BYTE + 1];
    for (int i = bytesCount - 1; i >= 0; i--) {
        getBinaryRepresentationOfByte(byteBuff, data[i]);
        std::cout << byteBuff << ' ';
    }
}

void MultiSet::deserializeFromBinaryFile(std::ifstream& ifs) {
    ifs.read((char*)&maxNumber, sizeof(maxNumber));
    ifs.read((char*)&bitsPerNumber, sizeof(bitsPerNumber));
    ifs.read((char*)&bytesCount, sizeof(bytesCount));

    delete[] data;
    data = new unsigned char[bytesCount];
    maxCountForNumber = (1 << bitsPerNumber) - 1;

    ifs.read((char*)data, bytesCount);
}

void MultiSet::serializeToBinaryFile(std::ofstream& ofs) const {
    ofs.write((const char*)&maxNumber, sizeof(maxNumber));
    ofs.write((const char*)&bitsPerNumber, sizeof(bitsPerNumber));
    ofs.write((const char*)&bytesCount, sizeof(bytesCount));
    ofs.write((const char*)data, bytesCount);
}

MultiSet unionOfMultiSets(const MultiSet& lhs, const MultiSet& rhs) {
    MultiSet unionMultiSet(std::max(lhs.maxNumber, rhs.maxNumber), std::max(lhs.bitsPerNumber, rhs.bitsPerNumber));
    for (size_t i = 0; i <= unionMultiSet.maxNumber; i++) {
        unionMultiSet.setCountForNumber(i, lhs.count(i) + rhs.count(i));
    }
    return unionMultiSet;
}

MultiSet intersectionOfMultiSets(const MultiSet& lhs, const MultiSet& rhs) {
    MultiSet intersection(std::min(lhs.maxNumber, rhs.maxNumber), std::min(lhs.bitsPerNumber, rhs.bitsPerNumber));
    for (size_t i = 0; i <= intersection.maxNumber; i++) {
        intersection.setCountForNumber(i, std::min(lhs.count(i), rhs.count(i)));
    }
    return intersection;
}

MultiSet differenceOfMultiSets(const MultiSet& subtractFrom, const MultiSet subtracted) {
    MultiSet diff(subtractFrom);
    for (size_t i = 0; i <= diff.maxNumber; i++) {
        size_t leftCount = subtractFrom.count(i);
        size_t rightCount = subtracted.count(i);
        if (leftCount <= rightCount) {
            diff.setCountForNumber(i, 0);
        }
        else {
            diff.setCountForNumber(i, leftCount - rightCount);
        }
    }
    return diff;
}

MultiSet complementOfMultiSet(const MultiSet& ms) {
    MultiSet complement(ms.maxNumber, ms.bitsPerNumber);
    for (size_t i = 0; i <= complement.maxNumber; i++) {
        complement.setCountForNumber(i, complement.maxCountForNumber - ms.count(i));
    }
    return complement;
}
