#include "Ticket.h"

Ticket::Ticket(const MyString& playName, double price)
{
    setPlayName(playName);
    setPrice(price);
}

const MyString& Ticket::getPlayName() const
{
    return playName;
}

const double Ticket::getPrice() const
{
    return price;
}

void Ticket::printInfo() const
{
    std::cout << "Play name: " << playName << ", Price: " << price;
}

void Ticket::setPlayName(const MyString& name)
{
    if (name.length() == 0) {
        throw std::invalid_argument("Play name can't be empty!");
    }
    playName = name;
}

void Ticket::setPrice(double price)
{
    if (price < 0) {
        throw std::invalid_argument("Price must be a positive number!");
    }
    this->price = price;
}
