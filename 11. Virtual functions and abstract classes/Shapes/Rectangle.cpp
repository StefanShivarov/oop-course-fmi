#include "Rectangle.h"

Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shape(4)
{
    setPoint(0, x1, y1);
    setPoint(1, x1, y3);
    setPoint(2, x3, y3);
    setPoint(3, x3, y1);
}

double Rectangle::getArea() const
{
    double sideA = getPointAtIndex(0).getDistanceTo(getPointAtIndex(1));
    double sideB = getPointAtIndex(0).getDistanceTo(getPointAtIndex(3));

    return sideA * sideB;
}

bool Rectangle::isPointInside(int x, int y) const
{
    Shape::Point p(x, y);
    return p.x >= getPointAtIndex(0).x 
        && p.x >= getPointAtIndex(1).x 
        && p.y <= getPointAtIndex(0).y 
        && p.y >= getPointAtIndex(2).y;
}
