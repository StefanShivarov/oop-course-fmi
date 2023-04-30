#pragma once
#include "Restaurant.h"
#include "Order.h"

class Foodpanda
{
	Restaurant* restaurants;
	size_t restaurantsCapacity;

public:
	Foodpanda();
	Foodpanda(size_t capacity);

	Foodpanda(const Foodpanda& other);
	Foodpanda& operator=(const Foodpanda& other);

	Foodpanda(Foodpanda&& other);
	Foodpanda& operator=(Foodpanda&& other);

	~Foodpanda();

	void addRestaurant(const Restaurant& restaurant);
	void manageOrders();

private:
	void free();
	void copyFrom(const Foodpanda& other);
	void move(Foodpanda&& other);
};

