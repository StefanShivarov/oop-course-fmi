#pragma once

class MultiSet {
private:
    size_t size = 0;
    unsigned char* data = nullptr;
    size_t bytesCount = 0;

    void copyFrom(const MultiSet& other);
    void free();
    unsigned char getMask(size_t destNum, size_t maskNum) const;
public:
    MultiSet() = default;
    explicit MultiSet(size_t n);

    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);

    ~MultiSet();

    size_t getSize() const;

    size_t count(size_t num) const;

    bool insert(size_t num);
    bool remove(size_t num);
    
    void print() const;

    void unionizeWith(const MultiSet& other);
    void intersectWith(const MultiSet& other);
};

MultiSet Union(const MultiSet& lhs, const MultiSet& rhs);
MultiSet intersection(const MultiSet& lhs, const MultiSet& rhs);
