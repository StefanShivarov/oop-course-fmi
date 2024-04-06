#include "ShoppingCart.h"

void ShoppingCart::free() {
    delete[] products;
    products = nullptr;
    productsCount = productsCapacity = 0;
}

void ShoppingCart::copyFrom(const ShoppingCart& other) {
    productsCount = other.productsCount;
    productsCapacity = other.productsCapacity;
    products = new Product[productsCapacity];
    for (size_t i = 0; i < other.productsCount; i++) {
        products[i] = other.products[i];
    }
}

void ShoppingCart::resize(size_t newCapacity) {
    Product* resizedProducts = new Product[newCapacity];
    for (size_t i = 0; i < productsCount; i++) {
        resizedProducts[i] = products[i];
    }
    delete[] products;
    products = resizedProducts;
    productsCapacity = newCapacity;
}

void ShoppingCart::sortProducts(bool (*isLess)(const Product&, const Product&)) {
    for (size_t i = 0; i < productsCount - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < productsCount; j++) {
            if (isLess(products[j], products[minIndex])) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(products[i], products[minIndex]);
        }
    }
}

size_t ShoppingCart::getProductIndexByName(const char* productName) const {
    for (size_t i = 0; i < productsCount; i++) {
        if (strcmp(products[i].getName(), productName) == 0) {
            return i;
        }
    }
    return productsCount;
}

ShoppingCart::ShoppingCart() : productsCapacity(INITIAL_PRODUCTS_CAPACITY), productsCount(0) {
    products = new Product[productsCapacity];
}

ShoppingCart::ShoppingCart(const ShoppingCart& other) {
    copyFrom(other);
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ShoppingCart::~ShoppingCart() {
    free();
}

ShoppingCart& ShoppingCart::operator+=(const Product& product) {
    if (productsCount >= productsCapacity) {
        resize(productsCapacity * 2);
    }

    products[productsCount++] = product;
    return *this;
}

ShoppingCart& ShoppingCart::operator-=(const char* productName) {
    if (!productName) {
        return *this;
    }

    size_t productIndex = getProductIndexByName(productName);
    for (size_t i = productIndex; i < productsCount - 1; i++) {
        products[i] = products[i + 1];
    }

    productsCount--;
    return *this;
}

Product& ShoppingCart::operator[](size_t index) {
    return products[index];
}

const Product& ShoppingCart::operator[](size_t index) const {
    return products[index];
}

size_t ShoppingCart::getProductsCount() const {
    return productsCount;
}

bool ShoppingCart::isEmpty() const {
    return productsCount == 0;
}

double ShoppingCart::getTotalPrice() const {
    double sum = 0.0;
    for (size_t i = 0; i < productsCount; i++) {
        sum += products[i].getPrice();
    }
    return sum;
}

void ShoppingCart::sortProductsByName() {
    sortProducts([](const Product& p1, const Product& p2) { return strcmp(p1.getName(), p2.getName()) < 0; });
}

void ShoppingCart::sortProductsByPrice() {
    sortProducts([](const Product& p1, const Product& p2) { return p1.getPrice() < p2.getPrice(); });
}

void ShoppingCart::sortProductsByQuantity() {
    sortProducts([](const Product& p1, const Product& p2) { return p1.getQuantity() < p2.getQuantity(); });
}

void ShoppingCart::saveToTextFile(std::ofstream& ofs) const {
    ofs << productsCount << '\n';
    for (size_t i = 0; i < productsCount; i++) {
        ofs << products[i] << '\n';
    }
}
