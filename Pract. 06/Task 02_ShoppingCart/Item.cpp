#include "Item.h"
#include <cstring>
#pragma warning (disable: 4996)

Item::Item(const char* name, double price, bool isAvailable): isAvailable(isAvailable) {

	setName(name);
	setPrice(price);
}

const char* Item::getName() const {
	return name;
}

bool Item::getIsAvailable() const {
	return isAvailable;
}

double Item::getPrice() const {
	return price;
}

void Item::setName(const char* name) {

	if (name == nullptr) {
		return;
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Item::setIsAvailable(bool available) {
	this->isAvailable = available;
}

void Item::setPrice(double price) {

	if (price < 0) {
		return;
	}

	this->price = price;
}

void Item::free() {

	delete[] name;
	name = nullptr;
	this->isAvailable = false;
	this->price = 0;
}

void Item::copyFrom(const Item& other) {

	setName(other.name);
	this->isAvailable = other.isAvailable;
	this->price = other.price;
}

Item::Item(const Item& other) {
	copyFrom(other);
}

Item& Item::operator=(const Item& other) {

	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Item::~Item() {
	free();
}


