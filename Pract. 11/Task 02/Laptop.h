#pragma once
#include "Computer.h"

class Laptop : public Computer 
{

private:

	static const unsigned int LAPTOP_PERIPHERALS_SIZE = 3;
	static MyString peripherals[LAPTOP_PERIPHERALS_SIZE];

public:

	Laptop();
	Laptop(double processorPower, const MyString& videoCardModel, unsigned int powerSupply, unsigned int ram);

	void printTypeOfComputer() const override;
	const MyString* getPeripherals() const override;
};

