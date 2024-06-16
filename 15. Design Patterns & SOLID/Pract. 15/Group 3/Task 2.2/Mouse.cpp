#include "Mouse.h"

Mouse::Mouse() : ElectronicDevice(), dpi(0) {}

Mouse::Mouse(const char* model, double price, unsigned dpi) : ElectronicDevice(model, price)
{
    setDPI(dpi);
}

unsigned Mouse::getDPI() const
{
    return dpi;
}

void Mouse::setDPI(unsigned dpi)
{
    this->dpi = dpi;
}

ElectronicDevice* Mouse::clone() const
{
    return new Mouse(*this);
}
