#include "Control.h"

Control::Control(const Size& size, const Location& location) : size(size), location(location) {}

const Size& Control::getSize() const
{
    return size;
}

const Location& Control::getLocation() const
{
    return location;
}

void Control::setSize(const Size& size)
{
    // validation...
    this->size = size;
}

void Control::setLocation(const Location& location)
{
    // validation...
    this->location = location;
}
