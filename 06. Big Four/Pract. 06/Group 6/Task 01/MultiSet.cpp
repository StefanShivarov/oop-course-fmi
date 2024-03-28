#include <iostream>
#include "MultiSet.h"

constexpr int BUCKETS_IN_BYTE = 4;
constexpr int BITS_IN_BYTE = 8;
constexpr int MAX_COUNT_FOR_NUMBER = 3;

void MultiSet::copyFrom(const MultiSet& other) {
    size = other.size;
    bytesCount = other.bytesCount;
    data = new unsigned char[other.bytesCount] {};
    for (size_t i = 0; i < other.bytesCount; i++) {
        data[i] = other.data[i];
    }
}

void MultiSet::free() {
    delete[] data;
    size = bytesCount = 0;
}

unsigned char MultiSet::getMask(size_t destNum, size_t maskNum) const {
    size_t bucketIndexInByte = destNum % BUCKETS_IN_BYTE;
    size_t offset = (BUCKETS_IN_BYTE - bucketIndexInByte - 1) * 2;
    return maskNum << offset;
}

MultiSet::MultiSet(size_t n) : size(n), bytesCount((n * 2 + 7) / BITS_IN_BYTE) {
    data = new unsigned char[bytesCount] {};
}

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

size_t MultiSet::getSize() const {
    return size;
}

size_t MultiSet::count(size_t num) const {
    if (num >= size) {
        return 0;
    }

    size_t dataIndex = num / BUCKETS_IN_BYTE;
    size_t offset = (BUCKETS_IN_BYTE - (num % BUCKETS_IN_BYTE) - 1) * 2;

    return (data[dataIndex] >> offset) & MAX_COUNT_FOR_NUMBER;
}

bool MultiSet::insert(size_t num) {
    size_t countOfNum = count(num);
    if (countOfNum == MAX_COUNT_FOR_NUMBER) {
        return false;
    }

    size_t dataIndex = num / BUCKETS_IN_BYTE;
    if (countOfNum == 1) {
        data[dataIndex] ^= getMask(num, MAX_COUNT_FOR_NUMBER);
    }
    else {
        data[dataIndex] |= getMask(num, countOfNum + 1);
    }
    return true;
}

bool MultiSet::remove(size_t num) {
    size_t countOfNum = count(num);
    if (countOfNum == 0) {
        return false;
    }

    size_t dataIndex = num / BUCKETS_IN_BYTE;
    if (countOfNum == 2) {
        data[dataIndex] ^= getMask(num, MAX_COUNT_FOR_NUMBER);
    }
    else {
        data[dataIndex] ^= getMask(num, 1);
    }
    return true;
}

void MultiSet::print() const {
    for (size_t i = 0; i < size; i++) {
        size_t countOfNum = count(i);
        if (countOfNum == 0) {
            continue;
        }

        for (size_t j = 0; j < countOfNum; j++) {
            std::cout << i << ' ';
        }
    }
}

void MultiSet::unionizeWith(const MultiSet& other) {
    size_t maxSize = std::max(size, other.size);
    MultiSet unionized(maxSize);

    for (size_t i = 0; i < maxSize; i++) {
        size_t maxCount = std::max(count(i), other.count(i));
        for (size_t j = 0; j < maxCount; j++) {
            unionized.insert(i);
        }
    }

    *this = unionized;
}

void MultiSet::intersectWith(const MultiSet& other) {
    size_t minSize = std::min(size, other.size);
    MultiSet intersected(minSize);
    
    for (size_t i = 0; i < minSize; i++) {
        size_t minCount = std::min(count(i), other.count(i));
        for (size_t j = 0; j < minCount; j++) {
            intersected.insert(i);
        }
    }

    *this = intersected;
}

MultiSet Union(const MultiSet& lhs, const MultiSet& rhs) {
    MultiSet unionMultiSet = lhs;
    unionMultiSet.unionizeWith(rhs);
    return unionMultiSet;
}

MultiSet intersection(const MultiSet& lhs, const MultiSet& rhs) {
    MultiSet intersectionMultiSet = lhs;
    intersectionMultiSet.intersectWith(rhs);
    return intersectionMultiSet;
}
