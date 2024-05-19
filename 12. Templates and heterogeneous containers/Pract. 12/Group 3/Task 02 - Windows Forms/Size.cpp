#include "Size.h"

Size::Size(size_t width, size_t height) : width(width), height(height) {}

size_t Size::getWidth() const
{
    return width;
}

size_t Size::getHeight() const
{
    return height;
}
