#include <iostream>
#include <fstream>

namespace Constants {
    const int MAX_NAME_LENGTH = 100;
    const int MAX_PRODUCTS_COUNT = 200;
}

unsigned getFileSize(std::ifstream& ifs) {
    size_t currentPos = ifs.tellg();
    ifs.seekg(0, std::ios::end);
    size_t symbolsCount = ifs.tellg();
    ifs.seekg(currentPos);
    ifs.clear();

    return symbolsCount;
}

enum class Category {
    ELECTRONICS,
    CLOTHING,
    BOOKS,
    FOOD,
    BEAUTY,
    OTHER
};

struct Product {
    char name[Constants::MAX_NAME_LENGTH]{};
    unsigned quantity = 0;
    double price = 0.0;
    Category category = Category::OTHER;
    char supplier[Constants::MAX_NAME_LENGTH]{};
};

void printProduct(const Product& product) {
    std::cout << product.name << ' '
        << product.quantity << ' '
        << product.price << ' '
        << product.supplier;
}

Product deserializeProductFromBinaryFile(std::ifstream& ifs) {
    Product product;
    ifs.read((char*)&product, sizeof(Product));
    return product;
}

void serializeProductToBinaryFile(std::ofstream& ofs, const Product& product) {
    ofs.write((const char*)&product, sizeof(Product));
}

struct ProductDatabase {
    Product* products = nullptr;
    unsigned productsCount = 0;
};

void freeProductDatabase(ProductDatabase& productDatabase) {
    delete[] productDatabase.products;
    productDatabase.products = nullptr;
    productDatabase.productsCount = 0;
}

void printAllProducts(const ProductDatabase& productDatabase) {
    for (unsigned i = 0; i < productDatabase.productsCount; i++) {
        printProduct(productDatabase.products[i]);
        std::cout << std::endl;
    }
}

void saveProductsToBinaryFile(std::ofstream& ofs, const ProductDatabase& productDatabase) {
    for (unsigned i = 0; i < productDatabase.productsCount; i++) {
        serializeProductToBinaryFile(ofs, productDatabase.products[i]);
    }
    // because there is no dynamic memory in the struct, this will also work:
    // ofs.write((const char*)&productDatabase.products, sizeof(Product) * productDatabase.productsCount);
}

ProductDatabase loadProductsFromBinaryFile(std::ifstream& ifs) {
    ProductDatabase productDatabase;
    productDatabase.productsCount = getFileSize(ifs) / sizeof(Product);
    productDatabase.products = new Product[productDatabase.productsCount];

    for (unsigned i = 0; i < productDatabase.productsCount; i++) {
        productDatabase.products[i] = deserializeProductFromBinaryFile(ifs);
    }

    return productDatabase;
}

int getProductIndexByName(const char* productName, const ProductDatabase& productDatabase) {
    for (unsigned i = 0; i < productDatabase.productsCount; i++) {
        if (strcmp(productName, productDatabase.products[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

const Product& getProductByName(const char* productName, const ProductDatabase& productDatabase) {
    int index = getProductIndexByName(productName, productDatabase);
    if (index < 0) {
        return {};
    }

    return productDatabase.products[index];
}

void writeProductsByCategoryToBinaryFile(const char* fileName, const ProductDatabase& productDatabase, Category category) {
    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cerr << "Failed to open file " << fileName << '!';
        return;
    }

    for (unsigned i = 0; i < productDatabase.productsCount; i++) {
        if (productDatabase.products[i].category == category) {
            serializeProductToBinaryFile(ofs, productDatabase.products[i]);
        }
    }
}

void changeProductQuantity(std::ofstream& ofs, Product& product, ProductDatabase& productDatabase, unsigned updatedQuantity) {
    product.quantity = updatedQuantity;
    int productIndex = getProductIndexByName(product.name, productDatabase);
    ofs.seekp(productIndex * sizeof(Product));
    ofs.write((const char*)&product, sizeof(Product));
}

int main() {

}
