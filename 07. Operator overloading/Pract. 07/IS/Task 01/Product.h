#pragma once
#include <iostream>

class Product {
private:
    char* name = nullptr;
    double price = 0.0;
    size_t quantity = 0;

    void free();
    void copyFrom(const Product& other);

public:
    Product() = default;
    Product(const char* name, double price, size_t quantity);

    Product(const Product& other);
    Product& operator=(const Product& other);
    ~Product();

    const char* getName() const;
    double getPrice() const;
    size_t getQuantity() const;

    bool setName(const char* newName);
    bool setPrice(double newPrice);
    bool setQuantity(size_t newQuantity);

    Product& operator++();
    Product operator++(int);
};

std::istream& operator>>(std::istream& is, Product& product);
std::ostream& operator<<(std::ostream& os, const Product& product);