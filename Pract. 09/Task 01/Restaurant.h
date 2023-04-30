#pragma once
#include "MyString.h"
#include "Order.h"

const unsigned short MAX_NAME_LENGTH = 25;

class Restaurant
{
	MyString name;
	MyString* products;
	size_t productsCapacity;

public:
	Restaurant();
	Restaurant(size_t capacity);

	Restaurant(const Restaurant& other);
	Restaurant& operator=(const Restaurant& other);

	Restaurant(Restaurant&& other);
	Restaurant& operator=(Restaurant&& other);

	~Restaurant();

	const MyString& getName() const;

	void addProduct(const char* product);
	void receiveOrder(const Order& order);

private:

	void free();
	void copyFrom(const Restaurant& other);
	void move(Restaurant&& other);
};

