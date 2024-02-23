#include "ShoppingCart.h"
#include <iostream>
#include <cstring>
#include <fstream>

void ShoppingCart::free() {

	delete[] items;
	items = nullptr;
	itemsAmount = 0;
	itemsCapacity = 0;
}

void ShoppingCart::copyFrom(const ShoppingCart& other) {

	if (other.items == nullptr) {
		return;
	}

	items = new Item[other.itemsCapacity];
	for (int i = 0; i < other.itemsAmount; i++) {
		items[i] = other.items[i];
	}

	this->itemsCapacity = other.itemsCapacity;
	this->itemsAmount = other.itemsAmount;

}

void ShoppingCart::resize() {

	itemsCapacity *= 2;
	Item* resized = new Item[itemsCapacity];
	for (int i = 0; i < itemsAmount; i++) {
		resized[i] = items[i];
	}
	delete[] items;
	items = resized;
}

int ShoppingCart::find(const char* name) const {

	if (name == nullptr) {
		return -1;
	}

	for (int i = 0; i < itemsAmount; i++) {
		if (strcmp(items[i].getName(), name) == 0) {
			return i;
		}
	}

	return -1;
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

bool ShoppingCart::exists(const char* name) const {

	return find(name) != -1;
}

bool ShoppingCart::isEmpty() const {
	return itemsAmount == 0;
}

size_t ShoppingCart::itemsCount() const {
	return itemsAmount;
}

double ShoppingCart::getPriceOf(const char* name) const {

	size_t index = find(name);

	if (index == -1) {
		return 0;
	}
	else {
		return items[index].getPrice();
	}
}

double ShoppingCart::totalPrice() const {

	double total = 0;

	for (int i = 0; i < itemsAmount; i++) {
		total += items[i].getPrice();
	}

	return total;
}

bool ShoppingCart::addItem(const Item& item) {

	if (find(item.getName()) == -1) {

		if (itemsAmount == itemsCapacity) {
			resize();
		}

		items[itemsAmount++] = item;
		return true;
	}
	return false;
}


bool ShoppingCart::removeItem(const char* itemName) {

	int removeIndex = find(itemName);

	if (removeIndex == -1) {
		return false;
	}

	for (int i = removeIndex; i < itemsAmount - 1; i++) {
		items[i] = items[i + 1];
	}
	itemsAmount--;
	return true;
}

void ShoppingCart::sortByName() {

	for (int i = 0; i < itemsAmount - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < itemsAmount; j++) {
			if (strcmp(items[minIndex].getName(), items[j].getName()) > 0) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			Item temp(items[minIndex]);
			items[minIndex] = items[i];
			items[i] = temp;
		}
	}
}

void ShoppingCart::save(const char* filePath) const {

	std::ofstream ofs(filePath);

	if (!ofs.is_open()) {
		std::cout << "Error! Can't write to file!" << std::endl;
	}

	for (int i = 0; i < itemsAmount; i++) {

		ofs << items[i].getName() << ", " << items[i].getPrice() << ", " << items[i].getIsAvailable() << std::endl;
	}

	ofs.close();
}