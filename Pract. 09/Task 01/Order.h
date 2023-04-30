#pragma once
#include "MyString.h"

class Order
{
	MyString restaurantName;
	size_t productsAmount;
	MyString* productsList;

public:
	Order();
	Order(size_t productsAmount);

	Order(const Order& other);
	Order& operator=(const Order& other);

	Order(Order&& other);
	Order& operator=(Order&& other);

	~Order();

	const MyString& getRestaurantName() const;

private:

	void free();
	void copyFrom(const Order& other);
	void move(Order&& other);
};

