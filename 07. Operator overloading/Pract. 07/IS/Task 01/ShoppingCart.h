#pragma once
#include "Product.h"
#include <fstream>

constexpr size_t INITIAL_PRODUCTS_CAPACITY = 16;

class ShoppingCart {
private:
    Product* products = nullptr;
    size_t productsCount = 0;
    size_t productsCapacity = INITIAL_PRODUCTS_CAPACITY;

    void free();
    void copyFrom(const ShoppingCart& other);
    void resize(size_t newCapacity);
    void sortProducts(bool (*isLess)(const Product&, const Product&));

    size_t getProductIndexByName(const char* productName) const;
public:
    ShoppingCart();
    ShoppingCart(const ShoppingCart& other);
    ShoppingCart& operator=(const ShoppingCart& other);
    ~ShoppingCart();

    ShoppingCart& operator+=(const Product& product);
    ShoppingCart& operator-=(const char* productName);

    Product& operator[](size_t index);
    const Product& operator[](size_t index) const;

    size_t getProductsCount() const;
    bool isEmpty() const;

    double getTotalPrice() const;

    void sortProductsByName();
    void sortProductsByPrice();
    void sortProductsByQuantity();

    void saveToTextFile(std::ofstream& ofs) const;
};

