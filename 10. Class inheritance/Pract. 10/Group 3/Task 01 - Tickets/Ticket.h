#pragma once
#include "MyString.h"

class Ticket
{
public:
    Ticket() = default;
    Ticket(const MyString& playName, double price);

    const MyString& getPlayName() const;
    const double getPrice() const;

    void printInfo() const;

protected:
    void setPlayName(const MyString& name);
    void setPrice(double price);

private:
    MyString playName;
    double price = 0.0;
};

