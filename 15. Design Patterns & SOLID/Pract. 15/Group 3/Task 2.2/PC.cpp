#include "PC.h"

PC::PC() : ElectronicDevice() {}

PC::PC(const char* model, double price) : ElectronicDevice(model, price) {}

ElectronicDevice* PC::clone() const
{
    return new PC(*this);
}
