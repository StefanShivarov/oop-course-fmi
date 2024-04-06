#include "Product.h"
#pragma warning (disable: 4996)

void Product::free() {
    delete[] name;
    name = nullptr;
    quantity = 0;
    price = 0.0;
}

void Product::copyFrom(const Product& other) {
    quantity = other.quantity;
    price = other.price;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

Product::Product(const char* name, double price, size_t quantity) {
    setName(name);
    setPrice(price);
    setQuantity(quantity);
}

Product::Product(const Product& other) {
    copyFrom(other);
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Product::~Product() {
    free();
}

const char* Product::getName() const {
    return name;
}

bool Product::setName(const char* newName) {
    if (!newName) {
        return false;
    }

    delete[] name;
    name = new char[strlen(newName) + 1];
    strcpy(name, newName);
    return true;
}

double Product::getPrice() const {
    return price;
}

bool Product::setPrice(double newPrice) {
    if (newPrice < 0) {
        return false;
    }

    price = newPrice;
    return true;
}

size_t Product::getQuantity() const {
    return quantity;
}

bool Product::setQuantity(size_t newQuantity) {
    // can include some validations here...
    quantity = newQuantity;
    return true;
}

Product& Product::operator++() {
    ++quantity;
    return *this;
}

Product Product::operator++(int) {
    Product copy(*this);
    ++quantity;
    return copy;
}

std::istream& operator>>(std::istream& is, Product& p) {
    char buff[1024];
    is >> buff;
    p.setName(buff);

    double price;
    is >> price;
    p.setPrice(price);

    size_t quantity;
    is >> quantity;
    p.setQuantity(quantity);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Product& p) {
    return os << p.getName() << ' ' << p.getPrice() << ' ' << p.getQuantity();
}
