#include "Laptop.h"

Laptop::Laptop() : ElectronicDevice(), weight(0.0) {}

Laptop::Laptop(const char* model, double price, double weight) : ElectronicDevice(model, price)
{
    setWeight(weight);
}

double Laptop::getWeight() const
{
    return weight;
}

void Laptop::setWeight(double weight)
{
    if (weight < 0) {
        throw std::invalid_argument("Weight must be a positive number!");
    }
    this->weight = weight;
}

ElectronicDevice* Laptop::clone() const
{
    return new Laptop(*this);
}
