#include "Circle.h"

const double PI = 3.1415;

Circle::Circle(int x, int y, double radius) : Shape(1), radius(radius)
{
    setPoint(0, x, y);
}

double Circle::getRadius() const
{
    return radius;
}

double Circle::getArea() const
{
    return PI * radius * radius;
}

double Circle::getPerimeter() const
{
    return 2 * PI * radius;
}

bool Circle::isPointInside(int x, int y) const
{
    Shape::Point point(x, y);
    return point.getDistanceTo(getPointAtIndex(0)) <= radius;
}
