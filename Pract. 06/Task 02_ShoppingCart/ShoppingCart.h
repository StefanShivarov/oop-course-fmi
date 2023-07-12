#pragma once
#include "Item.h"

class ShoppingCart
{

	Item* items = nullptr;
	size_t itemsAmount = 0;
	size_t itemsCapacity = 0;

public:

	ShoppingCart() = default;
	ShoppingCart(const ShoppingCart& other);
	ShoppingCart& operator=(const ShoppingCart& other);
	~ShoppingCart();

	bool addItem(const Item& item);
	bool removeItem(const char* itemName);
	size_t itemsCount() const;
	bool exists(const char* itemName) const;
	bool isEmpty() const;
	double getPriceOf(const char* itemName) const;
	double totalPrice() const;
	void sortByName();
	void save(const char* filePath) const;

private:

	void free();
	void copyFrom(const ShoppingCart& other);
	void resize();
	int find(const char* name) const;
};