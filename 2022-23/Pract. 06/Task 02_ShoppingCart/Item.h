#pragma once
class Item
{

	char* name = nullptr;
	bool isAvailable = false;
	double price = 0;

public:

	Item() = default;
	Item(const char* name, double price, bool isAvailable = false);
	Item(const Item& other);
	Item& operator=(const Item& other);
	~Item();

	const char* getName() const;
	void setName(const char* name);

	bool getIsAvailable() const;
	void setIsAvailable(bool available);

	double getPrice() const;
	void setPrice(double price);

private:

	void free();
	void copyFrom(const Item& other);
};