#include "ElectronicDevice.h"
#include <cstring>
#pragma warning(disable: 4996)

ElectronicDevice::ElectronicDevice() : ElectronicDevice("n/a", 0.0) {}

ElectronicDevice::ElectronicDevice(const char* model, double price)
{
    setPrice(price);
    setModel(model);
}

ElectronicDevice::ElectronicDevice(const ElectronicDevice& other)
{
    copyFrom(other);
}

ElectronicDevice::ElectronicDevice(ElectronicDevice&& other) noexcept
{
    moveFrom(std::move(other));
}

ElectronicDevice& ElectronicDevice::operator=(const ElectronicDevice& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ElectronicDevice& ElectronicDevice::operator=(ElectronicDevice&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

const char* ElectronicDevice::getModel() const
{
    return model;
}

void ElectronicDevice::setModel(const char* model)
{
    if (!model) {
        throw std::invalid_argument("Model is nullptr!");
    }
    delete[] this->model;
    this->model = new char[strlen(model) + 1];
    strcpy(this->model, model);
}

const double ElectronicDevice::getPrice() const
{
    return price;
}

void ElectronicDevice::setPrice(double price)
{
    if (price < 0) {
        throw std::invalid_argument("Price must be a positive number!");
    }
    this->price = price;
}

ElectronicDevice::~ElectronicDevice()
{
    free();
}

void ElectronicDevice::free()
{
    delete[] model;
    model = nullptr;
    price = 0.0;
}

void ElectronicDevice::copyFrom(const ElectronicDevice& other)
{
    model = new char[strlen(other.model) + 1];
    strcpy(model, other.model);
    price = other.price;
}

void ElectronicDevice::moveFrom(ElectronicDevice&& other) noexcept
{
    model = other.model;
    other.model = nullptr;
    price = other.price;
    other.price = 0;
}
