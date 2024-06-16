#include "Keyboard.h"

Keyboard::Keyboard() : ElectronicDevice(), layout(KeyboardLayout::QWERTY) {}

Keyboard::Keyboard(const char* model, double price, KeyboardLayout layout) : ElectronicDevice(model, price)
{
    setLayout(layout);
}

Keyboard::KeyboardLayout Keyboard::getLayout() const
{
    return layout;
}

void Keyboard::setLayout(KeyboardLayout layout)
{
    this->layout = layout;
}

ElectronicDevice* Keyboard::clone() const
{
    return new Keyboard(*this);
}
